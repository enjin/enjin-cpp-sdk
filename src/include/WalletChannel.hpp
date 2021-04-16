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

#ifndef ENJINCPPSDK_WALLETCHANNEL_HPP
#define ENJINCPPSDK_WALLETCHANNEL_HPP

#include "enjinsdk_export.h"
#include "IChannel.hpp"
#include "enjinsdk/models/Platform.hpp"
#include <string>

namespace enjin::sdk::events {

/// \brief Represents a channel to subscribe to for Enjin Cloud wallet events.
class ENJINSDK_EXPORT WalletChannel : public IChannel {
public:
    WalletChannel() = delete;

    /// \brief Constructs a channel for the given network and wallet.
    /// \param platform The platform.
    /// \param eth_address The wallet's address.
    WalletChannel(const models::Platform& platform, const std::string& eth_address);

    ~WalletChannel() override = default;

    [[nodiscard]] std::string channel() const override;

private:
    models::Platform platform;
    std::string eth_address;
};

}

#endif //ENJINCPPSDK_WALLETCHANNEL_HPP
