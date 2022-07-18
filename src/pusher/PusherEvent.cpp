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

#include "PusherEvent.hpp"

#include "enjinsdk/JsonUtils.hpp"
#include "enjinsdk/JsonValue.hpp"

using namespace enjin::pusher;
using namespace enjin::sdk::json;
using namespace enjin::sdk::models;
using namespace enjin::sdk::utils;

void PusherEvent::deserialize(const std::string& json) {
    JsonValue json_object;

    if (!json_object.try_parse_as_object(json)) {
        user_id.reset();
        channel_name.reset();
        event_name.reset();
        data.reset();

        return;
    }

    JsonUtils::try_get_field(json_object, "user_id", user_id);
    JsonUtils::try_get_field(json_object, "channel", channel_name);
    JsonUtils::try_get_field(json_object, "event", event_name);
    JsonUtils::try_get_field(json_object, "data", data);
}

const std::optional<std::string>& PusherEvent::get_user_id() const {
    return user_id;
}

const std::optional<std::string>& PusherEvent::get_channel_name() const {
    return channel_name;
}

const std::optional<std::string>& PusherEvent::get_event_name() const {
    return event_name;
}

const std::optional<std::string>& PusherEvent::get_data() const {
    return data;
}

bool PusherEvent::operator==(const PusherEvent& rhs) const {
    return user_id == rhs.user_id
           && channel_name == rhs.channel_name
           && event_name == rhs.event_name
           && data == rhs.data;
}

bool PusherEvent::operator!=(const PusherEvent& rhs) const {
    return !(*this == rhs);
}
