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

#ifndef ENJINCPPSDK_NOTIFICATIONEVENT_HPP
#define ENJINCPPSDK_NOTIFICATIONEVENT_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/models/EventType.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::models {

/// \brief Container class for notification data from the platform.
class ENJINSDK_EXPORT NotificationEvent {
public:
    NotificationEvent() = delete;

    /// \brief Constructor to be used internally.
    /// \param type The event type.
    /// \param channel The event channel.
    /// \param message The serialized message.
    NotificationEvent(EventType type, std::string channel, std::string message);

    /// \brief Default destructor.
    ~NotificationEvent() = default;

    /// \brief Returns the event type.
    /// \return The event type.
    [[nodiscard]] EventType get_type() const;

    /// \brief Returns the event channel the event was broadcasted on.
    /// \return The channel.
    [[nodiscard]] const std::string& get_channel() const;

    /// \brief Returns the serialized message broadcasted with the event.
    /// \return The message.
    [[nodiscard]] const std::string& get_message() const;

    bool operator==(const NotificationEvent& rhs) const;

    bool operator!=(const NotificationEvent& rhs) const;

private:
    EventType type;
    std::string channel;
    std::string message;
};

}

#endif //ENJINCPPSDK_NOTIFICATIONEVENT_HPP
