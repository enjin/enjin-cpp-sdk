#include "enjinsdk/GraphqlQueryRegistry.hpp"

#include "TemplateConstants.hpp"
#include <algorithm>

namespace enjin::sdk::graphql {

GraphqlQueryRegistry::GraphqlQueryRegistry() {
    register_template_constants();
}

GraphqlQueryRegistry::~GraphqlQueryRegistry() = default;

bool GraphqlQueryRegistry::register_template(const std::string& name, const std::string& query) {
    if (this->registered.find(name) == this->registered.end()) {
        this->registered.emplace(name, query);
        return true;
    }

    return false;
}

void GraphqlQueryRegistry::register_template_constants() {
    std::map<std::string, std::string> templates = TemplateConstants::templates;
    std::for_each(templates.begin(), templates.end(), [this](const std::pair<std::string, std::string>& t) {
        this->register_template(t.first, t.second);
    });
}

bool GraphqlQueryRegistry::has_operation_for_name(const std::string& name) {
    return this->registered.find(name) != this->registered.end();
}

std::string GraphqlQueryRegistry::get_operation_for_name(const std::string& name) const {
    auto iter = this->registered.find(name);
    if (iter == this->registered.end()) {
        return std::string();
    }

    return std::string(iter->second);
}

}
