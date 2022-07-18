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

#include "enjinsdk/EnumUtils.hpp"

#include "enjinsdk_utils/StringUtils.hpp"
#include <stdexcept>

/* The namespace for utilities from enjin::utils is used explicitly to avoid collision with enjin::sdk::utils with some
 * compilers.
 */
using namespace enjin::sdk::http;
using namespace enjin::sdk::models;
using namespace enjin::sdk::utils;

EventType EnumUtils::deserialize_event_type(const std::string& s) noexcept {
    std::string str = enjin::utils::to_upper(s);
    if (str == "PROJECT_CREATED") {
        return EventType::ProjectCreated;
    } else if (str == "PROJECT_DELETED") {
        return EventType::ProjectDeleted;
    } else if (str == "PROJECT_LINKED") {
        return EventType::ProjectLinked;
    } else if (str == "PROJECT_LOCKED") {
        return EventType::ProjectLocked;
    } else if (str == "PROJECT_UNLINKED") {
        return EventType::ProjectUnlinked;
    } else if (str == "PROJECT_UNLOCKED") {
        return EventType::ProjectUnlocked;
    } else if (str == "PROJECT_UPDATED") {
        return EventType::ProjectUpdated;
    } else if (str == "BLOCKCHAIN_LOG_PROCESSED") {
        return EventType::BlockchainLogProcessed;
    } else if (str == "MESSAGE_PROCESSED") {
        return EventType::MessageProcessed;
    } else if (str == "PLAYER_CREATED") {
        return EventType::PlayerCreated;
    } else if (str == "PLAYER_DELETED") {
        return EventType::PlayerDeleted;
    } else if (str == "PLAYER_LINKED") {
        return EventType::PlayerLinked;
    } else if (str == "PLAYER_UNLINKED") {
        return EventType::PlayerUnlinked;
    } else if (str == "PLAYER_UPDATED") {
        return EventType::PlayerUpdated;
    } else if (str == "ASSET_CREATED") {
        return EventType::AssetCreated;
    } else if (str == "ASSET_MELTED") {
        return EventType::AssetMelted;
    } else if (str == "ASSET_MINTED") {
        return EventType::AssetMinted;
    } else if (str == "ASSET_TRANSFERRED") {
        return EventType::AssetTransferred;
    } else if (str == "ASSET_UPDATED") {
        return EventType::AssetUpdated;
    } else if (str == "TRADE_ASSET_COMPLETED") {
        return EventType::TradeAssetCompleted;
    } else if (str == "TRADE_ASSET_CREATED") {
        return EventType::TradeAssetCreated;
    } else if (str == "TRANSACTION_BROADCAST") {
        return EventType::TransactionBroadcast;
    } else if (str == "TRANSACTION_CANCELED") {
        return EventType::TransactionCanceled;
    } else if (str == "TRANSACTION_DROPPED") {
        return EventType::TransactionDropped;
    } else if (str == "TRANSACTION_EXECUTED") {
        return EventType::TransactionExecuted;
    } else if (str == "TRANSACTION_FAILED") {
        return EventType::TransactionFailed;
    } else if (str == "TRANSACTION_PENDING") {
        return EventType::TransactionPending;
    } else if (str == "TRANSACTION_PROCESSING") {
        return EventType::TransactionProcessing;
    } else if (str == "TRANSACTION_UPDATED") {
        return EventType::TransactionUpdated;
    }

    return EventType::Unknown;
}

TransactionState EnumUtils::deserialize_transaction_state(const std::string& s) noexcept {
    std::string str = enjin::utils::to_upper(s);
    if (str == "PENDING") {
        return TransactionState::Pending;
    } else if (str == "BROADCAST") {
        return TransactionState::Broadcast;
    } else if (str == "TP_PROCESSING") {
        return TransactionState::TpProcessing;
    } else if (str == "EXECUTED") {
        return TransactionState::Executed;
    } else if (str == "CANCELED_USER") {
        return TransactionState::CanceledUser;
    } else if (str == "CANCELED_PLATFORM") {
        return TransactionState::CanceledPlatform;
    } else if (str == "DROPPED") {
        return TransactionState::Dropped;
    } else if (str == "FAILED") {
        return TransactionState::Failed;
    }

    return TransactionState::Unknown;
}

