#include "EnumUtils.hpp"
#include "StringUtils.hpp"

namespace enjin::sdk::utils {

enjin::sdk::models::RequestState deserialize_request_state(const std::string& s) noexcept {
    std::string str = to_upper(s);
    if (str == "PENDING") {
        return models::RequestState::PENDING;
    } else if (str == "BROADCAST") {
        return models::RequestState::BROADCAST;
    } else if (str == "TP_PROCESSING") {
        return models::RequestState::TP_PROCESSING;
    } else if (str == "EXECUTED") {
        return models::RequestState::EXECUTED;
    } else if (str == "CANCELED_USER") {
        return models::RequestState::CANCELED_USER;
    } else if (str == "CANCELED_PLATFORM") {
        return models::RequestState::CANCELED_PLATFORM;
    } else if (str == "DROPPED") {
        return models::RequestState::DROPPED;
    } else if (str == "FAILED") {
        return models::RequestState::FAILED;
    }

    return models::RequestState::UNKNOWN;
}

enjin::sdk::models::RequestType deserialize_request_type(const std::string& s) noexcept {
    std::string str = to_upper(s);
    if (str == "APPROVE") {
        return models::RequestType::APPROVE;
    } else if (str == "CREATE") {
        return models::RequestType::CREATE;
    } else if (str == "MINT") {
        return models::RequestType::MINT;
    } else if (str == "SEND") {
        return models::RequestType::SEND;
    } else if (str == "SEND_ENJ") {
        return models::RequestType::SEND_ENJ;
    } else if (str == "ADVANCED_SEND") {
        return models::RequestType::ADVANCED_SEND;
    } else if (str == "CREATE_TRADE") {
        return models::RequestType::CREATE_TRADE;
    } else if (str == "CANCEL_TRADE") {
        return models::RequestType::CANCEL_TRADE;
    } else if (str == "MELT") {
        return models::RequestType::MELT;
    } else if (str == "UPDATE_NAME") {
        return models::RequestType::UPDATE_NAME;
    } else if (str == "SET_ITEM_URI") {
        return models::RequestType::SET_ITEM_URI;
    } else if (str == "SET_WHITELISTED") {
        return models::RequestType::SET_WHITELISTED;
    } else if (str == "SET_TRANSFERABLE") {
        return models::RequestType::SET_TRANSFERABLE;
    } else if (str == "SET_MELT_FEE") {
        return models::RequestType::SET_MELT_FEE;
    } else if (str == "DECREASE_MAX_MELT_FEE") {
        return models::RequestType::DECREASE_MAX_MELT_FEE;
    } else if (str == "SET_TRANSFER_FEE") {
        return models::RequestType::SET_TRANSFER_FEE;
    } else if (str == "DECREASE_MAX_TRANSFER_FEE") {
        return models::RequestType::DECREASE_MAX_TRANSFER_FEE;
    } else if (str == "RELEASE_RESERVE") {
        return models::RequestType::RELEASE_RESERVE;
    } else if (str == "ADD_LOG") {
        return models::RequestType::ADD_LOG;
    } else if (str == "SET_APPROVAL_FOR_ALL") {
        return models::RequestType::SET_APPROVAL_FOR_ALL;
    } else if (str == "MANAGE_UPDATE") {
        return models::RequestType::MANAGE_UPDATE;
    } else if (str == "SET_DECIMALS") {
        return models::RequestType::SET_DECIMALS;
    } else if (str == "SET_SYMBOL") {
        return models::RequestType::SET_SYMBOL;
    } else if (str == "MESSAGE") {
        return models::RequestType::MESSAGE;
    }

    return models::RequestType::UNKNOWN;
}

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
