#include "enjinsdk/BaseSchema.hpp"

#include "RapidJsonUtils.hpp"
#include <sstream>
#include <string>

namespace enjin::sdk {

BaseSchema::BaseSchema(TrustedPlatformMiddleware middleware,
                       std::string schema,
                       std::shared_ptr<utils::Logger> logger)
        : middleware(std::move(middleware)),
          schema(std::move(schema)),
          logger(std::move(logger)) {
}

std::string BaseSchema::create_request_body(graphql::AbstractGraphqlRequest& request) {
    rapidjson::Document document(rapidjson::kObjectType);

    utils::set_string_member(document,
                             "query",
                             middleware.get_query_registry().get_operation_for_name(request.get_namespace()));
    utils::set_object_member_from_string(document, "variables", request.serialize());

    return utils::document_to_string(document);
}

http::HttpRequest BaseSchema::create_request(graphql::AbstractGraphqlRequest& request) {
    http::HttpRequestBuilder builder;
    builder.method("POST")
           .path_query_fragment(std::string("/graphql/").append(schema))
           .content_type(JSON)
           .body(create_request_body(request));

    // Adds the default SDK user agent header using the defined SDK version if the definition was set
    std::stringstream user_agent_ss;
    user_agent_ss << http::TrustedPlatformHandler::USER_AGENT_PREFIX;

#ifdef ENJINSDK_VERSION
    user_agent_ss << ENJINSDK_VERSION;
#else
    user_agent_ss << "?";
#endif

    builder.add_header(http::TrustedPlatformHandler::USER_AGENT, user_agent_ss.str());

    // Adds authorization header if SDK has been authenticated
    auto tp_handler = middleware.get_handler();
    if (tp_handler != nullptr && tp_handler->is_authenticated()) {
        std::stringstream authorization_ss;
        authorization_ss << http::TrustedPlatformHandler::AUTHORIZATION_SCHEMA
                        << " "
                        << tp_handler->get_auth_token().value();

        builder.add_header(http::TrustedPlatformHandler::AUTHORIZATION, authorization_ss.str());
    }

    return builder.build();
}

const std::shared_ptr<utils::Logger>& BaseSchema::get_logger() const {
    return logger;
}

void BaseSchema::log_graphql_exception(const std::exception& e) {
    std::stringstream ss;
    ss << "An exception occurred processing GraphQL response: " << e.what();
    logger->log(utils::LogLevel::SEVERE, ss.str());
}

}
