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

#include "enjinsdk/models/AssetStateData.hpp"

#include "enjinsdk/JsonUtils.hpp"
#include "enjinsdk/JsonValue.hpp"

using namespace enjin::sdk::json;
using namespace enjin::sdk::models;
using namespace enjin::sdk::serialization;
using namespace enjin::sdk::utils;

class AssetStateData::Impl final : public IDeserializable {
public:
    Impl() = default;

    ~Impl() override = default;

    void deserialize(const std::string& json) override {
        JsonValue json_object;

        if (!json_object.try_parse_as_object(json)) {
            non_fungible.reset();
            block_height.reset();
            creator.reset();
            first_block.reset();
            reserve.reset();
            supply_model.reset();
            circulating_supply.reset();
            mintable_supply.reset();
            total_supply.reset();

            return;
        }

        JsonUtils::try_get_field(json_object, "nonFungible", non_fungible);
        JsonUtils::try_get_field(json_object, "blockHeight", block_height);
        JsonUtils::try_get_field(json_object, "creator", creator);
        JsonUtils::try_get_field(json_object, "firstBlock", first_block);
        JsonUtils::try_get_field(json_object, "reserve", reserve);
        JsonUtils::try_get_field(json_object, "supplyModel", supply_model);
        JsonUtils::try_get_field(json_object, "circulatingSupply", circulating_supply);
        JsonUtils::try_get_field(json_object, "mintableSupply", mintable_supply);
        JsonUtils::try_get_field(json_object, "totalSupply", total_supply);
    }

    [[nodiscard]] const std::optional<bool>& get_non_fungible() const {
        return non_fungible;
    }

    [[nodiscard]] const std::optional<int>& get_block_height() const {
        return block_height;
    }

    [[nodiscard]] const std::optional<std::string>& get_creator() const {
        return creator;
    }

    [[nodiscard]] const std::optional<int>& get_first_block() const {
        return first_block;
    }

    [[nodiscard]] const std::optional<std::string>& get_reserve() const {
        return reserve;
    }

    [[nodiscard]] const std::optional<AssetSupplyModel>& get_supply_model() const {
        return supply_model;
    }

    [[nodiscard]] const std::optional<std::string>& get_circulating_supply() const {
        return circulating_supply;
    }

    [[nodiscard]] const std::optional<std::string>& get_mintable_supply() const {
        return mintable_supply;
    }

    [[nodiscard]] const std::optional<std::string>& get_total_supply() const {
        return total_supply;
    }

    bool operator==(const Impl& rhs) const {
        return non_fungible == rhs.non_fungible
               && block_height == rhs.block_height
               && creator == rhs.creator
               && first_block == rhs.first_block
               && reserve == rhs.reserve
               && supply_model == rhs.supply_model
               && circulating_supply == rhs.circulating_supply
               && mintable_supply == rhs.mintable_supply
               && total_supply == rhs.total_supply;
    }

    bool operator!=(const Impl& rhs) const {
        return !(*this == rhs);
    }

private:
    std::optional<bool> non_fungible;
    std::optional<int> block_height;
    std::optional<std::string> creator;
    std::optional<int> first_block;
    std::optional<std::string> reserve;
    std::optional<AssetSupplyModel> supply_model;
    std::optional<std::string> circulating_supply;
    std::optional<std::string> mintable_supply;
    std::optional<std::string> total_supply;
};

AssetStateData::AssetStateData() : pimpl(std::make_unique<Impl>()) {
}

AssetStateData::AssetStateData(const AssetStateData& other) : pimpl(std::make_unique<Impl>(*other.pimpl)) {
}

AssetStateData::AssetStateData(AssetStateData&& other) noexcept = default;

AssetStateData::~AssetStateData() = default;

void AssetStateData::deserialize(const std::string& json) {
    pimpl->deserialize(json);
}

const std::optional<bool>& AssetStateData::get_non_fungible() const {
    return pimpl->get_non_fungible();
}

const std::optional<int>& AssetStateData::get_block_height() const {
    return pimpl->get_block_height();
}

const std::optional<std::string>& AssetStateData::get_creator() const {
    return pimpl->get_creator();
}

const std::optional<int>& AssetStateData::get_first_block() const {
    return pimpl->get_first_block();
}

const std::optional<std::string>& AssetStateData::get_reserve() const {
    return pimpl->get_reserve();
}

const std::optional<AssetSupplyModel>& AssetStateData::get_supply_model() const {
    return pimpl->get_supply_model();
}

const std::optional<std::string>& AssetStateData::get_circulating_supply() const {
    return pimpl->get_circulating_supply();
}

const std::optional<std::string>& AssetStateData::get_mintable_supply() const {
    return pimpl->get_mintable_supply();
}

const std::optional<std::string>& AssetStateData::get_total_supply() const {
    return pimpl->get_total_supply();
}

bool AssetStateData::operator==(const AssetStateData& rhs) const {
    return *pimpl == *rhs.pimpl;
}

bool AssetStateData::operator!=(const AssetStateData& rhs) const {
    return *pimpl != *rhs.pimpl;
}

AssetStateData& AssetStateData::operator=(const AssetStateData& rhs) {
    pimpl = std::make_unique<Impl>(*rhs.pimpl);
    return *this;
}
