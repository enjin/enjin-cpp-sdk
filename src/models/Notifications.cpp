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

#include "enjinsdk/models/Notifications.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::models {

void Notifications::deserialize(const std::string& json) {
    rapidjson::Document document;
    document.Parse(json.c_str());
    if (document.IsObject()) {
        if (document.HasMember(PUSHER_KEY) && document[PUSHER_KEY].IsObject()) {
            pusher.emplace(utils::get_object_as_type<Pusher>(document, PUSHER_KEY));
        }
    }
}

const std::optional<Pusher>& Notifications::get_pusher() const {
    return pusher;
}

bool Notifications::operator==(const Notifications& rhs) const {
    return pusher == rhs.pusher;
}

bool Notifications::operator!=(const Notifications& rhs) const {
    return !(rhs == *this);
}

}
