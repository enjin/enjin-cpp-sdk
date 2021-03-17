#include "EnumUtils.hpp"

#include "StringUtils.hpp"

namespace enjin::sdk::utils {

enjin::sdk::models::EventType deserialize_event_type(const std::string& s) noexcept {
    std::string str = to_upper(s);
    if (str == "PROJECT_CREATED") {
        return models::EventType::PROJECT_CREATED;
    } else if (str == "PROJECT_DELETED") {
        return models::EventType::PROJECT_DELETED;
    } else if (str == "PROJECT_LINKED") {
        return models::EventType::PROJECT_LINKED;
    } else if (str == "PROJECT_LOCKED") {
        return models::EventType::PROJECT_LOCKED;
    } else if (str == "PROJECT_UNLINKED") {
        return models::EventType::PROJECT_UNLINKED;
    } else if (str == "PROJECT_UNLOCKED") {
        return models::EventType::PROJECT_UNLOCKED;
    } else if (str == "PROJECT_UPDATED") {
        return models::EventType::PROJECT_UPDATED;
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
    } else if (str == "ASSET_CREATED") {
        return models::EventType::ASSET_CREATED;
    } else if (str == "ASSET_MELTED") {
        return models::EventType::ASSET_MELTED;
    } else if (str == "ASSET_MINTED") {
        return models::EventType::ASSET_MINTED;
    } else if (str == "ASSET_TRANSFERRED") {
        return models::EventType::ASSET_TRANSFERRED;
    } else if (str == "ASSET_UPDATED") {
        return models::EventType::ASSET_UPDATED;
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

enjin::sdk::models::AssetSupplyModel deserialize_asset_supply_model(const std::string& s) noexcept {
    std::string str = to_upper(s);
    if (str == "FIXED") {
        return models::AssetSupplyModel::FIXED;
    } else if (str == "SETTABLE") {
        return models::AssetSupplyModel::SETTABLE;
    } else if (str == "INFINITE") {
        return models::AssetSupplyModel::INFINITE;
    } else if (str == "COLLAPSING") {
        return models::AssetSupplyModel::COLLAPSING;
    } else if (str == "ANNUAL_VALUE") {
        return models::AssetSupplyModel::ANNUAL_VALUE;
    } else if (str == "ANNUAL_PERCENTAGE") {
        return models::AssetSupplyModel::ANNUAL_PERCENTAGE;
    }

    return models::AssetSupplyModel::UNKNOWN;
}

enjin::sdk::models::AssetTransferFeeType deserialize_asset_transfer_fee_type(const std::string& s) noexcept {
    std::string str = to_upper(s);
    if (str == "NONE") {
        return models::AssetTransferFeeType::NONE;
    } else if (str == "PER_TRANSFER") {
        return models::AssetTransferFeeType::PER_TRANSFER;
    } else if (str == "PER_CRYPTO_ITEM") {
        return models::AssetTransferFeeType::PER_CRYPTO_ITEM;
    } else if (str == "RATIO_CUT") {
        return models::AssetTransferFeeType::RATIO_CUT;
    } else if (str == "RATIO_EXTRA") {
        return models::AssetTransferFeeType::RATIO_EXTRA;
    }

    return models::AssetTransferFeeType::UNKNOWN;
}

enjin::sdk::models::AssetTransferable deserialize_asset_transferable(const std::string& s) noexcept {
    std::string str = to_upper(s);
    if (str == "PERMANENT") {
        return models::AssetTransferable::PERMANENT;
    } else if (str == "TEMPORARY") {
        return models::AssetTransferable::TEMPORARY;
    } else if (str == "BOUND") {
        return models::AssetTransferable::BOUND;
    }

    return models::AssetTransferable::UNKNOWN;
}

enjin::sdk::models::AssetVariantMode deserialize_asset_variant_mode(const std::string& s) noexcept {
    std::string str = to_upper(s);
    if (str == "NONE") {
        return models::AssetVariantMode::NONE;
    } else if (str == "BEAM") {
        return models::AssetVariantMode::BEAM;
    } else if (str == "ONCE") {
        return models::AssetVariantMode::ONCE;
    } else if (str == "ALWAYS") {
        return models::AssetVariantMode::ALWAYS;
    }

    return models::AssetVariantMode::UNKNOWN;
}

std::string serialize_event_type(models::EventType v) noexcept {
    switch (v) {
        case models::EventType::PROJECT_CREATED:
            return "PROJECT_CREATED";
        case models::EventType::PROJECT_DELETED:
            return "PROJECT_DELETED";
        case models::EventType::PROJECT_LINKED:
            return "PROJECT_LINKED";
        case models::EventType::PROJECT_LOCKED:
            return "PROJECT_LOCKED";
        case models::EventType::PROJECT_UNLINKED:
            return "PROJECT_UNLINKED";
        case models::EventType::PROJECT_UNLOCKED:
            return "PROJECT_UNLOCKED";
        case models::EventType::PROJECT_UPDATED:
            return "PROJECT_UPDATED";
        case models::EventType::BLOCKCHAIN_LOG_PROCESSED:
            return "BLOCKCHAIN_LOG_PROCESSED";
        case models::EventType::MESSAGE_PROCESSED:
            return "MESSAGE_PROCESSED";
        case models::EventType::PLAYER_CREATED:
            return "PLAYER_CREATED";
        case models::EventType::PLAYER_DELETED:
            return "PLAYER_DELETED";
        case models::EventType::PLAYER_LINKED:
            return "PLAYER_LINKED";
        case models::EventType::PLAYER_UNLINKED:
            return "PLAYER_UNLINKED";
        case models::EventType::PLAYER_UPDATED:
            return "PLAYER_UPDATED";
        case models::EventType::ASSET_CREATED:
            return "ASSET_CREATED";
        case models::EventType::ASSET_MELTED:
            return "ASSET_MELTED";
        case models::EventType::ASSET_MINTED:
            return "ASSET_MINTED";
        case models::EventType::ASSET_TRANSFERRED:
            return "ASSET_TRANSFERRED";
        case models::EventType::ASSET_UPDATED:
            return "ASSET_UPDATED";
        case models::EventType::TRADE_COMPLETED:
            return "TRADE_COMPLETED";
        case models::EventType::TRADE_CREATED:
            return "TRADE_CREATED";
        case models::EventType::TRANSACTION_BROADCAST:
            return "TRANSACTION_BROADCAST";
        case models::EventType::TRANSACTION_CANCELED:
            return "TRANSACTION_CANCELED";
        case models::EventType::TRANSACTION_DROPPED:
            return "TRANSACTION_DROPPED";
        case models::EventType::TRANSACTION_EXECUTED:
            return "TRANSACTION_EXECUTED";
        case models::EventType::TRANSACTION_FAILED:
            return "TRANSACTION_FAILED";
        case models::EventType::TRANSACTION_PENDING:
            return "TRANSACTION_PENDING";
        case models::EventType::TRANSACTION_PROCESSING:
            return "TRANSACTION_PROCESSING";
        case models::EventType::TRANSACTION_UPDATED:
            return "TRANSACTION_UPDATED";
        default:
            return "";
    }
}

std::string serialize_pusher_connection_state(pusher::ConnectionState v) noexcept {
    switch (v) {
        case pusher::ConnectionState::ALL:
            return "ALL";
        case pusher::ConnectionState::CONNECTING:
            return "CONNECTING";
        case pusher::ConnectionState::CONNECTED:
            return "CONNECTED";
        case pusher::ConnectionState::DISCONNECTED:
            return "DISCONNECTED";
        case pusher::ConnectionState::DISCONNECTING:
            return "DISCONNECTING";
        case pusher::ConnectionState::RECONNECTING:
            return "RECONNECTING";
        default:
            return "";
    }
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

std::string serialize_asset_field(enjin::sdk::models::AssetField v) noexcept {
    switch (v) {
        case models::AssetField::ID:
            return "id";
        case models::AssetField::NAME:
            return "name";
        case models::AssetField::CIRCULATING_SUPPLY:
            return "circulatingSupply";
        case models::AssetField::NON_FUNGIBLE:
            return "nonFungible";
        case models::AssetField::RESERVE:
            return "reserve";
        case models::AssetField::TOTAL_SUPPLY:
            return "totalSupply";
        case models::AssetField::CREATED_AT:
            return "createdAt";
        default:
            return "";
    }
}

std::string serialize_asset_id_format(enjin::sdk::models::AssetIdFormat v) noexcept {
    switch (v) {
        case models::AssetIdFormat::HEX64:
            return "hex64";
        case models::AssetIdFormat::HEX256:
            return "hex256";
        case models::AssetIdFormat::UINT256:
            return "uint256";
        default:
            return "";
    }
}

std::string serialize_asset_index_format(enjin::sdk::models::AssetIndexFormat v) noexcept {
    switch (v) {
        case models::AssetIndexFormat::HEX64:
            return "hex64";
        case models::AssetIndexFormat::UINT64:
            return "uint64";
        default:
            return "";
    }
}

std::string serialize_asset_supply_model(enjin::sdk::models::AssetSupplyModel v) noexcept {
    switch (v) {
        case models::AssetSupplyModel::FIXED:
            return "FIXED";
        case models::AssetSupplyModel::SETTABLE:
            return "SETTABLE";
        case models::AssetSupplyModel::INFINITE:
            return "INFINITE";
        case models::AssetSupplyModel::COLLAPSING:
            return "COLLAPSING";
        case models::AssetSupplyModel::ANNUAL_VALUE:
            return "ANNUAL_VALUE";
        case models::AssetSupplyModel::ANNUAL_PERCENTAGE:
            return "ANNUAL_PERCENTAGE";
        default:
            return "UNKNOWN";
    }
}

std::string serialize_asset_transfer_fee_type(enjin::sdk::models::AssetTransferFeeType v) noexcept {
    switch (v) {
        case models::AssetTransferFeeType::NONE:
            return "NONE";
        case models::AssetTransferFeeType::PER_TRANSFER:
            return "PER_TRANSFER";
        case models::AssetTransferFeeType::PER_CRYPTO_ITEM:
            return "PER_CRYPTO_ITEM";
        case models::AssetTransferFeeType::RATIO_CUT:
            return "RATIO_CUT";
        case models::AssetTransferFeeType::RATIO_EXTRA:
            return "RATIO_EXTRA";
        default:
            return "UNKNOWN";
    }
}

std::string serialize_asset_transferable(enjin::sdk::models::AssetTransferable v) noexcept {
    switch (v) {
        case models::AssetTransferable::PERMANENT:
            return "PERMANENT";
        case models::AssetTransferable::TEMPORARY:
            return "TEMPORARY";
        case models::AssetTransferable::BOUND:
            return "BOUND";
        default:
            return "UNKNOWN";
    }
}

std::string serialize_asset_variant_mode(enjin::sdk::models::AssetVariantMode v) noexcept {
    switch (v) {
        case models::AssetVariantMode::NONE:
            return "NONE";
        case models::AssetVariantMode::BEAM:
            return "BEAM";
        case models::AssetVariantMode::ONCE:
            return "ONCE";
        case models::AssetVariantMode::ALWAYS:
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
