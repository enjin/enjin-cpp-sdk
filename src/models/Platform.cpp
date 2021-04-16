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

#include "enjinsdk/models/Platform.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::models {

void Platform::deserialize(const std::string& json) {
    rapidjson::Document document;
    document.Parse(json.c_str());
    if (document.IsObject()) {
        if (document.HasMember(ID_KEY) && document[ID_KEY].IsInt()) {
            id.emplace(document[ID_KEY].GetInt());
        }
        if (document.HasMember(NAME_KEY) && document[NAME_KEY].IsString()) {
            name.emplace(document[NAME_KEY].GetString());
        }
        if (document.HasMember(NETWORK_KEY) && document[NETWORK_KEY].IsString()) {
            network.emplace(document[NETWORK_KEY].GetString());
        }
        if (document.HasMember(CONTRACTS_KEY) && document[CONTRACTS_KEY].IsObject()) {
            contracts.emplace(utils::get_object_as_type<Contracts>(document, CONTRACTS_KEY));
        }
        if (document.HasMember(NOTIFICATIONS_KEY) && document[NOTIFICATIONS_KEY].IsObject()) {
            notifications.emplace(utils::get_object_as_type<Notifications>(document, NOTIFICATIONS_KEY));
        }
    }
}

const std::optional<int>& Platform::get_id() const {
    return id;
}

const std::optional<std::string>& Platform::get_name() const {
    return name;
}

const std::optional<std::string>& Platform::get_network() const {
    return network;
}

const std::optional<Contracts>& Platform::get_contracts() const {
    return contracts;
}

const std::optional<Notifications>& Platform::get_notifications() const {
    return notifications;
}

bool Platform::operator==(const Platform& rhs) const {
    return id == rhs.id &&
           name == rhs.name &&
           network == rhs.network &&
           contracts == rhs.contracts &&
           notifications == rhs.notifications;
}

bool Platform::operator!=(const Platform& rhs) const {
    return !(rhs == *this);
}

}