TransactionType EnumUtils::deserialize_transaction_type(const std::string& s) noexcept {
    std::string str = enjin::utils::to_upper(s);
    if (str == "ACCEPT_ASSIGNMENT") {
        return TransactionType::AcceptAssignment;
    } else if (str == "ASSIGN") {
        return TransactionType::Assign;
    } else if (str == "APPROVE") {
        return TransactionType::Approve;
    } else if (str == "CREATE") {
        return TransactionType::Create;
    } else if (str == "MINT") {
        return TransactionType::Mint;
    } else if (str == "SEND") {
        return TransactionType::Send;
    } else if (str == "SEND_ENJ") {
        return TransactionType::SendEnj;
    } else if (str == "ADVANCED_SEND") {
        return TransactionType::AdvancedSend;
    } else if (str == "CREATE_TRADE") {
        return TransactionType::CreateTrade;
    } else if (str == "CANCEL_TRADE") {
        return TransactionType::CancelTrade;
    } else if (str == "MELT") {
        return TransactionType::Melt;
    } else if (str == "UPDATE_NAME") {
        return TransactionType::UpdateName;
    } else if (str == "SET_ITEM_URI") {
        return TransactionType::SetItemUri;
    } else if (str == "SET_WHITELISTED") {
        return TransactionType::SetWhitelisted;
    } else if (str == "SET_TRANSFERABLE") {
        return TransactionType::SetTransferable;
    } else if (str == "SET_MELT_FEE") {
        return TransactionType::SetMeltFee;
    } else if (str == "DECREASE_MAX_MELT_FEE") {
        return TransactionType::DecreaseMaxMeltFee;
    } else if (str == "SET_TRANSFER_FEE") {
        return TransactionType::SetTransferFee;
    } else if (str == "DECREASE_MAX_TRANSFER_FEE") {
        return TransactionType::DecreaseMaxTransferFee;
    } else if (str == "RELEASE_RESERVE") {
        return TransactionType::ReleaseReserve;
    } else if (str == "ADD_LOG") {
        return TransactionType::AddLog;
    } else if (str == "SET_APPROVAL_FOR_ALL") {
        return TransactionType::SetApprovalForAll;
    } else if (str == "MANAGE_UPDATE") {
        return TransactionType::ManageUpdate;
    } else if (str == "SET_DECIMALS") {
        return TransactionType::SetDecimals;
    } else if (str == "SET_SYMBOL") {
        return TransactionType::SetSymbol;
    } else if (str == "MESSAGE") {
        return TransactionType::Message;
    }

    return TransactionType::Unknown;
}

AssetSupplyModel EnumUtils::deserialize_asset_supply_model(const std::string& s) noexcept {
    std::string str = enjin::utils::to_upper(s);
    if (str == "FIXED") {
        return AssetSupplyModel::Fixed;
    } else if (str == "SETTABLE") {
        return AssetSupplyModel::Settable;
    } else if (str == "INFINITE") {
        return AssetSupplyModel::Infinite;
    } else if (str == "COLLAPSING") {
        return AssetSupplyModel::Collapsing;
    } else if (str == "ANNUAL_VALUE") {
        return AssetSupplyModel::AnnualValue;
    } else if (str == "ANNUAL_PERCENTAGE") {
        return AssetSupplyModel::AnnualPercentage;
    }

    return AssetSupplyModel::Unknown;
}

AssetTransferFeeType EnumUtils::deserialize_asset_transfer_fee_type(const std::string& s) noexcept {
    std::string str = enjin::utils::to_upper(s);
    if (str == "NONE") {
        return AssetTransferFeeType::None;
    } else if (str == "PER_TRANSFER") {
        return AssetTransferFeeType::PerTransfer;
    } else if (str == "PER_CRYPTO_ITEM") {
        return AssetTransferFeeType::PerCryptoItem;
    } else if (str == "RATIO_CUT") {
        return AssetTransferFeeType::RatioCut;
    } else if (str == "RATIO_EXTRA") {
        return AssetTransferFeeType::RatioExtra;
    }

    return AssetTransferFeeType::Unknown;
}

