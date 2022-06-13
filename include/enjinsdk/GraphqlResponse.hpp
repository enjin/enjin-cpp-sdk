/* Copyright 2021 Enjin Pte. Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ENJINCPPSDK_GRAPHQLRESPONSE_HPP
#define ENJINCPPSDK_GRAPHQLRESPONSE_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/GraphqlError.hpp"
#include "enjinsdk/IDeserializable.hpp"
#include "enjinsdk/JsonUtils.hpp"
#include "enjinsdk/internal/AbstractGraphqlResponse.hpp"
#include "enjinsdk/models/PaginationCursor.hpp"
#include <optional>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

namespace enjin::sdk::graphql {

/// \brief Variadic template for GraphQL responses.
/// \tparam ... Variadic types.
template<class...>
class GraphqlResponse;

/// \brief Models the body of a GraphQL response for responses with one object.
/// \tparam T The model of the data field. Must inherit from enjin::sdk::serialization::IDeserializable.
template<class T>
class GraphqlResponse<T> : public AbstractGraphqlResponse {
    static_assert(std::is_base_of<serialization::IDeserializable, T>::value || std::is_same_v<bool, T>,
                  "Type T does not inherit from IDeserializable or boolean.");

public:
    GraphqlResponse() = default;

    /// \brief Constructs the GraphQL response with a JSON string.
    /// \param raw The JSON body that is the GraphQL response.
    explicit GraphqlResponse(const std::string& raw) {
        process(raw);
    };

    GraphqlResponse(const GraphqlResponse<T>& other) : result(other.esult) {
    }

    GraphqlResponse(GraphqlResponse<T>&& other) noexcept: result(std::move(other.result)) {
    }

    ~GraphqlResponse() override = default;

    [[nodiscard]] const std::optional<models::PaginationCursor>& get_cursor() const override {
        return empty_cursor;
    }

    /// \brief Returns the result of the response.
    /// \return Optional for the result.
    [[nodiscard]] const std::optional<T>& get_result() const {
        return result;
    }

    [[nodiscard]] bool is_empty() const noexcept override {
        return !result.has_value();
    }

    [[nodiscard]] bool is_paginated() const noexcept override {
        return false;
    }

    GraphqlResponse<T>& operator=(const GraphqlResponse<T>& rhs) {
        result = rhs.result;

        return *this;
    }

protected:
    void process_data(const json::JsonValue& data) override {
        T new_result;

        if (utils::JsonUtils::try_get_object_as_type(data, ResultKey, new_result)) {
            result.emplace(std::move(new_result));
        }
    }

private:
    const std::optional<models::PaginationCursor> empty_cursor;
    std::optional<T> result;
};

/// \brief Specialized member function for responses containing booleans instead of platform objects.
/// \param data_json The JSON string of the member.
template<>
inline void GraphqlResponse<bool>::process_data(const json::JsonValue& data) {
    bool new_result;
    json::JsonValue value;

    if (data.try_get_object_field(ResultKey, value) && value.try_get_bool(new_result)) {
        result = new_result;
    }
}

/// \brief Models the body of a GraphQL response for paginated responses or responses with many objects.
/// \tparam T The model of the data field. Must inherit from enjin::sdk::serialization::IDeserializable.
template<class T>
class GraphqlResponse<std::vector<T>> : public AbstractGraphqlResponse {
    static_assert(std::is_base_of<serialization::IDeserializable, T>::value,
                  "Type T does not inherit from IDeserializable.");

public:
    GraphqlResponse() = default;

    /// \brief Constructs the GraphQL response with a JSON string.
    /// \param raw The JSON body that is the GraphQL response.
    explicit GraphqlResponse(const std::string& raw) {
        process(raw);
    };

    GraphqlResponse(const GraphqlResponse<std::vector<T>>& other) : cursor(other.cursor), result(other.result) {
    }

    GraphqlResponse(GraphqlResponse<std::vector<T>>&& other) noexcept: cursor(std::move(other.cursor)),
                                                                       result(std::move(other.result)) {
    }

    ~GraphqlResponse() override = default;

    [[nodiscard]] const std::optional<models::PaginationCursor>& get_cursor() const override {
        return cursor;
    }

    /// \brief Returns the result of the response.
    /// \return Optional for the result.
    [[nodiscard]] const std::optional<std::vector<T>>& get_result() const {
        return result;
    }

    [[nodiscard]] bool is_empty() const noexcept override {
        return !result.has_value();
    }

    [[nodiscard]] bool is_paginated() const noexcept override {
        return cursor.has_value();
    }

    GraphqlResponse<std::vector<T>>& operator=(const GraphqlResponse<std::vector<T>>& rhs) {
        cursor = rhs.cursor;
        result = rhs.result;

        return *this;
    }

protected:
    void process_data(const json::JsonValue& data) override {
        if (is_result_paginated(data)) {
            process_paginated_result(data);
        } else {
            process_non_paginated_result(data);
        }
    }

private:
    std::optional<models::PaginationCursor> cursor;
    std::optional<std::vector<T>> result;

    static constexpr char CursorKey[] = "cursor";
    static constexpr char ItemsKey[] = "items";

    /// \brief Processes non-paginated data to form the result.
    /// \param data The data JSON object.
    void process_non_paginated_result(const json::JsonValue& data) {
        std::vector<T> new_result;

        if (utils::JsonUtils::try_get_array_as_type_array(data, ResultKey, new_result)) {
            result.emplace(std::move(new_result));
        }
    }

    /// \brief Processes paginated data to form the result and pagination cursor.
    /// \param data The data JSON object.
    void process_paginated_result(const json::JsonValue& data) {
        json::JsonValue result_object;

        if (!data.try_get_object_field(ResultKey, result_object)) {
            return;
        }

        models::PaginationCursor new_cursor;
        std::vector<T> new_result;

        if (utils::JsonUtils::try_get_object_as_type(result_object, CursorKey, new_cursor)) {
            cursor.emplace(std::move(new_cursor));
        }

        if (utils::JsonUtils::try_get_array_as_type_array(result_object, ItemsKey, new_result)) {
            result.emplace(std::move(new_result));
        }
    }

    /// \brief Determines whether the data is paginated.
    /// \param data The data JSON object.
    /// \return Whether the data is paginated.
    static bool is_result_paginated(const json::JsonValue& data) {
        json::JsonValue result_object;

        if (data.try_get_object_field(ResultKey, result_object)) {
            json::JsonValue cursor_object;

            return result_object.try_get_object_field(CursorKey, cursor_object) && cursor_object.is_object();
        }

        return false;
    }
};

}

#endif //ENJINCPPSDK_GRAPHQLRESPONSE_HPP
