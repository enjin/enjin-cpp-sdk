#include "enjinsdk/BaseSchema.hpp"

#include "RapidJsonUtils.hpp"
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
    utils::set_string_member(document, "variables", request.serialize());

    return utils::document_to_string(document);
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
