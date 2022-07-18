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

#include "enjinsdk/models/Notifications.hpp"

#include "enjinsdk/JsonUtils.hpp"
#include "enjinsdk/JsonValue.hpp"

using namespace enjin::sdk::json;
using namespace enjin::sdk::models;
using namespace enjin::sdk::serialization;
using namespace enjin::sdk::utils;

class Notifications::Impl final : public IDeserializable {
public:
    Impl() = default;

    ~Impl() override = default;

    void deserialize(const std::string& json) override {
        JsonValue json_object;

        if (!json_object.try_parse_as_object(json)) {
            pusher.reset();

            return;
        }

        JsonUtils::try_get_field(json_object, "pusher", pusher);
    }

    [[nodiscard]] const std::optional<Pusher>& get_pusher() const {
        return pusher;
    }

    bool operator==(const Impl& rhs) const {
        return pusher == rhs.pusher;
    }

    bool operator!=(const Impl& rhs) const {
        return !(*this == rhs);
    }

private:
    std::optional<Pusher> pusher;
};

Notifications::Notifications() : pimpl(std::make_unique<Impl>()) {
}

Notifications::Notifications(const Notifications& other) : pimpl(std::make_unique<Impl>(*other.pimpl)) {
}

Notifications::Notifications(Notifications&& other) noexcept = default;

Notifications::~Notifications() = default;

void Notifications::deserialize(const std::string& json) {
    pimpl->deserialize(json);
}

const std::optional<Pusher>& Notifications::get_pusher() const {
    return pimpl->get_pusher();
}

bool Notifications::operator==(const Notifications& rhs) const {
    return *pimpl == *rhs.pimpl;
}

bool Notifications::operator!=(const Notifications& rhs) const {
    return *pimpl != *rhs.pimpl;
}

Notifications& Notifications::operator=(const Notifications& rhs) {
    pimpl = std::make_unique<Impl>(*rhs.pimpl);
    return *this;
}
