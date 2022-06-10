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
using namespace enjin::sdk::serialization;
using namespace enjin::sdk::utils;

class Platform::Impl final : public IDeserializable {
public:
    Impl() = default;

    ~Impl() override = default;

    void deserialize(const std::string& json) override {
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

    [[nodiscard]] const std::optional<int>& get_id() const {
        return id;
    }

    [[nodiscard]] const std::optional<std::string>& get_name() const {
        return name;
    }

    [[nodiscard]] const std::optional<std::string>& get_network() const {
        return network;
    }

    [[nodiscard]] const std::optional<Contracts>& get_contracts() const {
        return contracts;
    }

    [[nodiscard]] const std::optional<Notifications>& get_notifications() const {
        return notifications;
    }

    bool operator==(const Impl& rhs) const {
        return id == rhs.id
               && name == rhs.name
               && network == rhs.network
               && contracts == rhs.contracts
               && notifications == rhs.notifications;
    }

    bool operator!=(const Impl& rhs) const {
        return !(*this == rhs);
    }

private:
    std::optional<int> id;
    std::optional<std::string> name;
    std::optional<std::string> network;
    std::optional<Contracts> contracts;
    std::optional<Notifications> notifications;
};

Platform::Platform() : pimpl(std::make_unique<Impl>()) {
}

Platform::Platform(const Platform& other) : pimpl(std::make_unique<Impl>(*other.pimpl)) {
}

Platform::Platform(Platform&& other) noexcept = default;

Platform::~Platform() = default;

void Platform::deserialize(const std::string& json) {
    pimpl->deserialize(json);
}

const std::optional<int>& Platform::get_id() const {
    return pimpl->get_id();
}

const std::optional<std::string>& Platform::get_name() const {
    return pimpl->get_name();
}

const std::optional<std::string>& Platform::get_network() const {
    return pimpl->get_network();
}

const std::optional<Contracts>& Platform::get_contracts() const {
    return pimpl->get_contracts();
}

const std::optional<Notifications>& Platform::get_notifications() const {
    return pimpl->get_notifications();
}

bool Platform::operator==(const Platform& rhs) const {
    return *pimpl == *rhs.pimpl;
}

bool Platform::operator!=(const Platform& rhs) const {
    return *pimpl != *rhs.pimpl;
}

Platform& Platform::operator=(const Platform& rhs) {
    pimpl = std::make_unique<Impl>(*rhs.pimpl);
    return *this;
}
