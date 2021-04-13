#include "enjinsdk/GraphqlQueryRegistry.hpp"

#include "TemplateConstants.hpp"

namespace enjin::sdk::graphql {

GraphqlQueryRegistry::GraphqlQueryRegistry() {
    register_template_constants();
}

bool GraphqlQueryRegistry::register_template(const std::string& name, const std::string& query) {
    if (registered.find(name) == registered.end()) {
        registered.emplace(name, query);
        return true;
    }

    return false;
}

void GraphqlQueryRegistry::register_template_constants() {
    for (const auto& t : TemplateConstants::templates) {
        register_template(t.first, t.second);
    }
}

bool GraphqlQueryRegistry::has_operation_for_name(const std::string& name) const {
    return registered.find(name) != registered.end();
}

std::string GraphqlQueryRegistry::get_operation_for_name(const std::string& name) const {
    auto iter = registered.find(name);
    if (iter == registered.end()) {
        return std::string();
    }

    return std::string(iter->second);
}

}
