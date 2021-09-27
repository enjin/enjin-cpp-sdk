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

#ifndef ENJINCPPSDK_PLATFORM_HPP
#define ENJINCPPSDK_PLATFORM_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/IDeserializable.hpp"
#include "enjinsdk/models/Contracts.hpp"
#include "enjinsdk/models/Notifications.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::models {

/// \brief Models data about the platform.
class ENJINSDK_EXPORT Platform : public serialization::IDeserializable {
public:
    /// \brief Default constructor.
    Platform() = default;

    ~Platform() override = default;

    void deserialize(const std::string& json) override;

    /// \brief Returns the ID of this platform.
    /// \return The ID.
    [[nodiscard]] const std::optional<int>& get_id() const;

    /// \brief Returns the name of this platform.
    /// \return The name.
    [[nodiscard]] const std::optional<std::string>& get_name() const;

    /// \brief Returns the current network this platform is using.
    /// \return The network.
    [[nodiscard]] const std::optional<std::string>& get_network() const;

    /// \brief Returns the smart contracts used by this platform.
    /// \return The contracts.
    [[nodiscard]] const std::optional<Contracts>& get_contracts() const;

    /// \brief Returns the notification drivers that this platform is using.
    /// \return The notification drivers.
    [[nodiscard]] const std::optional<Notifications>& get_notifications() const;

    bool operator==(const Platform& rhs) const;

    bool operator!=(const Platform& rhs) const;

private:
    std::optional<int> id;
    std::optional<std::string> name;
    std::optional<std::string> network;
    std::optional<Contracts> contracts;
    std::optional<Notifications> notifications;

    constexpr static char ID_KEY[] = "id";
    constexpr static char NAME_KEY[] = "name";
    constexpr static char NETWORK_KEY[] = "network";
    constexpr static char CONTRACTS_KEY[] = "contracts";
    constexpr static char NOTIFICATIONS_KEY[] = "notifications";
};

}

#endif //ENJINCPPSDK_PLATFORM_HPP
