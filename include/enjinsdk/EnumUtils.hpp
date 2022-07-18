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

#ifndef ENJINCPPSDK_ENUMUTILS_HPP
#define ENJINCPPSDK_ENUMUTILS_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/HttpMethod.hpp"
#include "enjinsdk/models/EventType.hpp"
#include "enjinsdk/models/TransactionState.hpp"
#include "enjinsdk/models/TransactionType.hpp"
#include "enjinsdk/models/SortDirection.hpp"
#include "enjinsdk/models/AssetField.hpp"
#include "enjinsdk/models/AssetIdFormat.hpp"
#include "enjinsdk/models/AssetIndexFormat.hpp"
#include "enjinsdk/models/AssetSupplyModel.hpp"
#include "enjinsdk/models/AssetTransferFeeType.hpp"
#include "enjinsdk/models/AssetTransferable.hpp"
#include "enjinsdk/models/AssetVariantMode.hpp"
#include "enjinsdk/models/Operator.hpp"
#include "enjinsdk/models/TransactionField.hpp"
#include "enjinsdk/models/Whitelisted.hpp"
#include <string>

namespace enjin::sdk::utils {

/// \brief Utility class for serialization of enum values.
class ENJINSDK_EXPORT EnumUtils final {
public:
    EnumUtils() = delete;

    ~EnumUtils() = delete;

    /// \brief Deserializes the event type from a string.
    /// \param s The serialized string.
    /// \return The event type.
    static models::EventType deserialize_event_type(const std::string& s) noexcept;

    /// \brief Deserializes the transaction state from a string.
    /// \param s The serialized string.
    /// \return The request state.
    static models::TransactionState deserialize_transaction_state(const std::string& s) noexcept;

    /// \brief Deserializes the transaction type from a string.
    /// \param s The serialized string.
    /// \return The request type.
    static models::TransactionType deserialize_transaction_type(const std::string& s) noexcept;

    /// \brief Deserializes the asset supply model from a string.
    /// \param s The serialized string.
    /// \return The asset supply model.
    static models::AssetSupplyModel deserialize_asset_supply_model(const std::string& s) noexcept;

    /// \brief Deserializes the asset transfer fee from a string.
    /// \param s The serialized string.
    /// \return The asset transfer fee.
    static models::AssetTransferFeeType deserialize_asset_transfer_fee_type(const std::string& s) noexcept;

    /// \brief Deserializes the asset transferable from a string.
    /// \param s The serialized string.
    /// \return The asset transferable.
    static models::AssetTransferable deserialize_asset_transferable(const std::string& s) noexcept;

    /// \brief Deserializes the asset variant mode from a string.
    /// \param s The serialized string.
    /// \return The asset variant mode.
    static models::AssetVariantMode deserialize_asset_variant_mode(const std::string& s) noexcept;

    /// \brief Deserializes the HTTP method from a string.
    /// \param s The serialized string.
    /// \return The HTTP method.
    static http::HttpMethod deserialize_http_method(const std::string& s);

    /// \brief Serializes the event type into a string.
    /// \param v The enum value.
    /// \return The serialized value.
    static std::string serialize_event_type(models::EventType v) noexcept;

    /// \brief Serializes the transaction state into a string.
    /// \param v The enum value.
    /// \return The serialized value.
    static std::string serialize_transaction_state(models::TransactionState v) noexcept;

    /// \brief Serializes the transaction type into a string.
    /// \param v The enum value.
    /// \return The serialized value.
    static std::string serialize_transaction_type(models::TransactionType v) noexcept;

    /// \brief Serializes the sort direction into a string.
    /// \param v The enum value.
    /// \return The serialized value.
    static std::string serialize_sort_direction(models::SortDirection v) noexcept;

    /// \brief Serializes the asset field into a string.
    /// \param v The enum value.
    /// \return The serialized value.
    static std::string serialize_asset_field(models::AssetField v) noexcept;

    /// \brief Serializes the asset ID into a string.
    /// \param v The enum value.
    /// \return The serialized value.
    static std::string serialize_asset_id_format(models::AssetIdFormat v) noexcept;

    /// \brief Serializes the asset index into a string.
    /// \param v The enum value.
    /// \return The serialized value.
    static std::string serialize_asset_index_format(models::AssetIndexFormat v) noexcept;

    /// \brief Serializes the asset supply model into a string.
    /// \param v The enum value.
    /// \return The serialized value.
    static std::string serialize_asset_supply_model(models::AssetSupplyModel v) noexcept;

    /// \brief Serializes the asset transfer fee type into a string.
    /// \param v The enum value.
    /// \return The serialized value.
    static std::string serialize_asset_transfer_fee_type(models::AssetTransferFeeType v) noexcept;

    /// \brief Serializes the asset transferable into a string.
    /// \param v The enum value.
    /// \return The serialized value.
    static std::string serialize_asset_transferable(models::AssetTransferable v) noexcept;

    /// \brief Serializes the asset variant mode into a string.
    /// \param v The enum value.
    /// \return The serialized value.
    static std::string serialize_asset_variant_mode(models::AssetVariantMode v) noexcept;

    /// \brief Serializes the HTTP method into a string.
    /// \param v The enum value.
    /// \return The serialized value.
    static std::string serialize_http_method(http::HttpMethod v) noexcept;

    /// \brief Serializes the operator into a string.
    /// \param v The enum value.
    /// \return The serialized value.
    static std::string serialize_operator(models::Operator v) noexcept;

    /// \brief Serializes the transaction field into a string.
    /// \param v The enum value.
    /// \return The serialized value.
    static std::string serialize_transaction_field(models::TransactionField v) noexcept;

    /// \brief Serializes the whitelisted into a string.
    /// \param v The enum value.
    /// \return The serialized value.
    static std::string serialize_whitelisted(models::Whitelisted v) noexcept;
};

}

#endif //ENJINCPPSDK_ENUMUTILS_HPP
