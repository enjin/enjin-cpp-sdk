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

#ifndef ENJINCPPSDK_SHAREDTRANSACTIONFRAGMENTARGUMENTS_HPP
#define ENJINCPPSDK_SHAREDTRANSACTIONFRAGMENTARGUMENTS_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/ISerializable.hpp"
#include "enjinsdk/JsonUtils.hpp"
#include "enjinsdk/JsonValue.hpp"
#include <optional>
#include <string>
#include <type_traits>

namespace enjin::sdk::shared {

/// \brief Fragment interface used to request certain information from transactions returned by the platform.
/// \tparam T The type of the implementing class.
template<class T>
class ENJINSDK_EXPORT TransactionFragmentArguments : public serialization::ISerializable {
public:
    ~TransactionFragmentArguments() override = default;

    [[nodiscard]] std::string serialize() const override {
        return to_json().to_string();
    }

    /// \brief Sets the desired asset ID format.
    /// \param asset_id_format The format.
    /// \return This request for chaining.
    T& set_transaction_asset_id_format(models::AssetIdFormat asset_id_format) {
        transaction_asset_id_format_opt = asset_id_format;
        return static_cast<T&>(*this);
    }

    /// \brief Sets the request to include the blockchain data with the transaction.
    /// \return This request for chaining.
    T& set_with_blockchain_data() {
        with_blockchain_data_opt = true;
        return static_cast<T&>(*this);
    }

    /// \brief Sets the request to include the metadata with the transaction.
    /// \return This request for chaining.
    T& set_with_meta() {
        with_meta_opt = true;
        return static_cast<T&>(*this);
    }

    /// \brief Sets the request to include the encoded data with the transaction when used with
    /// set_with_blockchain_data().
    /// \return This request for chaining.
    T& set_with_encoded_data() {
        with_encoded_data_opt = true;
        return static_cast<T&>(*this);
    }

    /// \brief Sets the request to include the asset data with the transaction.
    /// \return This request for chaining.
    T& set_with_asset_data() {
        with_asset_data_opt = true;
        return static_cast<T&>(*this);
    }

    /// \brief Sets the request to include the signed transactions with the transaction when used with
    /// set_with_blockchain_data().
    /// \return This request for chaining.
    T& set_with_signed_txs() {
        with_signed_txs_opt = true;
        return static_cast<T&>(*this);
    }

    /// \brief Sets the request to include the error with the transaction when used with set_with_blockchain_data().
    /// \return This request for chaining.
    T& set_with_error() {
        with_error_opt = true;
        return static_cast<T&>(*this);
    }

    /// \brief Sets the request to include the nonce with the transaction when used with set_with_blockchain_data().
    /// \return This request for chaining.
    T& set_with_nonce() {
        with_nonce_opt = true;
        return static_cast<T&>(*this);
    }

    /// \brief Sets the request to include the state with the transaction when used with set_with_blockchain_data().
    /// \return This request for chaining.
    T& set_with_state() {
        with_state_opt = true;
        return static_cast<T&>(*this);
    }

    /// \brief Sets the request to include the receipt with the transaction when used with set_with_blockchain_data().
    /// \return This request for chaining.
    T& set_with_receipt() {
        with_receipt_opt = true;
        return static_cast<T&>(*this);
    }

    /// \brief Sets the request to include the logs in the receipt when used with set_with_receipt().
    /// \return This request for chaining.
    T& set_with_receipt_logs() {
        with_receipt_logs_opt = true;
        return static_cast<T&>(*this);
    }

    /// \brief Sets the request to include the event data in the receipt logs when used with set_with_receipt_logs().
    /// \return This request for chaining.
    T& set_with_log_event() {
        with_log_event_opt = true;
        return static_cast<T&>(*this);
    }

    /// \brief Sets the request to include the project with its UUID field that the transaction belongs to.
    /// \return This request for chaining.
    T& set_with_transaction_project_uuid() {
        with_transaction_project_uuid_opt = true;
        return static_cast<T&>(*this);
    }

