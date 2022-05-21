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

#ifndef ENJINCPPSDK_PLAYER_HPP
#define ENJINCPPSDK_PLAYER_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/IDeserializable.hpp"
#include "enjinsdk/models/LinkingInfo.hpp"
#include "enjinsdk/models/Wallet.hpp"
#include <memory>
#include <optional>
#include <string>

namespace enjin::sdk::models {

/// \brief Models a player on the platform.
class ENJINSDK_EXPORT Player : public serialization::IDeserializable {
public:
    /// \brief Constructs an instance of this class.
    Player();

    /// \brief Constructs an instance as a copy of another.
    /// \param other The other instance.
    Player(const Player& other);

    /// \brief Constructs an instance via move.
    /// \param other The other instance being moved.
    Player(Player&& other) noexcept;

    /// \brief Deconstructs this instance.
    ~Player() override;

    void deserialize(const std::string& json) override;

    /// \brief Returns the ID of this player.
    /// \return The player ID.
    [[nodiscard]] const std::optional<std::string>& get_id() const;

    /// \brief Returns the linking information for this player.
    /// \return The information.
    [[nodiscard]] const std::optional<LinkingInfo>& get_linking_info() const;

    /// \brief Returns the wallet for this player.
    /// \return The wallet.
    [[nodiscard]] const std::optional<Wallet>& get_wallet() const;

    /// \brief Returns the datetime when this player was created.
    /// \return The datetime.
    /// \remarks The datetime is formatted using the ISO 8601 date format.
    [[nodiscard]] const std::optional<std::string>& get_created_at() const;

    /// \brief Returns the datetime when this player was last updated.
    /// \return The datetime.
    /// \remarks The datetime is formatted using the ISO 8601 date format.
    [[nodiscard]] const std::optional<std::string>& get_updated_at() const;

    bool operator==(const Player& rhs) const;

    bool operator!=(const Player& rhs) const;

    Player& operator=(const Player& rhs);

private:
    class Impl;

    std::unique_ptr<Impl> impl;
};

}

#endif //ENJINCPPSDK_PLAYER_HPP
