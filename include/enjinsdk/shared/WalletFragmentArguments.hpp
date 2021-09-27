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

#ifndef ENJINCPPSDK_SHAREDWALLETFRAGMENTARGUMENTS_HPP
#define ENJINCPPSDK_SHAREDWALLETFRAGMENTARGUMENTS_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/internal/WalletFragmentArgumentsImpl.hpp"
#include "enjinsdk/shared/AssetFragmentArguments.hpp"
#include <string>

namespace enjin::sdk::shared {

/// \brief Fragment interface used to request certain information from wallets returned by the platform.
/// \tparam T The type of the implementing class.
template<class T>
class ENJINSDK_EXPORT WalletFragmentArguments : public AssetFragmentArguments<T> {
public:
    ~WalletFragmentArguments() override = default;

    [[nodiscard]] std::string serialize() const override {
        return impl.serialize();
    }

    /// Sets the request to include the assets created by the wallet.
    /// \return This request for chaining.
    T& set_with_assets_created() {
        impl.set_with_assets_created();
        return dynamic_cast<T&>(*this);
    }

    bool operator==(const WalletFragmentArguments& rhs) const {
        return impl == rhs.impl;
    }

    bool operator!=(const WalletFragmentArguments& rhs) const {
        return rhs != *this;
    }

protected:
    /// \brief Default constructor.
    WalletFragmentArguments() = default;

private:
    WalletFragmentArgumentsImpl impl;
};

}

#endif //ENJINCPPSDK_SHAREDWALLETFRAGMENTARGUMENTS_HPP
