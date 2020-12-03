#include "EnumUtils.hpp"

std::string enjin::sdk::utils::get_name(enjin::sdk::graphql::TemplateType e) {
    // No default case to produce compiler warning
    switch (e) {
        case enjin::sdk::graphql::FRAGMENT:
            return "FRAGMENT";
        case enjin::sdk::graphql::MUTATION:
            return "MUTATION";
        case enjin::sdk::graphql::QUERY:
            return "QUERY";
    }
}
