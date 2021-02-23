#include "enjinsdk/models//AssetConfigData.hpp"

#include "EnumUtils.hpp"
#include "RapidJsonUtils.hpp"

namespace enjin::sdk::models {

void AssetConfigData::deserialize(const std::string& json) {
    rapidjson::Document document;
    document.Parse(json.c_str());
    if (document.IsObject()) {
        if (document.HasMember(MELT_FEE_RATIO_KEY) && document[MELT_FEE_RATIO_KEY].IsInt()) {
            melt_fee_ratio.emplace(document[MELT_FEE_RATIO_KEY].GetInt());
        }
        if (document.HasMember(MELT_FEE_MAX_RATIO_KEY) && document[MELT_FEE_MAX_RATIO_KEY].IsInt()) {
            melt_fee_max_ratio.emplace(document[MELT_FEE_MAX_RATIO_KEY].GetInt());
        }
        if (document.HasMember(MELT_VALUE_KEY) && document[MELT_VALUE_KEY].IsString()) {
            melt_value.emplace(document[MELT_VALUE_KEY].GetString());
        }
        if (document.HasMember(METADATA_URI_KEY) && document[METADATA_URI_KEY].IsString()) {
            metadata_uri.emplace(document[METADATA_URI_KEY].GetString());
        }
        if (document.HasMember(TRANSFERABLE_KEY) && document[TRANSFERABLE_KEY].IsString()) {
            transferable.emplace(utils::deserialize_asset_transferable(document[TRANSFERABLE_KEY].GetString()));
        }
        if (document.HasMember(TRANSFER_FEE_SETTINGS_KEY) && document[TRANSFER_FEE_SETTINGS_KEY].IsObject()) {
            transfer_fee_settings.emplace(utils::get_object_as_type<AssetTransferFeeSettings>(document,
                                                                                              TRANSFER_FEE_SETTINGS_KEY));
        }
    }
}

const std::optional<int>& AssetConfigData::get_melt_fee_ratio() const {
    return melt_fee_ratio;
}

const std::optional<int>& AssetConfigData::get_melt_fee_max_ratio() const {
    return melt_fee_max_ratio;
}

const std::optional<std::string>& AssetConfigData::get_melt_value() const {
    return melt_value;
}

const std::optional<std::string>& AssetConfigData::get_metadata_uri() const {
    return metadata_uri;
}

const std::optional<AssetTransferable>& AssetConfigData::get_transferable() const {
    return transferable;
}

const std::optional<AssetTransferFeeSettings>& AssetConfigData::get_transfer_fee_settings() const {
    return transfer_fee_settings;
}

bool AssetConfigData::operator==(const AssetConfigData& rhs) const {
    return melt_fee_ratio == rhs.melt_fee_ratio &&
           melt_fee_max_ratio == rhs.melt_fee_max_ratio &&
           melt_value == rhs.melt_value &&
           metadata_uri == rhs.metadata_uri &&
           transferable == rhs.transferable &&
           transfer_fee_settings == rhs.transfer_fee_settings;
}

bool AssetConfigData::operator!=(const AssetConfigData& rhs) const {
    return !(rhs == *this);
}

}
