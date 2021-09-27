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

#ifndef ENJINCPPSDK_PUSHERPUSHEREVENT_HPP
#define ENJINCPPSDK_PUSHERPUSHEREVENT_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/IDeserializable.hpp"
#include <optional>
#include <string>

namespace enjin::pusher {

/// \brief Class for modeling Pusher events.
class ENJINSDK_EXPORT PusherEvent : public sdk::serialization::IDeserializable {
public:
    /// \brief Default constructor.
    PusherEvent() = default;

    ~PusherEvent() override = default;

    void deserialize(const std::string& json) override;

    /// \brief Returns the user ID of the event.
    /// \return The optional for the user ID.
    [[nodiscard]] const std::optional<std::string>& get_user_id() const;

    /// \brief Returns the channel name of the event.
    /// \return The optional for the channel name.
    [[nodiscard]] const std::optional<std::string>& get_channel_name() const;

    /// \brief Returns the name of the event.
    /// \return The optional for the event name.
    [[nodiscard]] const std::optional<std::string>& get_event_name() const;

    /// \brief Returns the data of the event.
    /// \return The optional for the data.
    [[nodiscard]] const std::optional<std::string>& get_data() const;

    bool operator==(const PusherEvent& rhs) const;

    bool operator!=(const PusherEvent& rhs) const;

private:
    std::optional<std::string> user_id;
    std::optional<std::string> channel_name;
    std::optional<std::string> event_name;
    std::optional<std::string> data;
};

}

#endif //ENJINCPPSDK_PUSHERPUSHEREVENT_HPP
