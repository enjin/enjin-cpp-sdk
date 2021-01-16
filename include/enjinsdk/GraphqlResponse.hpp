#ifndef ENJINCPPSDK_GRAPHQLRESPONSE_HPP
#define ENJINCPPSDK_GRAPHQLRESPONSE_HPP

#include "enjinsdk/GraphqlError.hpp"
#include "enjinsdk/internal/AbstractGraphqlResponse.hpp"
#include "enjinsdk/models/PaginationCursor.hpp"
#include "enjinsdk/serialization/IDeserializable.hpp"
#include "rapidjson/document.h"     // TODO: Implement Pimpl idiom to hide rapidjson implementation if possible.
#include "rapidjson/stringbuffer.h" //
#include "rapidjson/writer.h"       //
#include <optional>
#include <type_traits>
#include <vector>

namespace enjin::sdk::graphql {

/// \brief Variadic template for GraphQL responses.
/// \tparam ... Variadic types.
template<class...>
class GraphqlResponse;

/// \brief Models the body of a GraphQL response for non-paginated responses.
/// \tparam T The model of the data field. Must inherit from enjin::sdk::serialization::IDeserializable.
template<class T>
class GraphqlResponse<T> : public AbstractGraphqlResponse {
    static_assert(std::is_base_of<enjin::sdk::serialization::IDeserializable, T>::value,
                  "Type T does not inherit from IDeserializable.");

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

    void process_data(const char* data_json) override {
        // Start TODO: Utilize Pimpl idiom on this section.
        rapidjson::Document document;
        document.Parse(data_json);
        if (!document.IsObject() || !document.HasMember(RESULT_KEY) || !document[RESULT_KEY].IsObject()) {
            return;
        }

        auto& result_value = document[RESULT_KEY];
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        result_value.Accept(writer);
        const char* result_json = buffer.GetString();
        // End TODO

        T t;
        t.deserialize(result_json);
        result.emplace(t);
    }
};

/// \brief Models the body of a GraphQL response for paginated responses.
/// \tparam T The model of the data field. Must inherit from enjin::sdk::serialization::IDeserializable.
template<class T>
class GraphqlResponse<std::vector<T>> : public AbstractGraphqlResponse {
    static_assert(std::is_base_of<enjin::sdk::serialization::IDeserializable, T>::value,
                  "Type T does not inherit from IDeserializable.");

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

    void process_data(const char* data_json) override {
        /* TODO: Refactor method to utilize Pimpl idiom so that rapidjson usage is hidden away into a non-public
         *       implementation class.
         */
        rapidjson::Document document;
        document.Parse(data_json);
        if (!document.IsObject() || !document.HasMember(RESULT_KEY) || !document[RESULT_KEY].IsObject()) {
            return;
        }

        auto result_obj = document[RESULT_KEY].GetObject();
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
