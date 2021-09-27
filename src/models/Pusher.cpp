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

#include "enjinsdk/models/Pusher.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::models {

void Pusher::deserialize(const std::string& json) {
    rapidjson::Document document;
    document.Parse(json.c_str());
    if (document.IsObject()) {
        if (document.HasMember(KEY_KEY) && document[KEY_KEY].IsString()) {
            key.emplace(document[KEY_KEY].GetString());
        }
        if (document.HasMember(PUSHER_NAMESPACE_KEY) && document[PUSHER_NAMESPACE_KEY].IsString()) {
            pusher_namespace.emplace(document[PUSHER_NAMESPACE_KEY].GetString());
        }
        if (document.HasMember(CHANNELS_KEY) && document[CHANNELS_KEY].IsObject()) {
            channels.emplace(utils::get_object_as_type<PusherChannels>(document, CHANNELS_KEY));
        }
        if (document.HasMember(OPTIONS_KEY) && document[OPTIONS_KEY].IsObject()) {
            options.emplace(utils::get_object_as_type<PusherOptions>(document, OPTIONS_KEY));
        }
    }
}

const std::optional<std::string>& Pusher::get_key() const {
    return key;
}

const std::optional<std::string>& Pusher::get_pusher_namespace() const {
    return pusher_namespace;
}

const std::optional<PusherChannels>& Pusher::get_channels() const {
    return channels;
}

const std::optional<PusherOptions>& Pusher::get_options() const {
    return options;
}

bool Pusher::operator==(const Pusher& rhs) const {
    return key == rhs.key &&
           pusher_namespace == rhs.pusher_namespace &&
           channels == rhs.channels &&
           options == rhs.options;
}

bool Pusher::operator!=(const Pusher& rhs) const {
    return !(rhs == *this);
}

}
