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

#ifndef ENJINCPPSDK_NOTIFICATIONS_HPP
#define ENJINCPPSDK_NOTIFICATIONS_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/IDeserializable.hpp"
#include "enjinsdk/models/Pusher.hpp"
#include <optional>

namespace enjin::sdk::models {

/// \brief Models the notification drivers and settings for the platform.
class ENJINSDK_EXPORT Notifications : public serialization::IDeserializable {
public:
    /// \brief Default constructor.
    Notifications() = default;

    ~Notifications() override = default;

    void deserialize(const std::string& json) override;

    /// \brief Returns the Pusher settings of the platform.
    /// \return The Pusher settings.
    [[nodiscard]] const std::optional<Pusher>& get_pusher() const;

    bool operator==(const Notifications& rhs) const;

    bool operator!=(const Notifications& rhs) const;

private:
    std::optional<Pusher> pusher;

    constexpr static char PUSHER_KEY[] = "pusher";
};

}

#endif //ENJINCPPSDK_NOTIFICATIONS_HPP
