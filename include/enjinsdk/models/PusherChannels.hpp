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

#ifndef ENJINCPPSDK_PUSHERCHANNELS_HPP
#define ENJINCPPSDK_PUSHERCHANNELS_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/IDeserializable.hpp"
#include <memory>
#include <optional>
#include <string>

namespace enjin::sdk::models {

/// \brief Models Pusher channels used by the platform.
class ENJINSDK_EXPORT PusherChannels : public serialization::IDeserializable {
public:
    /// \brief Constructs an instance of this class.
    PusherChannels();

    /// \brief Constructs an instance as a copy of another.
    /// \param other The other instance.
    PusherChannels(const PusherChannels& other);

    /// \brief Constructs an instance via move.
    /// \param other The other instance being moved.
    PusherChannels(PusherChannels&& other) noexcept;

    /// \brief Deconstructs this instance.
    ~PusherChannels() override;

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

    PusherChannels& operator=(const PusherChannels& rhs);

private:
    class Impl;

    std::unique_ptr<Impl> pimpl;
};

}

#endif //ENJINCPPSDK_PUSHERCHANNELS_HPP
