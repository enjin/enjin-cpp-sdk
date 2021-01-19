#include "enjinsdk/models/Melt.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::models {

std::string Melt::serialize() {
    rapidjson::Document document(rapidjson::kObjectType);

    if (token_id.has_value()) {
        utils::set_string_member(document, TOKEN_ID_KEY, token_id.value());
    }
    if (token_index.has_value()) {
        utils::set_string_member(document, TOKEN_INDEX_KEY, token_index.value());
    }
    if (value.has_value()) {
        utils::set_string_member(document, VALUE_KEY, value.value());
    }

    return utils::document_to_string(document);
}

Melt& Melt::set_token_id(const std::string& id) {
    token_id = id;
    return *this;
}

Melt& Melt::set_token_index(const std::string& index) {
    token_index = index;
    return *this;
}

Melt& Melt::set_value(const std::string& value) {
    Melt::value = value;
    return *this;
}

bool Melt::operator==(const Melt& rhs) const {
    return token_id == rhs.token_id &&
           token_index == rhs.token_index &&
           value == rhs.value;
}

bool Melt::operator!=(const Melt& rhs) const {
    return !(rhs == *this);
}

}
