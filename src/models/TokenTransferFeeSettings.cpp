#include "enjinsdk/models/TokenTransferFeeSettings.hpp"

namespace enjin::sdk::models {

void TokenTransferFeeSettings::deserialize(const std::string& json) {

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

}