AssetTransferable EnumUtils::deserialize_asset_transferable(const std::string& s) noexcept {
    std::string str = enjin::utils::to_upper(s);
    if (str == "PERMANENT") {
        return AssetTransferable::Permanent;
    } else if (str == "TEMPORARY") {
        return AssetTransferable::Temporary;
    } else if (str == "BOUND") {
        return AssetTransferable::Bound;
    }

    return AssetTransferable::Unknown;
}

AssetVariantMode EnumUtils::deserialize_asset_variant_mode(const std::string& s) noexcept {
    std::string str = enjin::utils::to_upper(s);
    if (str == "NONE") {
        return AssetVariantMode::None;
    } else if (str == "BEAM") {
        return AssetVariantMode::Beam;
    } else if (str == "ONCE") {
        return AssetVariantMode::Once;
    } else if (str == "ALWAYS") {
        return AssetVariantMode::Always;
    }

    return AssetVariantMode::Unknown;
}

HttpMethod EnumUtils::deserialize_http_method(const std::string& s) {
    std::string str = enjin::utils::to_upper(s);
    if (str == "GET") {
        return HttpMethod::Get;
    } else if (str == "HEAD") {
        return HttpMethod::Head;
    } else if (str == "POST") {
        return HttpMethod::Post;
    } else if (str == "PUT") {
        return HttpMethod::Put;
    } else if (str == "DELETE") {
        return HttpMethod::Delete;
    } else if (str == "CONNECT") {
        return HttpMethod::Connect;
    } else if (str == "OPTIONS") {
        return HttpMethod::Options;
    } else if (str == "TRACE") {
        return HttpMethod::Trace;
    } else if (str == "PATCH") {
        return HttpMethod::Patch;
    }

    throw std::runtime_error("No valid conversion for " + s + " to HTTP method.");
}

std::string EnumUtils::serialize_event_type(EventType v) noexcept {
    switch (v) {
        case EventType::ProjectCreated:
            return "PROJECT_CREATED";
        case EventType::ProjectDeleted:
            return "PROJECT_DELETED";
        case EventType::ProjectLinked:
            return "PROJECT_LINKED";
        case EventType::ProjectLocked:
            return "PROJECT_LOCKED";
        case EventType::ProjectUnlinked:
            return "PROJECT_UNLINKED";
        case EventType::ProjectUnlocked:
            return "PROJECT_UNLOCKED";
        case EventType::ProjectUpdated:
            return "PROJECT_UPDATED";
        case EventType::BlockchainLogProcessed:
            return "BLOCKCHAIN_LOG_PROCESSED";
        case EventType::MessageProcessed:
            return "MESSAGE_PROCESSED";
        case EventType::PlayerCreated:
            return "PLAYER_CREATED";
        case EventType::PlayerDeleted:
            return "PLAYER_DELETED";
        case EventType::PlayerLinked:
            return "PLAYER_LINKED";
        case EventType::PlayerUnlinked:
            return "PLAYER_UNLINKED";
        case EventType::PlayerUpdated:
            return "PLAYER_UPDATED";
        case EventType::AssetCreated:
            return "ASSET_CREATED";
        case EventType::AssetMelted:
            return "ASSET_MELTED";
        case EventType::AssetMinted:
            return "ASSET_MINTED";
        case EventType::AssetTransferred:
            return "ASSET_TRANSFERRED";
        case EventType::AssetUpdated:
            return "ASSET_UPDATED";
        case EventType::TradeAssetCompleted:
            return "TRADE_ASSET_COMPLETED";
        case EventType::TradeAssetCreated:
            return "TRADE_ASSET_CREATED";
        case EventType::TransactionBroadcast:
            return "TRANSACTION_BROADCAST";
        case EventType::TransactionCanceled:
            return "TRANSACTION_CANCELED";
        case EventType::TransactionDropped:
            return "TRANSACTION_DROPPED";
        case EventType::TransactionExecuted:
            return "TRANSACTION_EXECUTED";
        case EventType::TransactionFailed:
            return "TRANSACTION_FAILED";
        case EventType::TransactionPending:
            return "TRANSACTION_PENDING";
        case EventType::TransactionProcessing:
            return "TRANSACTION_PROCESSING";
        case EventType::TransactionUpdated:
            return "TRANSACTION_UPDATED";
        default:
            return "";
    }
}

