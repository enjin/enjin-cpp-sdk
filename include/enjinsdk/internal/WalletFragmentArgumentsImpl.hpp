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

#ifndef ENJINCPPSDK_SHAREDWALLETFRAGMENTARGUMENTSIMPL_HPP
#define ENJINCPPSDK_SHAREDWALLETFRAGMENTARGUMENTSIMPL_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/internal/AssetFragmentArgumentsImpl.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::shared {

/// \brief Internal implementation class for storing values of a GraphQL Wallet fragment.
class ENJINSDK_EXPORT WalletFragmentArgumentsImpl : public AssetFragmentArgumentsImpl {
public:
    /// \brief Default constructor.
    WalletFragmentArgumentsImpl() = default;

    ~WalletFragmentArgumentsImpl() override = default;

    [[nodiscard]] std::string serialize() const override;

    /// \brief Sets the value for the associated field to true.
    void set_with_assets_created();

    bool operator==(const WalletFragmentArgumentsImpl& rhs) const;

    bool operator!=(const WalletFragmentArgumentsImpl& rhs) const;

private:
    std::optional<bool> with_assets_created;
};

}

#endif //ENJINCPPSDK_SHAREDWALLETFRAGMENTARGUMENTSIMPL_HPP
