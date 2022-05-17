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

#ifndef ENJINSDK_PROJECTPROJECTTRANSACTIONREQUESTARGUMENTS_HPP
#define ENJINSDK_PROJECTPROJECTTRANSACTIONREQUESTARGUMENTS_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/internal/ProjectTransactionRequestArgumentsImpl.hpp"
#include "enjinsdk/shared/TransactionFragmentArguments.hpp"
#include <string>

namespace enjin::sdk::project {

/// \brief Interface used to set common arguments used in project transaction requests.
/// \tparam T The type of the implementing class.
template<typename T>
class ENJINSDK_EXPORT ProjectTransactionRequestArguments : public shared::TransactionFragmentArguments<T> {
public:
    ~ProjectTransactionRequestArguments() override = default;

    [[nodiscard]] std::string serialize() const override {
        return impl.serialize();
    }

    // ProjectTransactionRequestArguments functions

    /// \brief Sets the Ethereum address of the sender.
    /// \param address The address.
    /// \return This request for chaining.
    virtual T& set_eth_address(const std::string& address) {
        impl.set_eth_address(address);
        return dynamic_cast<T&>(*this);
    }

    // TransactionFragmentArguments functions

    /// \brief Sets the desired asset ID format.
    /// \param asset_id_format The format.
    /// \return This request for chaining.
    virtual T& set_asset_id_format(models::AssetIdFormat asset_id_format) override {
        impl.set_asset_id_format(asset_id_format);
        return dynamic_cast<T&>(*this);
    }

    /// \brief Sets the request to include the blockchain data with the transaction.
    /// \return This request for chaining.
    virtual T& set_with_blockchain_data() override {
        impl.set_with_blockchain_data();
        return dynamic_cast<T&>(*this);
    }

    /// \brief Sets the request to include the metadata with the transaction.
    /// \return This request for chaining.
    virtual T& set_with_meta() override {
        impl.set_with_meta();
        return dynamic_cast<T&>(*this);
    }

    /// \brief Sets the request to include the encoded data with the transaction when used with
    /// set_with_blockchain_data().
    /// \return This request for chaining.
    virtual T& set_with_encoded_data() override {
        impl.set_with_encoded_data();
        return dynamic_cast<T&>(*this);
    }

    /// \brief Sets the request to include the asset data with the transaction.
    /// \return This request for chaining.
    virtual T& set_with_asset_data() override {
        impl.set_with_asset_data();
        return dynamic_cast<T&>(*this);
    }

    /// \brief Sets the request to include the signed transactions with the transaction when used with
    /// set_with_blockchain_data().
    /// \return This request for chaining.
    virtual T& set_with_signed_txs() override {
        impl.set_with_signed_txs();
        return dynamic_cast<T&>(*this);
    }

    /// \brief Sets the request to include the error with the transaction when used with set_with_blockchain_data().
    /// \return This request for chaining.
    virtual T& set_with_error() override {
        impl.set_with_error();
        return dynamic_cast<T&>(*this);
    }

    /// \brief Sets the request to include the nonce with the transaction when used with set_with_blockchain_data().
    /// \return This request for chaining.
    virtual T& set_with_nonce() override {
        impl.set_with_nonce();
        return dynamic_cast<T&>(*this);
    }

    /// \brief Sets the request to include the state with the transaction when used with set_with_blockchain_data().
    /// \return This request for chaining.
    virtual T& set_with_state() override {
        impl.set_with_state();
        return dynamic_cast<T&>(*this);
    }

    /// \brief Sets the request to include the receipt with the transaction when used with set_with_blockchain_data().
    /// \return This request for chaining.
    virtual T& set_with_receipt() override {
        impl.set_with_receipt();
        return dynamic_cast<T&>(*this);
    }

    /// \brief Sets the request to include the logs in the receipt when used with set_with_receipt().
    /// \return This request for chaining.
    virtual T& set_with_receipt_logs() override {
        impl.set_with_receipt_logs();
        return dynamic_cast<T&>(*this);
    }

    /// \brief Sets the request to include the event data in the receipt logs when used with set_with_receipt_logs().
    /// \return This request for chaining.
    virtual T& set_with_log_event() override {
        impl.set_with_log_event();
        return dynamic_cast<T&>(*this);
    }

    /// \brief Sets the request to include the project with its UUID field that this belongs to.
    /// \return This request for chaining.
    virtual T& set_with_transaction_project_uuid() override {
        impl.set_with_transaction_project_uuid();
        return dynamic_cast<T&>(*this);
    }

protected:
    /// \brief Default constructor.
    ProjectTransactionRequestArguments() = default;

private:
    ProjectTransactionRequestArgumentsImpl impl;
};

}

#endif //ENJINSDK_PROJECTPROJECTTRANSACTIONREQUESTARGUMENTS_HPP
