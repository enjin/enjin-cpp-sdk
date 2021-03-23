#include "enjinsdk/internal/AbstractGraphqlRequest.hpp"

#include <utility>

namespace enjin::sdk::graphql {

AbstractGraphqlRequest::AbstractGraphqlRequest(std::string template_key) : template_key(std::move(template_key)) {
}

const std::string& AbstractGraphqlRequest::get_namespace() const {
    return template_key;
}

bool AbstractGraphqlRequest::operator==(const AbstractGraphqlRequest& rhs) const {
    return template_key == rhs.template_key;
}

bool AbstractGraphqlRequest::operator!=(const AbstractGraphqlRequest& rhs) const {
    return !(rhs == *this);
}

}
