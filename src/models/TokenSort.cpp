#include "enjinsdk/models/TokenSort.hpp"

#include "EnumUtils.hpp"
#include "RapidJsonUtils.hpp"

namespace enjin::sdk::models {

std::string TokenSort::serialize() {
    rapidjson::Document document(rapidjson::kObjectType);

    if (field.has_value()) {
        utils::set_string_member(document, FIELD_KEY, utils::serialize_token_field(field.value()));
    }
    if (direction.has_value()) {
        utils::set_string_member(document, DIRECTION_KEY, utils::serialize_sort_direction(direction.value()));
    }

    return utils::document_to_string(document);
}

TokenSort& TokenSort::set_field(TokenField field) {
    TokenSort::field = field;
    return *this;
}

TokenSort& TokenSort::set_direction(SortDirection direction) {
    TokenSort::direction = direction;
    return *this;
}

bool TokenSort::operator==(const TokenSort& rhs) const {
    return field == rhs.field &&
           direction == rhs.direction;
}

bool TokenSort::operator!=(const TokenSort& rhs) const {
    return !(rhs == *this);
}

}
