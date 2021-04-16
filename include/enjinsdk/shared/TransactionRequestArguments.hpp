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

#ifndef ENJINCPPSDK_SHAREDTRANSACTIONREQUESTARGUMENTS_HPP
#define ENJINCPPSDK_SHAREDTRANSACTIONREQUESTARGUMENTS_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/internal/TransactionRequestArgumentsImpl.hpp"
#include "enjinsdk/shared/TransactionFragmentArguments.hpp"
#include <string>

namespace enjin::sdk::shared {

/// \brief Interface used to set common arguments used in transaction requests.
/// \tparam T The type of the implementing class.
template<class T>
class ENJINSDK_EXPORT TransactionRequestArguments : public TransactionFragmentArguments<T> {
public:
    ~TransactionRequestArguments() override = default;

    [[nodiscard]] std::string serialize() const override {
        return impl.serialize();
    }

    /// \brief Sets the Ethereum address of the sender.
    /// \param address The address.
    /// \return The request for chaining.
    T& set_eth_address(const std::string& address) {
        impl.set_eth_address(address);
        return dynamic_cast<T&>(*this);
    }

    /// \brief Sets whether the request will send the transaction to the blockchain.
    /// \param send The send state.
    /// \return This request for chaining.
    T& set_send(bool send) {
        impl.set_send(send);
        return dynamic_cast<T&>(*this);
    }

protected:
    /// \brief Default constructor.
    TransactionRequestArguments() = default;

private:
    TransactionRequestArgumentsImpl impl;
};

}

#endif //ENJINCPPSDK_SHAREDTRANSACTIONREQUESTARGUMENTS_HPP
