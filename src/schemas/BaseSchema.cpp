#include "enjinsdk/BaseSchema.hpp"

#include "RapidJsonUtils.hpp"
#include <string>
#include <utility>

namespace enjin::sdk {

BaseSchema::BaseSchema(TrustedPlatformMiddleware middleware, std::string schema)
        : middleware(std::move(middleware)), schema(std::move(schema)) {
}

std::string BaseSchema::create_request_body(graphql::AbstractGraphqlRequest& request) {
    rapidjson::Document document(rapidjson::kObjectType);

    utils::set_string_member(document,
                             "query",
                             middleware.get_query_registry().get_operation_for_name(request.get_namespace()));
    utils::set_string_member(document, "variables", request.serialize());

    return utils::document_to_string(document);
}

}