std::string EnumUtils::serialize_transaction_state(TransactionState v) noexcept {
    switch (v) {
        case TransactionState::Pending:
            return "PENDING";
        case TransactionState::Broadcast:
            return "BROADCAST";
        case TransactionState::TpProcessing:
            return "TP_PROCESSING";
        case TransactionState::Executed:
            return "EXECUTED";
        case TransactionState::CanceledUser:
            return "CANCELED_USER";
        case TransactionState::CanceledPlatform:
            return "CANCELED_PLATFORM";
        case TransactionState::Dropped:
            return "DROPPED";
        case TransactionState::Failed:
            return "FAILED";
        default:
            return "";
    }
}

std::string EnumUtils::serialize_transaction_type(TransactionType v) noexcept {
    switch (v) {
        case TransactionType::AcceptAssignment:
            return "ACCEPT_ASSIGNMENT";
        case TransactionType::Assign:
            return "ASSIGN";
        case TransactionType::Approve:
            return "APPROVE";
        case TransactionType::Create:
            return "CREATE";
        case TransactionType::Mint:
            return "MINT";
        case TransactionType::Send:
            return "SEND";
        case TransactionType::SendEnj:
            return "SEND_ENJ";
        case TransactionType::AdvancedSend:
            return "ADVANCED_SEND";
        case TransactionType::CreateTrade:
            return "CREATE_TRADE";
        case TransactionType::CancelTrade:
            return "CANCEL_TRADE";
        case TransactionType::Melt:
            return "MELT";
        case TransactionType::UpdateName:
            return "UPDATE_NAME";
        case TransactionType::SetItemUri:
            return "SET_ITEM_URI";
        case TransactionType::SetWhitelisted:
            return "SET_WHITELISTED";
        case TransactionType::SetTransferable:
            return "SET_TRANSFERABLE";
        case TransactionType::SetMeltFee:
            return "SET_MELT_FEE";
        case TransactionType::DecreaseMaxMeltFee:
            return "DECREASE_MAX_MELT_FEE";
        case TransactionType::SetTransferFee:
            return "SET_TRANSFER_FEE";
        case TransactionType::DecreaseMaxTransferFee:
            return "DECREASE_MAX_TRANSFER_FEE";
        case TransactionType::ReleaseReserve:
            return "RELEASE_RESERVE";
        case TransactionType::AddLog:
            return "ADD_LOG";
        case TransactionType::SetApprovalForAll:
            return "SET_APPROVAL_FOR_ALL";
        case TransactionType::ManageUpdate:
            return "MANAGE_UPDATE";
        case TransactionType::SetDecimals:
            return "SET_DECIMALS";
        case TransactionType::SetSymbol:
            return "SET_SYMBOL";
        case TransactionType::Message:
            return "MESSAGE";
        default:
            return "";
    }
}

std::string EnumUtils::serialize_sort_direction(SortDirection v) noexcept {
    switch (v) {
        case SortDirection::Ascending:
            return "asc";
        case SortDirection::Descending:
            return "desc";
        default:
            return "";
    }
}

std::string EnumUtils::serialize_asset_field(AssetField v) noexcept {
    switch (v) {
        case AssetField::Id:
            return "id";
        case AssetField::Name:
            return "name";
        case AssetField::CirculatingSupply:
            return "circulatingSupply";
        case AssetField::NonFungible:
            return "nonFungible";
        case AssetField::Reserve:
            return "reserve";
        case AssetField::TotalSupply:
            return "totalSupply";
        case AssetField::CreatedAt:
            return "createdAt";
        default:
            return "";
    }
}

std::string EnumUtils::serialize_asset_id_format(AssetIdFormat v) noexcept {
    switch (v) {
        case AssetIdFormat::Hex64:
            return "hex64";
        case AssetIdFormat::Hex256:
            return "hex256";
        case AssetIdFormat::Uint256:
            return "uint256";
        default:
            return "";
    }
}

std::string EnumUtils::serialize_asset_index_format(AssetIndexFormat v) noexcept {
    switch (v) {
        case AssetIndexFormat::Hex64:
            return "hex64";
        case AssetIndexFormat::Uint64:
            return "uint64";
        default:
            return "";
    }
}

