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

#include "enjinsdk/models/AssetTransferFeeSettingsInput.hpp"

#include "enjinsdk/JsonUtils.hpp"
#include <utility>

using namespace enjin::sdk::json;
using namespace enjin::sdk::models;
using namespace enjin::sdk::serialization;
using namespace enjin::sdk::utils;

class AssetTransferFeeSettingsInput::Impl final : public ISerializable {
public:
    Impl() = default;

    ~Impl() override = default;

    [[nodiscard]] std::string serialize() const override {
        return to_json().to_string();
    }

    void set_type(AssetTransferFeeType type) {
        type_opt = type;
    }

    void set_asset_id(std::string asset_id) {
        asset_id_opt = std::move(asset_id);
    }

    void set_value(std::string value) {
        value_opt = std::move(value);
    }

    [[nodiscard]] json::JsonValue to_json() const override {
        JsonValue json = JsonValue::create_object();

        JsonUtils::try_set_field(json, "type", type_opt);
        JsonUtils::try_set_field(json, "assetId", asset_id_opt);
        JsonUtils::try_set_field(json, "value", value_opt);

        return json;
    }

    bool operator==(const Impl& rhs) const {
        return type_opt == rhs.type_opt
               && asset_id_opt == rhs.asset_id_opt
               && value_opt == rhs.value_opt;
    }

    bool operator!=(const Impl& rhs) const {
        return !(*this == rhs);
    }

private:
    std::optional<AssetTransferFeeType> type_opt;
    std::optional<std::string> asset_id_opt;
    std::optional<std::string> value_opt;
};

AssetTransferFeeSettingsInput::AssetTransferFeeSettingsInput() : pimpl(std::make_unique<Impl>()) {
}

AssetTransferFeeSettingsInput::AssetTransferFeeSettingsInput(const AssetTransferFeeSettingsInput& other)
        : pimpl(std::make_unique<Impl>(*other.pimpl)) {
}

AssetTransferFeeSettingsInput::AssetTransferFeeSettingsInput(AssetTransferFeeSettingsInput&& other) noexcept = default;

AssetTransferFeeSettingsInput::~AssetTransferFeeSettingsInput() = default;

std::string AssetTransferFeeSettingsInput::serialize() const {
    return to_json().to_string();
}

AssetTransferFeeSettingsInput& AssetTransferFeeSettingsInput::set_type(AssetTransferFeeType type) {
    pimpl->set_type(type);
    return *this;
}

AssetTransferFeeSettingsInput& AssetTransferFeeSettingsInput::set_asset_id(std::string asset_id) {
    pimpl->set_asset_id(std::move(asset_id));
    return *this;
}

AssetTransferFeeSettingsInput& AssetTransferFeeSettingsInput::set_value(std::string value) {
    pimpl->set_value(std::move(value));
    return *this;
}

JsonValue AssetTransferFeeSettingsInput::to_json() const {
    return pimpl->to_json();
}

bool AssetTransferFeeSettingsInput::operator==(const AssetTransferFeeSettingsInput& rhs) const {
    return *pimpl == *rhs.pimpl;
}

bool AssetTransferFeeSettingsInput::operator!=(const AssetTransferFeeSettingsInput& rhs) const {
    return *pimpl != *rhs.pimpl;
}

AssetTransferFeeSettingsInput& AssetTransferFeeSettingsInput::operator=(const AssetTransferFeeSettingsInput& rhs) {
    pimpl = std::make_unique<Impl>(*rhs.pimpl);
    return *this;
}
