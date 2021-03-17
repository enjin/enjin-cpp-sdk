#ifndef ENJINCPPSDK_ENUMUTILS_HPP
#define ENJINCPPSDK_ENUMUTILS_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/models/EventType.hpp"
#include "enjinsdk/models/RequestState.hpp"
#include "enjinsdk/models/RequestType.hpp"
#include "enjinsdk/models/SortDirection.hpp"
#include "enjinsdk/models/AssetField.hpp"
#include "enjinsdk/models/AssetIdFormat.hpp"
#include "enjinsdk/models/AssetIndexFormat.hpp"
#include "enjinsdk/models/AssetSupplyModel.hpp"
#include "enjinsdk/models/AssetTransferFeeType.hpp"
#include "enjinsdk/models/AssetTransferable.hpp"
#include "enjinsdk/models/AssetVariantMode.hpp"
#include "enjinsdk/models/TransactionField.hpp"
#include "enjinsdk/models/Whitelisted.hpp"
#include "enjinsdk/internal/pusher/ConnectionState.hpp"
#include <string>

namespace enjin::sdk::utils {

ENJINSDK_EXPORT
enjin::sdk::models::EventType deserialize_event_type(const std::string& s) noexcept;

ENJINSDK_EXPORT
enjin::sdk::models::RequestState deserialize_request_state(const std::string& s) noexcept;

ENJINSDK_EXPORT
enjin::sdk::models::RequestType deserialize_request_type(const std::string& s) noexcept;

ENJINSDK_EXPORT
enjin::sdk::models::AssetSupplyModel deserialize_asset_supply_model(const std::string& s) noexcept;

ENJINSDK_EXPORT
enjin::sdk::models::AssetTransferFeeType deserialize_asset_transfer_fee_type(const std::string& s) noexcept;

ENJINSDK_EXPORT
enjin::sdk::models::AssetTransferable deserialize_asset_transferable(const std::string& s) noexcept;

ENJINSDK_EXPORT
enjin::sdk::models::AssetVariantMode deserialize_asset_variant_mode(const std::string& s) noexcept;

ENJINSDK_EXPORT
std::string serialize_event_type(enjin::sdk::models::EventType v) noexcept;

ENJINSDK_EXPORT
std::string serialize_pusher_connection_state(pusher::ConnectionState v) noexcept;

ENJINSDK_EXPORT
std::string serialize_request_state(enjin::sdk::models::RequestState v) noexcept;

ENJINSDK_EXPORT
std::string serialize_request_type(enjin::sdk::models::RequestType v) noexcept;

ENJINSDK_EXPORT
std::string serialize_sort_direction(enjin::sdk::models::SortDirection v) noexcept;

ENJINSDK_EXPORT
std::string serialize_asset_field(enjin::sdk::models::AssetField v) noexcept;

ENJINSDK_EXPORT
std::string serialize_asset_id_format(enjin::sdk::models::AssetIdFormat v) noexcept;

ENJINSDK_EXPORT
std::string serialize_asset_index_format(enjin::sdk::models::AssetIndexFormat v) noexcept;

ENJINSDK_EXPORT
std::string serialize_asset_supply_model(enjin::sdk::models::AssetSupplyModel v) noexcept;

ENJINSDK_EXPORT
std::string serialize_asset_transfer_fee_type(enjin::sdk::models::AssetTransferFeeType v) noexcept;

ENJINSDK_EXPORT
std::string serialize_asset_transferable(enjin::sdk::models::AssetTransferable v) noexcept;

ENJINSDK_EXPORT
std::string serialize_asset_variant_mode(enjin::sdk::models::AssetVariantMode v) noexcept;

ENJINSDK_EXPORT
std::string serialize_transaction_field(enjin::sdk::models::TransactionField v) noexcept;

ENJINSDK_EXPORT
std::string serialize_whitelisted(enjin::sdk::models::Whitelisted v) noexcept;

}

#endif //ENJINCPPSDK_ENUMUTILS_HPP
