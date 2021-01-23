#ifndef ENJINCPPSDK_GRAPHQLRESPONSE_HPP
#define ENJINCPPSDK_GRAPHQLRESPONSE_HPP

#include "enjinsdk/GraphqlError.hpp"
#include "enjinsdk/internal/AbstractGraphqlResponse.hpp"
#include "enjinsdk/models/PaginationCursor.hpp"
#include "enjinsdk/serialization/IDeserializable.hpp"
#include "RapidJsonUtils.hpp"       // TODO: Implement Pimpl idiom to hide rapidjson implementation if possible.
#include "rapidjson/document.h"     //
#include "rapidjson/stringbuffer.h" //
#include "rapidjson/writer.h"       //
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
    static_assert(std::is_base_of<enjin::sdk::serialization::IDeserializable, T>::value,
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
    std::optional<T> get_result() {
        return result;
    }

    bool is_empty() noexcept override {
        return !result.has_value();
    }

protected:
    std::optional<T> result;

    void process_data(const std::string& data_json) override {
        /* TODO: Refactor method to utilize Pimpl idiom so that rapidjson usage is hidden away into a non-public
         *       implementation class.
         */
        rapidjson::Document document;
        document.Parse(data_json.c_str());

        if (document.IsObject() && document.HasMember(RESULT_KEY) && document[RESULT_KEY].IsObject()) {
            result.emplace(utils::get_object_as_type<T>(document, RESULT_KEY));
        }
    }
};

/// \brief Models the body of a GraphQL response for paginated responses or responses with many objects.
/// \tparam T The model of the data field. Must inherit from enjin::sdk::serialization::IDeserializable.
template<class T>
class GraphqlResponse<std::vector<T>> : public AbstractGraphqlResponse {
    static_assert(std::is_base_of<enjin::sdk::serialization::IDeserializable, T>::value,
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
    std::optional<std::vector<T>> get_result() {
        return result;
    }

    bool is_empty() noexcept override {
        return !result.has_value();
    }

protected:
    std::optional<std::vector<T>> result;

    void process_data(const std::string& data_json) override {
        /* TODO: Refactor method to utilize Pimpl idiom so that rapidjson usage is hidden away into a non-public
         *       implementation class.
         */
        rapidjson::Document document;
        document.Parse(data_json.c_str());
        if (!document.IsObject() || !document.HasMember(RESULT_KEY)) {
            return;
        }

        if (document[RESULT_KEY].IsObject()) {
            std::string result_json = utils::get_object_as_string(document, RESULT_KEY);
            rapidjson::Document result_document;
            result_document.Parse(result_json.c_str());

            auto result_obj = document[RESULT_KEY].GetObject();
            if (result_obj.HasMember(ITEMS_KEY) && result_obj[ITEMS_KEY].IsArray()) {
                result.emplace(utils::get_array_as_type_vector<T>(result_document, ITEMS_KEY));
            }
            if (result_obj.HasMember(CURSOR_KEY) && result_obj[CURSOR_KEY].IsObject()) {
                cursor.emplace(utils::get_object_as_type<models::PaginationCursor>(result_document, CURSOR_KEY));
            }
        } else if (document[RESULT_KEY].IsArray()) {
            result.emplace(utils::get_array_as_type_vector<T>(document, RESULT_KEY));
        }
    }
};

}

#endif //ENJINCPPSDK_GRAPHQLRESPONSE_HPP
