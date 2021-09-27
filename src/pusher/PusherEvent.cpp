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

#include "RapidJsonUtils.hpp"

namespace enjin::pusher {

static constexpr char USER_ID_KEY[] = "user_id";
static constexpr char CHANNEL_NAME_KEY[] = "channel";
static constexpr char EVENT_NAME_KEY[] = "event";
static constexpr char DATA_KEY[] = "data";

void PusherEvent::deserialize(const std::string& json) {
    rapidjson::Document document;
    document.Parse(json.c_str());
    if (document.IsObject()) {
        if (document.HasMember(USER_ID_KEY) && document[USER_ID_KEY].IsString()) {
            user_id.emplace(document[USER_ID_KEY].GetString());
        }
        if (document.HasMember(CHANNEL_NAME_KEY) && document[CHANNEL_NAME_KEY].IsString()) {
            channel_name.emplace(document[CHANNEL_NAME_KEY].GetString());
        }
        if (document.HasMember(EVENT_NAME_KEY) && document[EVENT_NAME_KEY].IsString()) {
            event_name.emplace(document[EVENT_NAME_KEY].GetString());
        }
        if (document.HasMember(DATA_KEY) && document[DATA_KEY].IsString()) {
            data.emplace(document[DATA_KEY].GetString());
        }
    }
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
    return user_id == rhs.user_id &&
           channel_name == rhs.channel_name &&
           event_name == rhs.event_name &&
           data == rhs.data;
}

bool PusherEvent::operator!=(const PusherEvent& rhs) const {
    return !(rhs == *this);
}

}
