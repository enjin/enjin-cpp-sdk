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

#ifndef ENJINCPPSDK_SHAREDBALANCEFRAGMENTARGUMENTS_HPP
#define ENJINCPPSDK_SHAREDBALANCEFRAGMENTARGUMENTS_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/ISerializable.hpp"
#include "enjinsdk/internal/BalanceFragmentArgumentsImpl.hpp"
#include "enjinsdk/models/AssetIdFormat.hpp"
#include "enjinsdk/models/AssetIndexFormat.hpp"
#include <string>
#include <type_traits>

namespace enjin::sdk::shared {

/// \brief Fragment interface used to request certain information from balances returned by the platform.
/// \tparam T The type of the implementing class.
template<class T>
class ENJINSDK_EXPORT BalanceFragmentArguments : public serialization::ISerializable {
public:
    ~BalanceFragmentArguments() override = default;

    [[nodiscard]] std::string serialize() const override {
        return impl.serialize();
    }

    /// \brief Sets the desired asset ID format.
    /// \param bal_id_format The ID format.
    /// \return This request for chaining.
    virtual T& set_bal_id_format(models::AssetIdFormat bal_id_format) {
        impl.set_bal_id_format(bal_id_format);
        return static_cast<T&>(*this);
    }

    /// \brief Sets the desired index format for non-fungible assets.
    /// \param bal_index_format The index format.
    /// \return This request for chaining.
    virtual T& set_bal_index_format(models::AssetIndexFormat bal_index_format) {
        impl.set_bal_index_format(bal_index_format);
        return static_cast<T&>(*this);
    }

    /// \brief Sets the request to include the project UUID with the balance.
    /// \return This request for chaining.
    virtual T& set_with_bal_project_uuid() {
        impl.set_with_bal_project_uuid();
        return static_cast<T&>(*this);
    }

    /// \brief Sets the request to include the wallet address with balance.
    /// \return This request for chaining.
    virtual T& set_with_bal_wallet_address() {
        impl.set_with_bal_wallet_address();
        return static_cast<T&>(*this);
    }

    bool operator==(const BalanceFragmentArguments& rhs) const {
        return impl == rhs.impl;
    }

    bool operator!=(const BalanceFragmentArguments& rhs) const {
        return impl != rhs.impl;
    }

protected:
    /// \brief Sole constructor.
    BalanceFragmentArguments() {
        static_assert(std::is_base_of<BalanceFragmentArguments, T>::value,
                      "Class T does not inherit from BalanceFragmentArguments.");
    }

private:
    BalanceFragmentArgumentsImpl impl;
};

}

#endif //ENJINCPPSDK_SHAREDBALANCEFRAGMENTARGUMENTS_HPP
