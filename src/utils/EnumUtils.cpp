#include "EnumUtils.hpp"

#include "StringUtils.hpp"

namespace enjin::sdk::utils {

enjin::sdk::models::EventType deserialize_event_type(const std::string& s) noexcept {
    std::string str = to_upper(s);
    if (str == "APP_CREATED") {
        return models::EventType::APP_CREATED;
    } else if (str == "APP_DELETED") {
        return models::EventType::APP_DELETED;
    } else if (str == "APP_LINKED") {
        return models::EventType::APP_LINKED;
    } else if (str == "APP_LOCKED") {
        return models::EventType::APP_LOCKED;
    } else if (str == "APP_UNLINKED") {
        return models::EventType::APP_UNLINKED;
    } else if (str == "APP_UNLOCKED") {
        return models::EventType::APP_UNLOCKED;
    } else if (str == "APP_UPDATED") {
        return models::EventType::APP_UPDATED;
    } else if (str == "BLOCKCHAIN_LOG_PROCESSED") {
        return models::EventType::BLOCKCHAIN_LOG_PROCESSED;
    } else if (str == "MESSAGE_PROCESSED") {
        return models::EventType::MESSAGE_PROCESSED;
    } else if (str == "PLAYER_CREATED") {
        return models::EventType::PLAYER_CREATED;
    } else if (str == "PLAYER_DELETED") {
        return models::EventType::PLAYER_DELETED;
    } else if (str == "PLAYER_LINKED") {
        return models::EventType::PLAYER_LINKED;
    } else if (str == "PLAYER_UNLINKED") {
        return models::EventType::PLAYER_UNLINKED;
    } else if (str == "PLAYER_UPDATED") {
        return models::EventType::PLAYER_UPDATED;
    } else if (str == "TOKEN_CREATED") {
        return models::EventType::TOKEN_CREATED;
    } else if (str == "TOKEN_MELTED") {
        return models::EventType::TOKEN_MELTED;
    } else if (str == "TOKEN_MINTED") {
        return models::EventType::TOKEN_MINTED;
    } else if (str == "TOKEN_TRANSFERRED") {
        return models::EventType::TOKEN_TRANSFERRED;
    } else if (str == "TOKEN_UPDATED") {
        return models::EventType::TOKEN_UPDATED;
    } else if (str == "TRADE_COMPLETED") {
        return models::EventType::TRADE_COMPLETED;
    } else if (str == "TRADE_CREATED") {
        return models::EventType::TRADE_CREATED;
    } else if (str == "TRANSACTION_BROADCAST") {
        return models::EventType::TRANSACTION_BROADCAST;
    } else if (str == "TRANSACTION_CANCELED") {
        return models::EventType::TRANSACTION_CANCELED;
    } else if (str == "TRANSACTION_DROPPED") {
        return models::EventType::TRANSACTION_DROPPED;
    } else if (str == "TRANSACTION_EXECUTED") {
        return models::EventType::TRANSACTION_EXECUTED;
    } else if (str == "TRANSACTION_FAILED") {
        return models::EventType::TRANSACTION_FAILED;
    } else if (str == "TRANSACTION_PENDING") {
        return models::EventType::TRANSACTION_PENDING;
    } else if (str == "TRANSACTION_PROCESSING") {
        return models::EventType::TRANSACTION_PROCESSING;
    } else if (str == "TRANSACTION_UPDATED") {
        return models::EventType::TRANSACTION_UPDATED;
    }

    return models::EventType::UNKNOWN;
}

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

std::string serialize_request_state(enjin::sdk::models::RequestState v) noexcept {
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

std::string serialize_request_type(enjin::sdk::models::RequestType v) noexcept {
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

std::string serialize_sort_direction(enjin::sdk::models::SortDirection v) noexcept {
    switch (v) {
        case models::SortDirection::ASCENDING:
            return "asc";
        case models::SortDirection::DESCENDING:
            return "desc";
        default:
            return "";
    }
}

std::string serialize_token_field(enjin::sdk::models::TokenField v) noexcept {
    switch (v) {
        case models::TokenField::ID:
            return "id";
        case models::TokenField::NAME:
            return "name";
        case models::TokenField::CIRCULATING_SUPPLY:
            return "circulatingSupply";
        case models::TokenField::NON_FUNGIBLE:
            return "nonFungible";
        case models::TokenField::RESERVE:
            return "reserve";
        case models::TokenField::TOTAL_SUPPLY:
            return "totalSupply";
        case models::TokenField::CREATED_AT:
            return "createdAt";
        default:
            return "";
    }
}

std::string serialize_token_id_format(enjin::sdk::models::TokenIdFormat v) noexcept {
    switch (v) {
        case models::TokenIdFormat::HEX64:
            return "hex64";
        case models::TokenIdFormat::HEX256:
            return "hex256";
        case models::TokenIdFormat::UINT256:
            return "uint256";
        default:
            return "";
    }
}

std::string serialize_token_index_format(enjin::sdk::models::TokenIndexFormat v) noexcept {
    switch (v) {
        case models::TokenIndexFormat::HEX64:
            return "hex64";
        case models::TokenIndexFormat::UINT64:
            return "uint64";
        default:
            return "";
    }
}

std::string serialize_token_supply_model(enjin::sdk::models::TokenSupplyModel v) noexcept {
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

std::string serialize_token_transfer_fee_type(enjin::sdk::models::TokenTransferFeeType v) noexcept {
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

std::string serialize_token_transferable(enjin::sdk::models::TokenTransferable v) noexcept {
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

std::string serialize_token_variant_mode(enjin::sdk::models::TokenVariantMode v) noexcept {
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

std::string serialize_transaction_field(enjin::sdk::models::TransactionField v) noexcept {
    switch (v) {
        case models::TransactionField::ID:
            return "id";
        case models::TransactionField::STATE:
            return "state";
        case models::TransactionField::TITLE:
            return "title";
        case models::TransactionField::CREATED_AT:
            return "createdAt";
        default:
            return "";
    }
}

std::string serialize_whitelisted(enjin::sdk::models::Whitelisted v) noexcept {
    switch (v) {
        case models::Whitelisted::NONE:
            return "NONE";
        case models::Whitelisted::SEND_AND_RECEIVE:
            return "SEND_AND_RECEIVE";
        case models::Whitelisted::SEND:
            return "SEND";
        case models::Whitelisted::RECEIVE:
            return "RECEIVE";
        case models::Whitelisted::NO_FEES:
            return "NO_FEES";
        case models::Whitelisted::ADDRESS:
            return "ADDRESS";
        default:
            return "";
    }
}

}
