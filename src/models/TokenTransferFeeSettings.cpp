#include "enjinsdk/models/TokenTransferFeeSettings.hpp"

namespace enjin::sdk::models {

void TokenTransferFeeSettings::deserialize(const std::string& json) {

}

const std::optional<TokenTransferFeeType>& TokenTransferFeeSettings::getType() const {
    return type;
}

const std::optional<std::string>& TokenTransferFeeSettings::getTokenId() const {
    return token_id;
}

const std::optional<std::string>& TokenTransferFeeSettings::getValue() const {
    return value;
}

}
