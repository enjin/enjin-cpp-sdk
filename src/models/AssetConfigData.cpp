/* Copyright 2021 Enjin Pte. Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "enjinsdk/models//AssetConfigData.hpp"

#include "enjinsdk/JsonUtils.hpp"
#include "enjinsdk/JsonValue.hpp"

using namespace enjin::sdk::json;
using namespace enjin::sdk::models;
using namespace enjin::sdk::serialization;
using namespace enjin::sdk::utils;

class AssetConfigData::Impl final : public IDeserializable {
public:
    Impl() = default;

    ~Impl() override = default;

    void deserialize(const std::string& json) override {
        JsonValue json_object;

        if (!json_object.try_parse_as_object(json)) {
            melt_fee_ratio.reset();
            melt_fee_max_ratio.reset();
            melt_value.reset();
            metadata_uri.reset();
            transferable.reset();
            transfer_fee_settings.reset();

            return;
        }

        JsonUtils::try_get_field(json_object, "meltFeeRatio", melt_fee_ratio);
        JsonUtils::try_get_field(json_object, "meltFeeMaxRatio", melt_fee_max_ratio);
        JsonUtils::try_get_field(json_object, "meltValue", melt_value);
        JsonUtils::try_get_field(json_object, "metadataURI", metadata_uri);
        JsonUtils::try_get_field(json_object, "transferable", transferable);
        JsonUtils::try_get_field(json_object, "transferFeeSettings", transfer_fee_settings);
    }

    [[nodiscard]] const std::optional<int>& get_melt_fee_ratio() const {
        return melt_fee_ratio;
    }

    [[nodiscard]] const std::optional<int>& get_melt_fee_max_ratio() const {
        return melt_fee_max_ratio;
    }

    [[nodiscard]] const std::optional<std::string>& get_melt_value() const {
        return melt_value;
    }

    [[nodiscard]] const std::optional<std::string>& get_metadata_uri() const {
        return metadata_uri;
    }

    [[nodiscard]] const std::optional<AssetTransferable>& get_transferable() const {
        return transferable;
    }

    [[nodiscard]] const std::optional<AssetTransferFeeSettings>& get_transfer_fee_settings() const {
        return transfer_fee_settings;
    }

    bool operator==(const Impl& rhs) const {
        return melt_fee_ratio == rhs.melt_fee_ratio
               && melt_fee_max_ratio == rhs.melt_fee_max_ratio
               && melt_value == rhs.melt_value
               && metadata_uri == rhs.metadata_uri
               && transferable == rhs.transferable
               && transfer_fee_settings == rhs.transfer_fee_settings;
    }

    bool operator!=(const Impl& rhs) const {
        return !(*this == rhs);
    }

private:
    std::optional<int> melt_fee_ratio;
    std::optional<int> melt_fee_max_ratio;
    std::optional<std::string> melt_value;
    std::optional<std::string> metadata_uri;
    std::optional<AssetTransferable> transferable;
    std::optional<AssetTransferFeeSettings> transfer_fee_settings;
};

AssetConfigData::AssetConfigData() : pimpl(std::make_unique<Impl>()) {
}

AssetConfigData::AssetConfigData(const AssetConfigData& other) : pimpl(std::make_unique<Impl>(*other.pimpl)) {
}

AssetConfigData::AssetConfigData(AssetConfigData&& other) noexcept = default;

AssetConfigData::~AssetConfigData() = default;

void AssetConfigData::deserialize(const std::string& json) {
    pimpl->deserialize(json);
}

const std::optional<int>& AssetConfigData::get_melt_fee_ratio() const {
    return pimpl->get_melt_fee_ratio();
}

const std::optional<int>& AssetConfigData::get_melt_fee_max_ratio() const {
    return pimpl->get_melt_fee_max_ratio();
}

const std::optional<std::string>& AssetConfigData::get_melt_value() const {
    return pimpl->get_melt_value();
}

const std::optional<std::string>& AssetConfigData::get_metadata_uri() const {
    return pimpl->get_metadata_uri();
}

const std::optional<AssetTransferable>& AssetConfigData::get_transferable() const {
    return pimpl->get_transferable();
}

const std::optional<AssetTransferFeeSettings>& AssetConfigData::get_transfer_fee_settings() const {
    return pimpl->get_transfer_fee_settings();
}

bool AssetConfigData::operator==(const AssetConfigData& rhs) const {
    return *pimpl == *rhs.pimpl;
}

bool AssetConfigData::operator!=(const AssetConfigData& rhs) const {
    return *pimpl != *rhs.pimpl;
}

AssetConfigData& AssetConfigData::operator=(const AssetConfigData& rhs) {
    pimpl = std::make_unique<Impl>(*rhs.pimpl);
    return *this;
}
