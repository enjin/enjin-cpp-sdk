#include "enjinsdk/models/Trade.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::models {

std::string Trade::serialize() {
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

Trade& Trade::set_token_id(const std::string& id) {
    token_id = id;
    return *this;
}

Trade& Trade::set_token_index(const std::string& index) {
    token_index = index;
    return *this;
}

Trade& Trade::set_value(const std::string& value) {
    Trade::value = value;
    return *this;
}

bool Trade::operator==(const Trade& rhs) const {
    return token_id == rhs.token_id &&
           token_index == rhs.token_index &&
           value == rhs.value;
}

bool Trade::operator!=(const Trade& rhs) const {
    return !(rhs == *this);
}

}
