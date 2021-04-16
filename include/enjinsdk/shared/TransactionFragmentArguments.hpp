/* Copyright 2021 Enjin Pte Ltd.
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
#include "enjinsdk/internal/TransactionFragmentArgumentsImpl.hpp"

namespace enjin::sdk::shared {

/// \brief Fragment interface used to request certain information from transactions returned by the platform.
/// \tparam T The type of the implementing class.
template<class T>
class ENJINSDK_EXPORT TransactionFragmentArguments : public serialization::ISerializable {
public:
    ~TransactionFragmentArguments() override = default;

    [[nodiscard]] std::string serialize() const override {
        return impl.serialize();
    }

    /// \brief Sets the request to include the blockchain data with the transaction.
    /// \return This request for chaining.
    T& set_with_blockchain_data() {
        impl.set_with_blockchain_data();
        return dynamic_cast<T&>(*this);
    }

    /// \brief Sets the request to include the metadata with the transaction.
    /// \return This request for chaining.
    T& set_with_meta() {
        impl.set_with_meta();
        return dynamic_cast<T&>(*this);
    }

    /// \brief Sets the request to include the encoded data with the transaction when used with
    /// set_with_blockchain_data().
    /// \return This request for chaining.
    T& set_with_encoded_data() {
        impl.set_with_encoded_data();
        return dynamic_cast<T&>(*this);
    }

    /// \brief Sets the request to include the asset data with the transaction.
    /// \return This request for chaining.
    T& set_with_asset_data() {
        impl.set_with_asset_data();
        return dynamic_cast<T&>(*this);
    }

    /// \brief Sets the request to include the signed transactions with the transaction when used with
    /// set_with_blockchain_data().
    /// \return This request for chaining.
    T& set_with_signed_txs() {
        impl.set_with_signed_txs();
        return dynamic_cast<T&>(*this);
    }

    /// \brief Sets the request to include the error with the transaction when used with set_with_blockchain_data().
    /// \return This request for chaining.
    T& set_with_error() {
        impl.set_with_error();
        return dynamic_cast<T&>(*this);
    }

    /// \brief Sets the request to include the nonce with the transaction when used with set_with_blockchain_data().
    /// \return This request for chaining.
    T& set_with_nonce() {
        impl.set_with_nonce();
        return dynamic_cast<T&>(*this);
    }

    /// \brief Sets the request to include the state with the transaction when used with set_with_blockchain_data().
    /// \return This request for chaining.
    T& set_with_state() {
        impl.set_with_state();
        return dynamic_cast<T&>(*this);
    }

    /// \brief Sets the request to include the receipt with the transaction when used with set_with_blockchain_data().
    /// \return This request for chaining.
    T& set_with_receipt() {
        impl.set_with_receipt();
        return dynamic_cast<T&>(*this);
    }

    /// \brief Sets the request to include the logs in the receipt when used with set_with_receipt().
    /// \return This request for chaining.
    T& set_with_receipt_logs() {
        impl.set_with_receipt_logs();
        return dynamic_cast<T&>(*this);
    }

    /// \brief Sets the request to include the event data in the receipt logs when used with set_with_receipt_logs().
    /// \return This request for chaining.
    T& set_with_log_event() {
        impl.set_with_log_event();
        return dynamic_cast<T&>(*this);
    }

    bool operator==(const TransactionFragmentArguments& rhs) const {
        return impl == rhs.impl;
    }

    bool operator!=(const TransactionFragmentArguments& rhs) const {
        return rhs != *this;
    }

protected:
    /// \brief Default constructor.
    TransactionFragmentArguments() = default;

private:
    TransactionFragmentArgumentsImpl impl;
};

}

#endif //ENJINCPPSDK_SHAREDTRANSACTIONFRAGMENTARGUMENTS_HPP