std::string EnumUtils::serialize_asset_supply_model(AssetSupplyModel v) noexcept {
    switch (v) {
        case AssetSupplyModel::Fixed:
            return "FIXED";
        case AssetSupplyModel::Settable:
            return "SETTABLE";
        case AssetSupplyModel::Infinite:
            return "INFINITE";
        case AssetSupplyModel::Collapsing:
            return "COLLAPSING";
        case AssetSupplyModel::AnnualValue:
            return "ANNUAL_VALUE";
        case AssetSupplyModel::AnnualPercentage:
            return "ANNUAL_PERCENTAGE";
        default:
            return "UNKNOWN";
    }
}

std::string EnumUtils::serialize_asset_transfer_fee_type(AssetTransferFeeType v) noexcept {
    switch (v) {
        case AssetTransferFeeType::None:
            return "NONE";
        case AssetTransferFeeType::PerTransfer:
            return "PER_TRANSFER";
        case AssetTransferFeeType::PerCryptoItem:
            return "PER_CRYPTO_ITEM";
        case AssetTransferFeeType::RatioCut:
            return "RATIO_CUT";
        case AssetTransferFeeType::RatioExtra:
            return "RATIO_EXTRA";
        default:
            return "UNKNOWN";
    }
}

std::string EnumUtils::serialize_asset_transferable(AssetTransferable v) noexcept {
    switch (v) {
        case AssetTransferable::Permanent:
            return "PERMANENT";
        case AssetTransferable::Temporary:
            return "TEMPORARY";
        case AssetTransferable::Bound:
            return "BOUND";
        default:
            return "UNKNOWN";
    }
}

std::string EnumUtils::serialize_asset_variant_mode(AssetVariantMode v) noexcept {
    switch (v) {
        case AssetVariantMode::None:
            return "NONE";
        case AssetVariantMode::Beam:
            return "BEAM";
        case AssetVariantMode::Once:
            return "ONCE";
        case AssetVariantMode::Always:
            return "ALWAYS";
        default:
            return "UNKNOWN";
    }
}

std::string EnumUtils::serialize_http_method(HttpMethod v) noexcept {
    switch (v) {
        case HttpMethod::Get:
            return "GET";
        case HttpMethod::Head:
            return "HEAD";
        case HttpMethod::Post:
            return "POST";
        case HttpMethod::Put:
            return "PUT";
        case HttpMethod::Delete:
            return "DELETE";
        case HttpMethod::Connect:
            return "CONNECT";
        case HttpMethod::Options:
            return "OPTIONS";
        case HttpMethod::Trace:
            return "TRACE";
        case HttpMethod::Patch:
            return "PATCH";
        default:
            return "";
    }
}

std::string EnumUtils::serialize_operator(Operator v) noexcept {
    switch (v) {
        case Operator::GreaterThan:
            return "GREATER_THAN";
        case Operator::GreaterThanOrEqual:
            return "GREATER_THAN_OR_EQUAL";
        case Operator::LessThan:
            return "LESS_THAN";
        case Operator::LessThanOrEqual:
            return "LESS_THAN_OR_EQUAL";
        default:
            return "";
    }
}

std::string EnumUtils::serialize_transaction_field(TransactionField v) noexcept {
    switch (v) {
        case TransactionField::Id:
            return "id";
        case TransactionField::State:
            return "state";
        case TransactionField::Title:
            return "title";
        case TransactionField::CreatedAt:
            return "createdAt";
        case TransactionField::UpdatedAt:
            return "updatedAt";
        default:
            return "";
    }
}

std::string EnumUtils::serialize_whitelisted(Whitelisted v) noexcept {
    switch (v) {
        case Whitelisted::None:
            return "NONE";
        case Whitelisted::SendAndReceive:
            return "SEND_AND_RECEIVE";
        case Whitelisted::Send:
            return "SEND";
        case Whitelisted::Receive:
            return "RECEIVE";
        case Whitelisted::NoFees:
            return "NO_FEES";
        case Whitelisted::Address:
            return "ADDRESS";
        default:
            return "";
    }
}
