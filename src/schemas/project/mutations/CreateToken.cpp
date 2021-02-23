#include "enjinsdk/project/CreateToken.hpp"

#include "EnumUtils.hpp"
#include "RapidJsonUtils.hpp"

namespace enjin::sdk::project {

CreateToken::CreateToken() : graphql::AbstractGraphqlRequest("enjin.sdk.project.CreateToken") {
}

std::string CreateToken::serialize() {
    rapidjson::Document document(rapidjson::kObjectType);
    utils::join_serialized_object_to_document(document, TransactionRequestArgumentsTemplate::serialize());

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
        utils::set_string_member(document, "supplyModel", utils::serialize_token_supply_model(supply_model.value()));
    }
    if (melt_value.has_value()) {
        utils::set_string_member(document, "meltValue", melt_value.value());
    }
    if (melt_fee_ratio.has_value()) {
        utils::set_integer_member(document, "meltFeeRatio", melt_fee_ratio.value());
    }
    if (transferable.has_value()) {
        utils::set_string_member(document, "transferable", utils::serialize_token_transferable(transferable.value()));
    }
    if (transfer_fee_settings.has_value()) {
        utils::set_object_member_from_type<models::TokenTransferFeeSettingsInput>(document,
                                                                                  "transferFeeSettings",
                                                                                  transfer_fee_settings.value());
    }
    if (non_fungible.has_value()) {
        utils::set_boolean_member(document, "nonFungible", non_fungible.value());
    }

    return utils::document_to_string(document);
}

CreateToken& CreateToken::set_name(const std::string& name) {
    CreateToken::name = name;
    return *this;
}

CreateToken& CreateToken::set_total_supply(const std::string& total_supply) {
    CreateToken::total_supply = total_supply;
    return *this;
}

CreateToken& CreateToken::set_initial_reserve(const std::string& initial_reserve) {
    CreateToken::initial_reserve = initial_reserve;
    return *this;
}

CreateToken& CreateToken::set_supply_model(models::TokenSupplyModel supply_model) {
    CreateToken::supply_model = supply_model;
    return *this;
}

CreateToken& CreateToken::set_melt_value(const std::string& melt_value) {
    CreateToken::melt_value = melt_value;
    return *this;
}

CreateToken& CreateToken::set_melt_fee_ratio(int melt_fee_ratio) {
    CreateToken::melt_fee_ratio = melt_fee_ratio;
    return *this;
}

CreateToken& CreateToken::set_transferable(models::TokenTransferable transferable) {
    CreateToken::transferable = transferable;
    return *this;
}

CreateToken&
CreateToken::set_transfer_fee_settings(const models::TokenTransferFeeSettingsInput& transfer_fee_settings) {
    CreateToken::transfer_fee_settings = transfer_fee_settings;
    return *this;
}

CreateToken& CreateToken::set_non_fungible(bool non_fungible) {
    CreateToken::non_fungible = non_fungible;
    return *this;
}

bool CreateToken::operator==(const CreateToken& rhs) const {
    return static_cast<const graphql::AbstractGraphqlRequest&>(*this) ==
           static_cast<const graphql::AbstractGraphqlRequest&>(rhs) &&
           static_cast<const shared::TransactionRequestArgumentsTemplate<CreateToken>&>(*this) ==
           static_cast<const shared::TransactionRequestArgumentsTemplate<CreateToken>&>(rhs) &&
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

bool CreateToken::operator!=(const CreateToken& rhs) const {
    return !(rhs == *this);
}

}
