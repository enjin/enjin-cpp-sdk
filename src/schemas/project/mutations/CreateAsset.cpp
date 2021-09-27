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

#include "enjinsdk/project/CreateAsset.hpp"

#include "EnumUtils.hpp"
#include "RapidJsonUtils.hpp"

namespace enjin::sdk::project {

CreateAsset::CreateAsset() : graphql::AbstractGraphqlRequest("enjin.sdk.project.CreateAsset") {
}

std::string CreateAsset::serialize() const {
    rapidjson::Document document(rapidjson::kObjectType);
    utils::join_serialized_object_to_document(document, ProjectTransactionRequestArguments::serialize());

    if (name.has_value()) {
        utils::set_string_member(document, "name", name.value());
    }
    if (total_supply.has_value()) {
        utils::set_string_member(document, "totalSupply", total_supply.value());
    }
    if (initial_reserve.has_value()) {
        utils::set_string_member(document, "initialReserve", initial_reserve.value());
    }
    if (supply_model.has_value()) {
        utils::set_string_member(document, "supplyModel", utils::serialize_asset_supply_model(supply_model.value()));
    }
    if (melt_value.has_value()) {
        utils::set_string_member(document, "meltValue", melt_value.value());
    }
    if (melt_fee_ratio.has_value()) {
        utils::set_integer_member(document, "meltFeeRatio", melt_fee_ratio.value());
    }
    if (transferable.has_value()) {
        utils::set_string_member(document, "transferable", utils::serialize_asset_transferable(transferable.value()));
    }
    if (transfer_fee_settings.has_value()) {
        utils::set_object_member_from_type<models::AssetTransferFeeSettingsInput>(document,
                                                                                  "transferFeeSettings",
                                                                                  transfer_fee_settings.value());
    }
    if (non_fungible.has_value()) {
        utils::set_boolean_member(document, "nonFungible", non_fungible.value());
    }

    return utils::document_to_string(document);
}

CreateAsset& CreateAsset::set_name(const std::string& name) {
    CreateAsset::name = name;
    return *this;
}

CreateAsset& CreateAsset::set_total_supply(const std::string& total_supply) {
    CreateAsset::total_supply = total_supply;
    return *this;
}

CreateAsset& CreateAsset::set_initial_reserve(const std::string& initial_reserve) {
    CreateAsset::initial_reserve = initial_reserve;
    return *this;
}

CreateAsset& CreateAsset::set_supply_model(models::AssetSupplyModel supply_model) {
    CreateAsset::supply_model = supply_model;
    return *this;
}

CreateAsset& CreateAsset::set_melt_value(const std::string& melt_value) {
    CreateAsset::melt_value = melt_value;
    return *this;
}

CreateAsset& CreateAsset::set_melt_fee_ratio(int melt_fee_ratio) {
    CreateAsset::melt_fee_ratio = melt_fee_ratio;
    return *this;
}

CreateAsset& CreateAsset::set_transferable(models::AssetTransferable transferable) {
    CreateAsset::transferable = transferable;
    return *this;
}

CreateAsset&
CreateAsset::set_transfer_fee_settings(const models::AssetTransferFeeSettingsInput& transfer_fee_settings) {
    CreateAsset::transfer_fee_settings = transfer_fee_settings;
    return *this;
}

CreateAsset& CreateAsset::set_non_fungible(bool non_fungible) {
    CreateAsset::non_fungible = non_fungible;
    return *this;
}

bool CreateAsset::operator==(const CreateAsset& rhs) const {
    return static_cast<const graphql::AbstractGraphqlRequest&>(*this) ==
           static_cast<const graphql::AbstractGraphqlRequest&>(rhs) &&
           static_cast<const ProjectTransactionRequestArguments<CreateAsset>&>(*this) ==
           static_cast<const ProjectTransactionRequestArguments<CreateAsset>&>(rhs) &&
           name == rhs.name &&
           total_supply == rhs.total_supply &&
           initial_reserve == rhs.initial_reserve &&
           supply_model == rhs.supply_model &&
           melt_value == rhs.melt_value &&
           melt_fee_ratio == rhs.melt_fee_ratio &&
           transferable == rhs.transferable &&
           transfer_fee_settings == rhs.transfer_fee_settings &&
           non_fungible == rhs.non_fungible;
}

bool CreateAsset::operator!=(const CreateAsset& rhs) const {
    return !(rhs == *this);
}

}
