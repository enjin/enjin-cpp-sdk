#ifndef ENJINCPPSDK_BASESCHEMA_HPP
#define ENJINCPPSDK_BASESCHEMA_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/AbstractGraphqlRequest.hpp"
#include "enjinsdk/GraphqlResponse.hpp"
#include "enjinsdk/TrustedPlatformMiddleware.hpp"
#include <future>
#include <string>
#include <vector>

namespace enjin::sdk {

// TODO: Documentation
class ENJINSDK_EXPORT BaseSchema {
public:
    BaseSchema() = delete;

    ~BaseSchema() = default;

protected:
    TrustedPlatformMiddleware middleware;
    std::string schema;

    BaseSchema(TrustedPlatformMiddleware middleware, std::string schema);

    std::string create_request_body(graphql::AbstractGraphqlRequest& request);

    template<class T>
    std::future<graphql::GraphqlResponse<T>> send_request_for_one(graphql::AbstractGraphqlRequest& request) {
        // TODO: Placeholder section until function parameters are finalized.
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
            auto future = middleware.get_client()->send_request(http_request);

            try {
                http::HttpResponse response = future.get();
                return graphql::GraphqlResponse<T>(response.get_body().value());
            } catch (std::exception& e) {
                // TODO: Create an HTTP exception class that implements std::exception and pass `e.what()`.
                throw std::exception(e.what());
            }
        });
    }

    template<class T>
    std::future<graphql::GraphqlResponse<std::vector<T>>>
    send_request_for_many(graphql::AbstractGraphqlRequest& request) {
        // TODO: Placeholder section until function parameters are finalized.
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
            auto future = middleware.get_client()->send_request(http_request);
            future.wait();

            try {
                http::HttpResponse response = future.get();
                return graphql::GraphqlResponse<std::vector<T>>(response.get_body().value());
            } catch (std::exception& e) {
                // TODO: Create an HTTP exception class that implements std::exception and pass `e.what()`.
                throw std::exception(e.what());
            }
        });
    }
};

}

#endif //ENJINCPPSDK_BASESCHEMA_HPP
