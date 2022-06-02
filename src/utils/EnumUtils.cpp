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

#include "EnumUtils.hpp"

#include "enjinsdk_utils/StringUtils.hpp"
#include <stdexcept>

namespace enjin::sdk::utils {

models::EventType deserialize_event_type(const std::string& s) noexcept {
    std::string str = enjin::utils::to_upper(s);
    if (str == "PROJECT_CREATED") {
        return models::EventType::ProjectCreated;
    } else if (str == "PROJECT_DELETED") {
        return models::EventType::ProjectDeleted;
    } else if (str == "PROJECT_LINKED") {
        return models::EventType::ProjectLinked;
    } else if (str == "PROJECT_LOCKED") {
        return models::EventType::ProjectLocked;
    } else if (str == "PROJECT_UNLINKED") {
        return models::EventType::ProjectUnlinked;
    } else if (str == "PROJECT_UNLOCKED") {
        return models::EventType::ProjectUnlocked;
    } else if (str == "PROJECT_UPDATED") {
        return models::EventType::ProjectUpdated;
    } else if (str == "BLOCKCHAIN_LOG_PROCESSED") {
        return models::EventType::BlockchainLogProcessed;
    } else if (str == "MESSAGE_PROCESSED") {
        return models::EventType::MessageProcessed;
    } else if (str == "PLAYER_CREATED") {
        return models::EventType::PlayerCreated;
    } else if (str == "PLAYER_DELETED") {
        return models::EventType::PlayerDeleted;
    } else if (str == "PLAYER_LINKED") {
        return models::EventType::PlayerLinked;
    } else if (str == "PLAYER_UNLINKED") {
        return models::EventType::PlayerUnlinked;
    } else if (str == "PLAYER_UPDATED") {
        return models::EventType::PlayerUpdated;
    } else if (str == "ASSET_CREATED") {
        return models::EventType::AssetCreated;
    } else if (str == "ASSET_MELTED") {
        return models::EventType::AssetMelted;
    } else if (str == "ASSET_MINTED") {
        return models::EventType::AssetMinted;
    } else if (str == "ASSET_TRANSFERRED") {
        return models::EventType::AssetTransferred;
    } else if (str == "ASSET_UPDATED") {
        return models::EventType::AssetUpdated;
    } else if (str == "TRADE_ASSET_COMPLETED") {
        return models::EventType::TradeAssetCompleted;
    } else if (str == "TRADE_ASSET_CREATED") {
        return models::EventType::TradeAssetCreated;
    } else if (str == "TRANSACTION_BROADCAST") {
        return models::EventType::TransactionBroadcast;
    } else if (str == "TRANSACTION_CANCELED") {
        return models::EventType::TransactionCanceled;
    } else if (str == "TRANSACTION_DROPPED") {
        return models::EventType::TransactionDropped;
    } else if (str == "TRANSACTION_EXECUTED") {
        return models::EventType::TransactionExecuted;
    } else if (str == "TRANSACTION_FAILED") {
        return models::EventType::TransactionFailed;
    } else if (str == "TRANSACTION_PENDING") {
        return models::EventType::TransactionPending;
    } else if (str == "TRANSACTION_PROCESSING") {
        return models::EventType::TransactionProcessing;
    } else if (str == "TRANSACTION_UPDATED") {
        return models::EventType::TransactionUpdated;
    }

    return models::EventType::Unknown;
}

models::RequestState deserialize_request_state(const std::string& s) noexcept {
    std::string str = enjin::utils::to_upper(s);
    if (str == "PENDING") {
        return models::RequestState::Pending;
    } else if (str == "BROADCAST") {
        return models::RequestState::Broadcast;
    } else if (str == "TP_PROCESSING") {
        return models::RequestState::TpProcessing;
    } else if (str == "EXECUTED") {
        return models::RequestState::Executed;
    } else if (str == "CANCELED_USER") {
        return models::RequestState::CanceledUser;
    } else if (str == "CANCELED_PLATFORM") {
        return models::RequestState::CanceledPlatform;
    } else if (str == "DROPPED") {
        return models::RequestState::Dropped;
    } else if (str == "FAILED") {
        return models::RequestState::Failed;
    }

    return models::RequestState::Unknown;
}

models::RequestType deserialize_request_type(const std::string& s) noexcept {
    std::string str = enjin::utils::to_upper(s);
    if (str == "ACCEPT_ASSIGNMENT") {
        return models::RequestType::ACCEPT_ASSIGNMENT;
    } else if (str == "ASSIGN") {
        return models::RequestType::ASSIGN;
    } else if (str == "APPROVE") {
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

models::AssetSupplyModel deserialize_asset_supply_model(const std::string& s) noexcept {
    std::string str = enjin::utils::to_upper(s);
    if (str == "FIXED") {
        return models::AssetSupplyModel::Fixed;
    } else if (str == "SETTABLE") {
        return models::AssetSupplyModel::Settable;
    } else if (str == "INFINITE") {
        return models::AssetSupplyModel::Infinite;
    } else if (str == "COLLAPSING") {
        return models::AssetSupplyModel::Collapsing;
    } else if (str == "ANNUAL_VALUE") {
        return models::AssetSupplyModel::AnnualValue;
    } else if (str == "ANNUAL_PERCENTAGE") {
        return models::AssetSupplyModel::AnnualPercentage;
    }

    return models::AssetSupplyModel::Unknown;
}

models::AssetTransferFeeType deserialize_asset_transfer_fee_type(const std::string& s) noexcept {
    std::string str = enjin::utils::to_upper(s);
    if (str == "NONE") {
        return models::AssetTransferFeeType::None;
    } else if (str == "PER_TRANSFER") {
        return models::AssetTransferFeeType::PerTransfer;
    } else if (str == "PER_CRYPTO_ITEM") {
        return models::AssetTransferFeeType::PerCryptoItem;
    } else if (str == "RATIO_CUT") {
        return models::AssetTransferFeeType::RatioCut;
    } else if (str == "RATIO_EXTRA") {
        return models::AssetTransferFeeType::RatioExtra;
    }

    return models::AssetTransferFeeType::Unknown;
}

models::AssetTransferable deserialize_asset_transferable(const std::string& s) noexcept {
    std::string str = enjin::utils::to_upper(s);
    if (str == "PERMANENT") {
        return models::AssetTransferable::Permanent;
    } else if (str == "TEMPORARY") {
        return models::AssetTransferable::Temporary;
    } else if (str == "BOUND") {
        return models::AssetTransferable::Bound;
    }

    return models::AssetTransferable::Unknown;
}

models::AssetVariantMode deserialize_asset_variant_mode(const std::string& s) noexcept {
    std::string str = enjin::utils::to_upper(s);
    if (str == "NONE") {
        return models::AssetVariantMode::None;
    } else if (str == "BEAM") {
        return models::AssetVariantMode::Beam;
    } else if (str == "ONCE") {
        return models::AssetVariantMode::Once;
    } else if (str == "ALWAYS") {
        return models::AssetVariantMode::Always;
    }

    return models::AssetVariantMode::Unknown;
}

http::HttpMethod deserialize_http_method(const std::string& s) {
    std::string str = enjin::utils::to_upper(s);
    if (str == "GET") {
        return http::HttpMethod::GET;
    } else if (str == "HEAD") {
        return http::HttpMethod::HEAD;
    } else if (str == "POST") {
        return http::HttpMethod::POST;
    } else if (str == "PUT") {
        return http::HttpMethod::PUT;
    } else if (str == "DELETE") {
        return http::HttpMethod::DEL;
    } else if (str == "CONNECT") {
        return http::HttpMethod::CONNECT;
    } else if (str == "OPTIONS") {
        return http::HttpMethod::OPTIONS;
    } else if (str == "TRACE") {
        return http::HttpMethod::TRACE;
    } else if (str == "PATCH") {
        return http::HttpMethod::PATCH;
    }

    throw std::runtime_error("No valid conversion for " + s + " to HTTP method.");
}

std::string serialize_event_type(models::EventType v) noexcept {
    switch (v) {
        case models::EventType::ProjectCreated:
            return "PROJECT_CREATED";
        case models::EventType::ProjectDeleted:
            return "PROJECT_DELETED";
        case models::EventType::ProjectLinked:
            return "PROJECT_LINKED";
        case models::EventType::ProjectLocked:
            return "PROJECT_LOCKED";
        case models::EventType::ProjectUnlinked:
            return "PROJECT_UNLINKED";
        case models::EventType::ProjectUnlocked:
            return "PROJECT_UNLOCKED";
        case models::EventType::ProjectUpdated:
            return "PROJECT_UPDATED";
        case models::EventType::BlockchainLogProcessed:
            return "BLOCKCHAIN_LOG_PROCESSED";
        case models::EventType::MessageProcessed:
            return "MESSAGE_PROCESSED";
        case models::EventType::PlayerCreated:
            return "PLAYER_CREATED";
        case models::EventType::PlayerDeleted:
            return "PLAYER_DELETED";
        case models::EventType::PlayerLinked:
            return "PLAYER_LINKED";
        case models::EventType::PlayerUnlinked:
            return "PLAYER_UNLINKED";
        case models::EventType::PlayerUpdated:
            return "PLAYER_UPDATED";
        case models::EventType::AssetCreated:
            return "ASSET_CREATED";
        case models::EventType::AssetMelted:
            return "ASSET_MELTED";
        case models::EventType::AssetMinted:
            return "ASSET_MINTED";
        case models::EventType::AssetTransferred:
            return "ASSET_TRANSFERRED";
        case models::EventType::AssetUpdated:
            return "ASSET_UPDATED";
        case models::EventType::TradeAssetCompleted:
            return "TRADE_ASSET_COMPLETED";
        case models::EventType::TradeAssetCreated:
            return "TRADE_ASSET_CREATED";
        case models::EventType::TransactionBroadcast:
            return "TRANSACTION_BROADCAST";
        case models::EventType::TransactionCanceled:
            return "TRANSACTION_CANCELED";
        case models::EventType::TransactionDropped:
            return "TRANSACTION_DROPPED";
        case models::EventType::TransactionExecuted:
            return "TRANSACTION_EXECUTED";
        case models::EventType::TransactionFailed:
            return "TRANSACTION_FAILED";
        case models::EventType::TransactionPending:
            return "TRANSACTION_PENDING";
        case models::EventType::TransactionProcessing:
            return "TRANSACTION_PROCESSING";
        case models::EventType::TransactionUpdated:
            return "TRANSACTION_UPDATED";
        default:
            return "";
    }
}

std::string serialize_pusher_connection_state(pusher::PusherConnectionState v) noexcept {
    switch (v) {
        case pusher::PusherConnectionState::ALL:
            return "ALL";
        case pusher::PusherConnectionState::CONNECTING:
            return "CONNECTING";
        case pusher::PusherConnectionState::CONNECTED:
            return "CONNECTED";
        case pusher::PusherConnectionState::DISCONNECTED:
            return "DISCONNECTED";
        case pusher::PusherConnectionState::DISCONNECTING:
            return "DISCONNECTING";
        case pusher::PusherConnectionState::RECONNECTING:
            return "RECONNECTING";
        default:
            return "";
    }
}

std::string serialize_request_state(models::RequestState v) noexcept {
    switch (v) {
        case models::RequestState::Pending:
            return "PENDING";
        case models::RequestState::Broadcast:
            return "BROADCAST";
        case models::RequestState::TpProcessing:
            return "TP_PROCESSING";
        case models::RequestState::Executed:
            return "EXECUTED";
        case models::RequestState::CanceledUser:
            return "CANCELED_USER";
        case models::RequestState::CanceledPlatform:
            return "CANCELED_PLATFORM";
        case models::RequestState::Dropped:
            return "DROPPED";
        case models::RequestState::Failed:
            return "FAILED";
        default:
            return "";
    }
}

std::string serialize_request_type(models::RequestType v) noexcept {
    switch (v) {
        case models::RequestType::ACCEPT_ASSIGNMENT:
            return "ACCEPT_ASSIGNMENT";
        case models::RequestType::ASSIGN:
            return "ASSIGN";
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

std::string serialize_sort_direction(models::SortDirection v) noexcept {
    switch (v) {
        case models::SortDirection::ASCENDING:
            return "asc";
        case models::SortDirection::DESCENDING:
            return "desc";
        default:
            return "";
    }
}

std::string serialize_asset_field(models::AssetField v) noexcept {
    switch (v) {
        case models::AssetField::Id:
            return "id";
        case models::AssetField::Name:
            return "name";
        case models::AssetField::CirculatingSupply:
            return "circulatingSupply";
        case models::AssetField::NonFungible:
            return "nonFungible";
        case models::AssetField::Reserve:
            return "reserve";
        case models::AssetField::TotalSupply:
            return "totalSupply";
        case models::AssetField::CreatedAt:
            return "createdAt";
        default:
            return "";
    }
}

std::string serialize_asset_id_format(models::AssetIdFormat v) noexcept {
    switch (v) {
        case models::AssetIdFormat::Hex64:
            return "hex64";
        case models::AssetIdFormat::Hex256:
            return "hex256";
        case models::AssetIdFormat::Uint256:
            return "uint256";
        default:
            return "";
    }
}

std::string serialize_asset_index_format(models::AssetIndexFormat v) noexcept {
    switch (v) {
        case models::AssetIndexFormat::Hex64:
            return "hex64";
        case models::AssetIndexFormat::Uint64:
            return "uint64";
        default:
            return "";
    }
}

std::string serialize_asset_supply_model(models::AssetSupplyModel v) noexcept {
    switch (v) {
        case models::AssetSupplyModel::Fixed:
            return "FIXED";
        case models::AssetSupplyModel::Settable:
            return "SETTABLE";
        case models::AssetSupplyModel::Infinite:
            return "INFINITE";
        case models::AssetSupplyModel::Collapsing:
            return "COLLAPSING";
        case models::AssetSupplyModel::AnnualValue:
            return "ANNUAL_VALUE";
        case models::AssetSupplyModel::AnnualPercentage:
            return "ANNUAL_PERCENTAGE";
        default:
            return "UNKNOWN";
    }
}

std::string serialize_asset_transfer_fee_type(models::AssetTransferFeeType v) noexcept {
    switch (v) {
        case models::AssetTransferFeeType::None:
            return "NONE";
        case models::AssetTransferFeeType::PerTransfer:
            return "PER_TRANSFER";
        case models::AssetTransferFeeType::PerCryptoItem:
            return "PER_CRYPTO_ITEM";
        case models::AssetTransferFeeType::RatioCut:
            return "RATIO_CUT";
        case models::AssetTransferFeeType::RatioExtra:
            return "RATIO_EXTRA";
        default:
            return "UNKNOWN";
    }
}

std::string serialize_asset_transferable(models::AssetTransferable v) noexcept {
    switch (v) {
        case models::AssetTransferable::Permanent:
            return "PERMANENT";
        case models::AssetTransferable::Temporary:
            return "TEMPORARY";
        case models::AssetTransferable::Bound:
            return "BOUND";
        default:
            return "UNKNOWN";
    }
}

std::string serialize_asset_variant_mode(models::AssetVariantMode v) noexcept {
    switch (v) {
        case models::AssetVariantMode::None:
            return "NONE";
        case models::AssetVariantMode::Beam:
            return "BEAM";
        case models::AssetVariantMode::Once:
            return "ONCE";
        case models::AssetVariantMode::Always:
            return "ALWAYS";
        default:
            return "UNKNOWN";
    }
}

std::string serialize_http_method(http::HttpMethod v) noexcept {
    switch (v) {
        case http::HttpMethod::GET:
            return "GET";
        case http::HttpMethod::HEAD:
            return "HEAD";
        case http::HttpMethod::POST:
            return "POST";
        case http::HttpMethod::PUT:
            return "PUT";
        case http::HttpMethod::DEL:
            return "DELETE";
        case http::HttpMethod::CONNECT:
            return "CONNECT";
        case http::HttpMethod::OPTIONS:
            return "OPTIONS";
        case http::HttpMethod::TRACE:
            return "TRACE";
        case http::HttpMethod::PATCH:
            return "PATCH";
        default:
            return "";
    }
}

std::string serialize_operator(models::Operator v) noexcept {
    switch (v) {
        case models::Operator::GreaterThan:
            return "GREATER_THAN";
        case models::Operator::GreaterThanOrEqual:
            return "GREATER_THAN_OR_EQUAL";
        case models::Operator::LessThan:
            return "LESS_THAN";
        case models::Operator::LessThanOrEqual:
            return "LESS_THAN_OR_EQUAL";
        default:
            return "";
    }
}

std::string serialize_transaction_field(models::TransactionField v) noexcept {
    switch (v) {
        case models::TransactionField::ID:
            return "id";
        case models::TransactionField::STATE:
            return "state";
        case models::TransactionField::TITLE:
            return "title";
        case models::TransactionField::CREATED_AT:
            return "createdAt";
        case models::TransactionField::UPDATED_AT:
            return "updatedAt";
        default:
            return "";
    }
}

std::string serialize_whitelisted(models::Whitelisted v) noexcept {
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
