#ifndef ENJINCPPSDK_ENUMUTILS_HPP
#define ENJINCPPSDK_ENUMUTILS_HPP

#include "enjinsdk/models/RequestState.hpp"
#include "enjinsdk/models/RequestType.hpp"
#include "enjinsdk/models/TokenSupplyModel.hpp"
#include "enjinsdk/models/TokenTransferFeeType.hpp"
#include "enjinsdk/models/TokenTransferable.hpp"
#include "enjinsdk/models/TokenVariantMode.hpp"
#include <string>

namespace enjin::sdk::utils {

enjin::sdk::models::RequestState deserialize_request_state(const std::string& s) noexcept;

enjin::sdk::models::RequestType deserialize_request_type(const std::string& s) noexcept;

enjin::sdk::models::TokenSupplyModel deserialize_token_supply_model(const std::string& s) noexcept;

enjin::sdk::models::TokenTransferFeeType deserialize_token_transfer_fee_type(const std::string& s) noexcept;

enjin::sdk::models::TokenTransferable deserialize_token_transferable(const std::string& s) noexcept;

enjin::sdk::models::TokenVariantMode deserialize_token_variant_mode(const std::string& s) noexcept;

constexpr std::string_view serialize_request_state(enjin::sdk::models::RequestState v) noexcept {
    switch (v) {
        case models::RequestState::PENDING:
            return "PENDING";
        case models::RequestState::BROADCAST:
            return "BROADCAST";
        case models::RequestState::TP_PROCESSING:
            return "TP_PROCESSING";
        case models::RequestState::EXECUTED:
            return "EXECUTED";
        case models::RequestState::CANCELED_USER:
            return "CANCELED_USER";
        case models::RequestState::CANCELED_PLATFORM:
            return "CANCELED_PLATFORM";
        case models::RequestState::DROPPED:
            return "DROPPED";
        case models::RequestState::FAILED:
            return "FAILED";
        default:
            return "";
    }
}

constexpr std::string_view serialize_request_type(enjin::sdk::models::RequestType v) noexcept {
    switch (v) {
        case models::RequestType::APPROVE:
            return "APPROVE";
        case models::RequestType::CREATE:
            return "CREATE";
        case models::RequestType::MINT:
            return "MINT";
        case models::RequestType::SEND:
            return "SEND";
        case models::RequestType::SEND_ENJ:
            return "SEND_ENJ";
        case models::RequestType::ADVANCED_SEND:
            return "ADVANCED_SEND";
        case models::RequestType::CREATE_TRADE:
            return "CREATE_TRADE";
        case models::RequestType::CANCEL_TRADE:
            return "CANCEL_TRADE";
        case models::RequestType::MELT:
            return "MELT";
        case models::RequestType::UPDATE_NAME:
            return "UPDATE_NAME";
        case models::RequestType::SET_ITEM_URI:
            return "SET_ITEM_URI";
        case models::RequestType::SET_WHITELISTED:
            return "SET_WHITELISTED";
        case models::RequestType::SET_TRANSFERABLE:
            return "SET_TRANSFERABLE";
        case models::RequestType::SET_MELT_FEE:
            return "SET_MELT_FEE";
        case models::RequestType::DECREASE_MAX_MELT_FEE:
            return "DECREASE_MAX_MELT_FEE";
        case models::RequestType::SET_TRANSFER_FEE:
            return "SET_TRANSFER_FEE";
        case models::RequestType::DECREASE_MAX_TRANSFER_FEE:
            return "DECREASE_MAX_TRANSFER_FEE";
        case models::RequestType::RELEASE_RESERVE:
            return "RELEASE_RESERVE";
        case models::RequestType::ADD_LOG:
            return "ADD_LOG";
        case models::RequestType::SET_APPROVAL_FOR_ALL:
            return "SET_APPROVAL_FOR_ALL";
        case models::RequestType::MANAGE_UPDATE:
            return "MANAGE_UPDATE";
        case models::RequestType::SET_DECIMALS:
            return "SET_DECIMALS";
        case models::RequestType::SET_SYMBOL:
            return "SET_SYMBOL";
        case models::RequestType::MESSAGE:
            return "MESSAGE";
        default:
            return "";
    }
}

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
