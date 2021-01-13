#include "EnumUtils.hpp"
#include "StringUtils.hpp"

namespace enjin::sdk::utils {

enjin::sdk::models::TokenSupplyModel deserialize_token_supply_model(const std::string& s) noexcept {
    std::string str = to_upper(s);
    if (str == "FIXED") {
        return models::TokenSupplyModel::FIXED;
    } else if (str == "SETTABLE") {
        return models::TokenSupplyModel::SETTABLE;
    } else if (str == "INFINITE") {
        return models::TokenSupplyModel::INFINITE;
    } else if (str == "COLLAPSING") {
        return models::TokenSupplyModel::COLLAPSING;
    } else if (str == "ANNUAL_VALUE") {
        return models::TokenSupplyModel::ANNUAL_VALUE;
    } else if (str == "ANNUAL_PERCENTAGE") {
        return models::TokenSupplyModel::ANNUAL_PERCENTAGE;
    }

    return models::TokenSupplyModel::UNKNOWN;
}

enjin::sdk::models::TokenTransferFeeType deserialize_token_transfer_fee_type(const std::string& s) noexcept {
    std::string str = to_upper(s);
    if (str == "NONE") {
        return models::TokenTransferFeeType::NONE;
    } else if (str == "PER_TRANSFER") {
        return models::TokenTransferFeeType::PER_TRANSFER;
    } else if (str == "PER_CRYPTO_ITEM") {
        return models::TokenTransferFeeType::PER_CRYPTO_ITEM;
    } else if (str == "RATIO_CUT") {
        return models::TokenTransferFeeType::RATIO_CUT;
    } else if (str == "RATIO_EXTRA") {
        return models::TokenTransferFeeType::RATIO_EXTRA;
    }

    return models::TokenTransferFeeType::UNKNOWN;
}

enjin::sdk::models::TokenTransferable deserialize_token_transferable(const std::string& s) noexcept {
    std::string str = to_upper(s);
    if (str == "PERMANENT") {
        return models::TokenTransferable::PERMANENT;
    } else if (str == "TEMPORARY") {
        return models::TokenTransferable::TEMPORARY;
    } else if (str == "BOUND") {
        return models::TokenTransferable::BOUND;
    }

    return models::TokenTransferable::UNKNOWN;
}

enjin::sdk::models::TokenVariantMode deserialize_token_variant_mode(const std::string& s) noexcept {
    std::string str = to_upper(s);
    if (str == "NONE") {
        return models::TokenVariantMode::NONE;
    } else if (str == "BEAM") {
        return models::TokenVariantMode::BEAM;
    } else if (str == "ONCE") {
        return models::TokenVariantMode::ONCE;
    } else if (str == "ALWAYS") {
        return models::TokenVariantMode::ALWAYS;
    }

    return models::TokenVariantMode::UNKNOWN;
}

}
