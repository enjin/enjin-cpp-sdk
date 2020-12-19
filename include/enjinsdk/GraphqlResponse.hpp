#ifndef ENJINCPPSDK_GRAPHQLRESPONSE_HPP
#define ENJINCPPSDK_GRAPHQLRESPONSE_HPP

#include "enjinsdk/GraphqlError.hpp"
#include "enjinsdk/internal/AbstractGraphqlResponse.hpp"
#include "enjinsdk/models/PaginationCursor.hpp"
#include "enjinsdk/serialization/ISerializable.hpp"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
#include <optional>
#include <type_traits>
#include <vector>

namespace enjin::sdk::graphql {

/// \brief Variadic template for GraphQL responses.
/// \tparam ... Variadic types.
template<class...>
class GraphqlResponse;

/// \brief Models the body of a GraphQL response for non-paginated responses.
/// \tparam T The model of the data field. Must inherit from enjin::sdk::serialization::ISerializable.
template<class T>
class GraphqlResponse<T> : public AbstractGraphqlResponse {
    static_assert(std::is_base_of<enjin::sdk::serialization::ISerializable, T>::value,
                  "Type T does not inherit from ISerializable.");

public:
    GraphqlResponse() = delete;

    /// \brief Constructs the GraphQL response with a JSON string.
    /// \param raw The JSON body that is the GraphQL response.
    explicit GraphqlResponse(const char* raw) {
        process(raw);
    };

    /// \brief Returns the result of the response.
    /// \return Optional for the result.
    std::optional<T> get_result() {
        return result;
    }

    bool is_empty() noexcept override {
        return !result.has_value();
    }

protected:
    std::optional<T> result;

    void process_data(const rapidjson::Document& document) override {
        auto data_obj = document[DATA_KEY].GetObject();
        if (!data_obj.HasMember(RESULT_KEY) || !data_obj[RESULT_KEY].IsObject()) {
            return;
        }

        auto& result_value = data_obj[RESULT_KEY];
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        result_value.Accept(writer);
        const char* result_json = buffer.GetString();

        T t;
        t.deserialize(result_json);
        result.emplace(t);
    }
};

/// \brief Models the body of a GraphQL response for paginated responses.
/// \tparam T The model of the data field. Must inherit from enjin::sdk::serialization::ISerializable.
template<class T>
class GraphqlResponse<std::vector<T>> : public AbstractGraphqlResponse {
    static_assert(std::is_base_of<enjin::sdk::serialization::ISerializable, T>::value,
                  "Type T does not inherit from ISerializable.");

public:
    GraphqlResponse() = delete;

    /// \brief Constructs the GraphQL response with a JSON string.
    /// \param raw The JSON body that is the GraphQL response.
    explicit GraphqlResponse(const char* raw) {
        process(raw);
    };

    /// \brief Returns the result of the response.
    /// \return Optional for the result.
    std::optional<std::vector<T>> get_result() {
        return result;
    }

    bool is_empty() noexcept override {
        return !result.has_value();
    }

protected:
    std::optional<std::vector<T>> result;

    void process_data(const rapidjson::Document& document) override {
        auto data_obj = document[DATA_KEY].GetObject();
        if (!data_obj.HasMember(RESULT_KEY) || !data_obj[RESULT_KEY].IsObject()) {
            return;
        }

        auto result_obj = data_obj[RESULT_KEY].GetObject();
        if (!result_obj.HasMember(ITEMS_KEY)
            || !result_obj.HasMember(CURSOR_KEY)
            || !result_obj[ITEMS_KEY].IsArray()
            || !result_obj[CURSOR_KEY].IsObject()) {
            return;
        }

        // Parse items list
        std::vector<T> list;
        for (auto& v : result_obj[ITEMS_KEY].GetArray()) {
            rapidjson::StringBuffer buffer;
            rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
            v.Accept(writer);
            const char* result_json = buffer.GetString();

            T t;
            t.deserialize(result_json);
            list.push_back(t);
        }
        result.emplace(list);

        // Parse cursor
        auto& cursor_value = result_obj[CURSOR_KEY];
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        cursor_value.Accept(writer);
        const char* cursor_json = buffer.GetString();

        enjin::sdk::models::PaginationCursor c;
        c.deserialize(cursor_json);
        cursor.emplace(c);
    }
};

}

#endif //ENJINCPPSDK_GRAPHQLRESPONSE_HPP
