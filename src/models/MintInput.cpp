#include "enjinsdk/models/MintInput.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::models {

std::string MintInput::serialize() {
    rapidjson::Document document(rapidjson::kObjectType);

    if (to.has_value()) {
        utils::set_string_member(document, TO_KEY, to.value());
    }
    if (value.has_value()) {
        utils::set_string_member(document, VALUE_KEY, value.value());
    }

    return utils::document_to_string(document);
}

MintInput& MintInput::set_to(const std::string& address) {
    to = address;
    return *this;
}

MintInput& MintInput::set_value(const std::string& value) {
    MintInput::value = value;
    return *this;
}

bool MintInput::operator==(const MintInput& rhs) const {
    return to == rhs.to &&
           value == rhs.value;
}

bool MintInput::operator!=(const MintInput& rhs) const {
    return !(rhs == *this);
}

}
