#include "enjinsdk/models//TokenConfigData.hpp"

namespace enjin::sdk::models {

void TokenConfigData::deserialize(const std::string& json) {

}

const std::optional<int>& TokenConfigData::get_melt_fee_ratio() const {
    return melt_fee_ratio;
}

const std::optional<int>& TokenConfigData::get_melt_fee_max_ratio() const {
    return melt_fee_max_ratio;
}

const std::optional<std::string>& TokenConfigData::get_melt_value() const {
    return melt_value;
}

const std::optional<std::string>& TokenConfigData::get_metadata_uri() const {
    return metadata_uri;
}

const std::optional<TokenTransferable>& TokenConfigData::get_transferable() const {
    return transferable;
}

const std::optional<TokenTransferFeeSettings>& TokenConfigData::get_transfer_fee_settings() const {
    return transfer_fee_settings;
}

}
