#ifndef ENJINCPPSDK_BASESCHEMA_HPP
#define ENJINCPPSDK_BASESCHEMA_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/AbstractGraphqlRequest.hpp"
#include "enjinsdk/GraphqlResponse.hpp"
#include "enjinsdk/Logger.hpp"
#include "enjinsdk/TrustedPlatformMiddleware.hpp"
#include <exception>
#include <future>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

namespace enjin::sdk {

/// \brief Base class for schema with functionality to send GraphQL requests to the platform and process the responses.
class ENJINSDK_EXPORT BaseSchema {
public:
    BaseSchema() = delete;

    /// \brief Default destructor.
    ~BaseSchema() = default;

    /// \brief Returns the logger for this schema.
    /// \return The logger.
    [[nodiscard]] const std::shared_ptr<utils::Logger>& get_logger() const;

protected:
    TrustedPlatformMiddleware middleware;
    std::shared_ptr<utils::Logger> logger;
    std::string schema;

    /// \brief The sole constructor for a base schema.
    /// \param middleware The platform middleware.
    /// \param schema The name of the schema.
    /// \param logger The logger. Null pointer by default.
    BaseSchema(TrustedPlatformMiddleware middleware,
               std::string schema,
               std::shared_ptr<utils::Logger> logger = nullptr);

    /// \brief Creates the serialized request body to be sent to the platform.
    /// \param request The request.
    /// \return The serialized request body.
    std::string create_request_body(graphql::AbstractGraphqlRequest& request);

    /// \brief Sends a request for one object from the platform.
    /// \tparam T The type contained by the response.
    /// \param request The request to being sent.
    /// \return The future containing the response.
    template<class T>
    std::future<graphql::GraphqlResponse<T>> send_request_for_one(graphql::AbstractGraphqlRequest& request) {
        auto method = "POST";
        auto path = std::string("/graphql/").append(schema);
        auto content = http::IHttpClient::CONTENT_TYPE;
        auto body = create_request_body(request);

        http::HttpRequest http_request = http::HttpRequestBuilder()
                .method(method)
                .path_query_fragment(path)
                .content_type(content)
                .body(body)
                .build();

        return std::async([this, http_request] {
            http::HttpResponse response = middleware.get_client()->send_request(http_request).get();

            try {
                return graphql::GraphqlResponse<T>(response.get_body().value());
            } catch (std::exception e) {
                log_graphql_exception(e);
                throw e;
            }
        });
    }

    /// \brief Sends a request for many objects from the platform.
    /// \tparam T The type contained the response's vector.
    /// \param request The request to being sent.
    /// \return The future containing the response.
    template<class T>
    std::future<graphql::GraphqlResponse<std::vector<T>>>
    send_request_for_many(graphql::AbstractGraphqlRequest& request) {
        auto method = "POST";
        auto path = std::string("/graphql/").append(schema);
        auto content = http::IHttpClient::CONTENT_TYPE;
        auto body = create_request_body(request);

        http::HttpRequest http_request = http::HttpRequestBuilder()
                .method(method)
                .path_query_fragment(path)
                .content_type(content)
                .body(body)
                .build();

        return std::async([this, http_request]() {
            http::HttpResponse response = middleware.get_client()->send_request(http_request).get();

            try {
                return graphql::GraphqlResponse<std::vector<T>>(response.get_body().value());
            } catch (std::exception e) {
                log_graphql_exception(e);
                throw e;
            }
        });
    }

private:
    void log_graphql_exception(const std::exception& e);
};

}

#endif //ENJINCPPSDK_BASESCHEMA_HPP
