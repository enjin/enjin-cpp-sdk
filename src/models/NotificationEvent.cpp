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

#include "enjinsdk/models/NotificationEvent.hpp"

#include <utility>

namespace enjin::sdk::models {

NotificationEvent::NotificationEvent(EventType type, std::string channel, std::string message)
        : type(type), channel(std::move(channel)), message(std::move(message)) {
}

EventType NotificationEvent::get_type() const {
    return type;
}

const std::string& NotificationEvent::get_channel() const {
    return channel;
}

const std::string& NotificationEvent::get_message() const {
    return message;
}

bool NotificationEvent::operator==(const NotificationEvent& rhs) const {
    return type == rhs.type &&
           channel == rhs.channel &&
           message == rhs.message;
}

bool NotificationEvent::operator!=(const NotificationEvent& rhs) const {
    return !(rhs == *this);
}

}
