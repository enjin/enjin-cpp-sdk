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

    /// \brief Sets the Ethereum address of the sender.
    /// \param address The address.
    /// \return This request for chaining.
    T& set_eth_address(const std::string& address) {
        impl.set_eth_address(address);
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
