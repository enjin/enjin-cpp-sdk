#include "enjinsdk/models/TokenTransferFeeSettings.hpp"

#include "EnumUtils.hpp"
#include "RapidJsonUtils.hpp"

namespace enjin::sdk::models {

void TokenTransferFeeSettings::deserialize(const std::string& json) {
    rapidjson::Document document;
    document.Parse(json.c_str());
    if (document.IsObject()) {
        if (document.HasMember(TYPE_KEY) && document[TYPE_KEY].IsString()) {
            type.emplace(utils::deserialize_token_transfer_fee_type(document[TYPE_KEY].GetString()));
        }
        if (document.HasMember(TOKEN_ID_KEY) && document[TOKEN_ID_KEY].IsString()) {
            token_id.emplace(document[TOKEN_ID_KEY].GetString());
        }
        if (document.HasMember(VALUE_KEY) && document[VALUE_KEY].IsString()) {
            value.emplace(document[VALUE_KEY].GetString());
        }
    }
}

const std::optional<TokenTransferFeeType>& TokenTransferFeeSettings::get_type() const {
    return type;
}

const std::optional<std::string>& TokenTransferFeeSettings::get_token_id() const {
    return token_id;
}

const std::optional<std::string>& TokenTransferFeeSettings::get_value() const {
    return value;
}

bool TokenTransferFeeSettings::operator==(const TokenTransferFeeSettings& rhs) const {
    return type == rhs.type &&
           token_id == rhs.token_id &&
           value == rhs.value;
}

bool TokenTransferFeeSettings::operator!=(const TokenTransferFeeSettings& rhs) const {
    return !(rhs == *this);
}

std::string TokenTransferFeeSettingsInput::serialize() {
    rapidjson::Document document(rapidjson::kObjectType);

    if (type.has_value()) {
        utils::set_string_member(document, TYPE_KEY, utils::serialize_token_transfer_fee_type(type.value()));
    }
    if (token_id.has_value()) {
        utils::set_string_member(document, TOKEN_ID_KEY, token_id.value());
    }
    if (value.has_value()) {
        utils::set_string_member(document, VALUE_KEY, value.value());
    }

    return utils::document_to_string(document);
}

TokenTransferFeeSettingsInput& TokenTransferFeeSettingsInput::set_type(TokenTransferFeeType type) {
    TokenTransferFeeSettingsInput::type = type;
    return *this;
}

TokenTransferFeeSettingsInput& TokenTransferFeeSettingsInput::set_token_id(const std::string& token_id) {
    TokenTransferFeeSettingsInput::token_id = token_id;
    return *this;
}

TokenTransferFeeSettingsInput& TokenTransferFeeSettingsInput::set_value(const std::string& value) {
    TokenTransferFeeSettingsInput::value = value;
    return *this;
}

bool TokenTransferFeeSettingsInput::operator==(const TokenTransferFeeSettingsInput& rhs) const {
    return static_cast<const TokenTransferFeeSettings&>(*this) ==
           static_cast<const TokenTransferFeeSettings&>(rhs);
}

bool TokenTransferFeeSettingsInput::operator!=(const TokenTransferFeeSettingsInput& rhs) const {
    return !(rhs == *this);
}

}
