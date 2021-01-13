#ifndef ENJINCPPSDK_ENUMUTILS_HPP
#define ENJINCPPSDK_ENUMUTILS_HPP

#include "enjinsdk/models/TokenSupplyModel.hpp"
#include "enjinsdk/models/TokenTransferFeeType.hpp"
#include "enjinsdk/models/TokenTransferable.hpp"
#include "enjinsdk/models/TokenVariantMode.hpp"
#include <string>

namespace enjin::sdk::utils {

enjin::sdk::models::TokenSupplyModel deserialize_token_supply_model(const std::string& s) noexcept;

enjin::sdk::models::TokenTransferFeeType deserialize_token_transfer_fee_type(const std::string& s) noexcept;

enjin::sdk::models::TokenTransferable deserialize_token_transferable(const std::string& s) noexcept;

enjin::sdk::models::TokenVariantMode deserialize_token_variant_mode(const std::string& s) noexcept;

constexpr std::string_view serialize_token_supply_model(enjin::sdk::models::TokenSupplyModel v) noexcept {
    switch (v) {
        case models::TokenSupplyModel::FIXED:
            return "FIXED";
        case models::TokenSupplyModel::SETTABLE:
            return "SETTABLE";
        case models::TokenSupplyModel::INFINITE:
            return "INFINITE";
        case models::TokenSupplyModel::COLLAPSING:
            return "COLLAPSING";
        case models::TokenSupplyModel::ANNUAL_VALUE:
            return "ANNUAL_VALUE";
        case models::TokenSupplyModel::ANNUAL_PERCENTAGE:
            return "ANNUAL_PERCENTAGE";
        default:
            return "UNKNOWN";
    }
}

constexpr std::string_view serialize_token_transfer_fee_type(enjin::sdk::models::TokenTransferFeeType v) noexcept {
    switch (v) {
        case models::TokenTransferFeeType::NONE:
            return "NONE";
        case models::TokenTransferFeeType::PER_TRANSFER:
            return "PER_TRANSFER";
        case models::TokenTransferFeeType::PER_CRYPTO_ITEM:
            return "PER_CRYPTO_ITEM";
        case models::TokenTransferFeeType::RATIO_CUT:
            return "RATIO_CUT";
        case models::TokenTransferFeeType::RATIO_EXTRA:
            return "RATIO_EXTRA";
        default:
            return "UNKNOWN";
    }
}

constexpr std::string_view serialize_token_transferable(enjin::sdk::models::TokenTransferable v) noexcept {
    switch (v) {
        case models::TokenTransferable::PERMANENT:
            return "PERMANENT";
        case models::TokenTransferable::TEMPORARY:
            return "TEMPORARY";
        case models::TokenTransferable::BOUND:
            return "BOUND";
        default:
            return "UNKNOWN";
    }
}

constexpr std::string_view serialize_token_variant_mode(enjin::sdk::models::TokenVariantMode v) noexcept {
    switch (v) {
        case models::TokenVariantMode::NONE:
            return "NONE";
        case models::TokenVariantMode::BEAM:
            return "BEAM";
        case models::TokenVariantMode::ONCE:
            return "ONCE";
        case models::TokenVariantMode::ALWAYS:
            return "ALWAYS";
        default:
            return "UNKNOWN";
    }
}

}

#endif //ENJINCPPSDK_ENUMUTILS_HPP
