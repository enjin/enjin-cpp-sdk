#include "enjinsdk/models/Transfer.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::models {

std::string Transfer::serialize() {
    rapidjson::Document document(rapidjson::kObjectType);

    if (from.has_value()) {
        utils::set_string_member(document, FROM_KEY, from.value());
    }
    if (to.has_value()) {
        utils::set_string_member(document, TO_KEY, to.value());
    }
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

Transfer& Transfer::set_from(const std::string& address) {
    from = address;
    return *this;
}

Transfer& Transfer::set_to(const std::string& address) {
    to = address;
    return *this;
}

Transfer& Transfer::set_token_id(const std::string& id) {
    token_id = id;
    return *this;
}

Transfer& Transfer::set_token_index(const std::string& index) {
    token_index = index;
    return *this;
}

Transfer& Transfer::set_value(const std::string& value) {
    Transfer::value = value;
    return *this;
}

bool Transfer::operator==(const Transfer& rhs) const {
    return from == rhs.from &&
           to == rhs.to &&
           token_id == rhs.token_id &&
           token_index == rhs.token_index &&
           value == rhs.value;
}

bool Transfer::operator!=(const Transfer& rhs) const {
    return !(rhs == *this);
}

}