    /// \brief Sets the request to include the wallet with its Ethereum address that belongs to the transaction.
    /// \return This request for chaining.
    T& set_with_transaction_wallet_address() {
        with_transaction_wallet_address_opt = true;
        return static_cast<T&>(*this);
    }

    [[nodiscard]] json::JsonValue to_json() const override {
        json::JsonValue json = json::JsonValue::create_object();

        utils::JsonUtils::try_set_field(json, "transactionAssetIdFormat", transaction_asset_id_format_opt);
        utils::JsonUtils::try_set_field(json, "withBlockchainData", with_blockchain_data_opt);
        utils::JsonUtils::try_set_field(json, "withMeta", with_meta_opt);
        utils::JsonUtils::try_set_field(json, "withEncodedData", with_encoded_data_opt);
        utils::JsonUtils::try_set_field(json, "withAssetData", with_asset_data_opt);
        utils::JsonUtils::try_set_field(json, "withSignedTxs", with_signed_txs_opt);
        utils::JsonUtils::try_set_field(json, "withError", with_error_opt);
        utils::JsonUtils::try_set_field(json, "withNonce", with_nonce_opt);
        utils::JsonUtils::try_set_field(json, "withState", with_state_opt);
        utils::JsonUtils::try_set_field(json, "withReceipt", with_receipt_opt);
        utils::JsonUtils::try_set_field(json, "withReceiptLogs", with_receipt_logs_opt);
        utils::JsonUtils::try_set_field(json, "withLogEvent", with_log_event_opt);
        utils::JsonUtils::try_set_field(json, "withTransactionProjectUuid", with_transaction_project_uuid_opt);
        utils::JsonUtils::try_set_field(json, "withTransactionWalletAddress", with_transaction_wallet_address_opt);

        return json;
    }

    bool operator==(const TransactionFragmentArguments& rhs) const {
        return transaction_asset_id_format_opt == rhs.transaction_asset_id_format_opt
               && with_blockchain_data_opt == rhs.with_blockchain_data_opt
               && with_meta_opt == rhs.with_meta_opt
               && with_encoded_data_opt == rhs.with_encoded_data_opt
               && with_asset_data_opt == rhs.with_asset_data_opt
               && with_signed_txs_opt == rhs.with_signed_txs_opt
               && with_error_opt == rhs.with_error_opt
               && with_nonce_opt == rhs.with_nonce_opt
               && with_state_opt == rhs.with_state_opt
               && with_receipt_opt == rhs.with_receipt_opt
               && with_receipt_logs_opt == rhs.with_receipt_logs_opt
               && with_log_event_opt == rhs.with_log_event_opt
               && with_transaction_project_uuid_opt == rhs.with_transaction_project_uuid_opt
               && with_transaction_wallet_address_opt == rhs.with_transaction_wallet_address_opt;
    }

    bool operator!=(const TransactionFragmentArguments& rhs) const {
        return !(*this == rhs);
    }

protected:
    /// \brief Sole constructor.
    TransactionFragmentArguments() {
        static_assert(std::is_base_of<TransactionFragmentArguments, T>::value,
                      "Class T does not inherit from TransactionFragmentArguments.");
    }

private:
    std::optional<models::AssetIdFormat> transaction_asset_id_format_opt;
    std::optional<bool> with_blockchain_data_opt;
    std::optional<bool> with_meta_opt;
    std::optional<bool> with_encoded_data_opt;
    std::optional<bool> with_asset_data_opt;
    std::optional<bool> with_signed_txs_opt;
    std::optional<bool> with_error_opt;
    std::optional<bool> with_nonce_opt;
    std::optional<bool> with_state_opt;
    std::optional<bool> with_receipt_opt;
    std::optional<bool> with_receipt_logs_opt;
    std::optional<bool> with_log_event_opt;
    std::optional<bool> with_transaction_project_uuid_opt;
    std::optional<bool> with_transaction_wallet_address_opt;
};

}

#endif //ENJINCPPSDK_SHAREDTRANSACTIONFRAGMENTARGUMENTS_HPP
