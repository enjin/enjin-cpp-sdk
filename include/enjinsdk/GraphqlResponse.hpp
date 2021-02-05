#ifndef ENJINCPPSDK_GRAPHQLRESPONSE_HPP
#define ENJINCPPSDK_GRAPHQLRESPONSE_HPP

#include "enjinsdk/GraphqlError.hpp"
#include "enjinsdk/internal/AbstractGraphqlResponse.hpp"
#include "enjinsdk/internal/GraphqlResponseImpl.hpp"
#include "enjinsdk/models/PaginationCursor.hpp"
#include "enjinsdk/serialization/IDeserializable.hpp"
#include <optional>
#include <string>
#include <type_traits>
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

    /// \brief Returns the result of the response.
    /// \return Optional for the result.
    [[nodiscard]] const std::optional<T>& get_result() const {
        return result;
    }

    bool is_empty() noexcept override {
        return !result.has_value();
    }

protected:
    std::optional<T> result;

    void process_data(const std::string& data_json) override {
        auto json = get_serialized_result_object(data_json);
        if (json.has_value()) {
            T t;
            t.deserialize(json.value());
            result.emplace(t);
        }
    }
};

/// \brief Specialized member function for responses containing booleans instead of platform objects.
/// \param data_json The JSON string of the member.
template<>
void GraphqlResponse<bool>::process_data(const std::string& data_json) {
    result.emplace(get_bool_result(data_json));
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

    /// \brief Returns the result of the response.
    /// \return Optional for the result.
    [[nodiscard]] const std::optional<std::vector<T>>& get_result() const {
        return result;
    }

    bool is_empty() noexcept override {
        return !result.has_value();
    }

protected:
    std::optional<std::vector<T>> result;

    void process_data(const std::string& data_json) override {
        if (is_json_paginated(data_json)) {
            auto pagination_pair = get_pagination_data(data_json);
            if (pagination_pair.has_value()) {
                cursor = pagination_pair.value().first;

                std::vector<T> items;
                for (const auto& el_json : pagination_pair.value().second) {
                    T t;
                    t.deserialize(el_json);
                    items.push_back(t);
                }
                result.emplace(items);
            }
        } else {
            auto jsons = get_serialized_object_array(data_json);
            if (jsons.has_value()) {
                std::vector<T> items;
                for (const auto& el_json : jsons.value()) {
                    T t;
                    t.deserialize(el_json);
                    items.push_back(t);
                }
                result.emplace(items);
            }
        }
    }
};

}

#endif //ENJINCPPSDK_GRAPHQLRESPONSE_HPP
