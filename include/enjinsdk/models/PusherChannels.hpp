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

#ifndef ENJINCPPSDK_PUSHERCHANNELS_HPP
#define ENJINCPPSDK_PUSHERCHANNELS_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/IDeserializable.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::models {

/// \brief Models Pusher channels used by the platform.
class ENJINSDK_EXPORT PusherChannels : public serialization::IDeserializable {
public:
    /// \brief Default constructor.
    PusherChannels() = default;

    ~PusherChannels() override = default;

    void deserialize(const std::string& json) override;

    /// \brief Returns the project channel.
    /// \return The project channel.
    [[nodiscard]] const std::optional<std::string>& get_project() const;

    /// \brief Returns the player channel.
    /// \return The player channel.
    [[nodiscard]] const std::optional<std::string>& get_player() const;

    /// \brief Returns the asset channel.
    /// \return The asset channel.
    [[nodiscard]] const std::optional<std::string>& get_asset() const;

    /// \brief Returns the wallet channel.
    /// \return The wallet channel.
    [[nodiscard]] const std::optional<std::string>& get_wallet() const;

    bool operator==(const PusherChannels& rhs) const;

    bool operator!=(const PusherChannels& rhs) const;

private:
    std::optional<std::string> project;
    std::optional<std::string> player;
    std::optional<std::string> asset;
    std::optional<std::string> wallet;

    constexpr static char PROJECT_KEY[] = "project";
    constexpr static char PLAYER_KEY[] = "player";
    constexpr static char ASSET_KEY[] = "asset";
    constexpr static char WALLET_KEY[] = "wallet";
};

}

#endif //ENJINCPPSDK_PUSHERCHANNELS_HPP
