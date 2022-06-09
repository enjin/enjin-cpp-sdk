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

#include "enjinsdk/models/Platform.hpp"

#include "enjinsdk/JsonUtils.hpp"
#include "enjinsdk/JsonValue.hpp"

using namespace enjin::sdk::json;
using namespace enjin::sdk::models;
using namespace enjin::sdk::utils;

namespace enjin::sdk::models {

void Platform::deserialize(const std::string& json) {
    JsonValue json_object;

    if (!json_object.try_parse_as_object(json)) {
        id.reset();
        name.reset();
        network.reset();
        contracts.reset();
        notifications.reset();

        return;
    }

    JsonUtils::try_get_field(json_object, "id", id);
    JsonUtils::try_get_field(json_object, "name", name);
    JsonUtils::try_get_field(json_object, "network", network);
    JsonUtils::try_get_field(json_object, "contracts", contracts);
    JsonUtils::try_get_field(json_object, "notifications", notifications);
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
    return id == rhs.id
           && name == rhs.name
           && network == rhs.network
           && contracts == rhs.contracts
           && notifications == rhs.notifications;
}

bool Platform::operator!=(const Platform& rhs) const {
    return !(*this == rhs);
}

}
