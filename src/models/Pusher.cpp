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

#include "enjinsdk/JsonUtils.hpp"
#include "enjinsdk/JsonValue.hpp"

using namespace enjin::sdk::json;
using namespace enjin::sdk::models;
using namespace enjin::sdk::serialization;
using namespace enjin::sdk::utils;

class Pusher::Impl final : public IDeserializable {
public:
    Impl() = default;

    ~Impl() override = default;

    void deserialize(const std::string& json) override {
        JsonValue json_object;

        if (!json_object.try_parse_as_object(json)) {
            key.reset();
            pusher_namespace.reset();
            channels.reset();
            options.reset();

            return;
        }

        JsonUtils::try_get_field(json_object, "key", key);
        JsonUtils::try_get_field(json_object, "namespace", pusher_namespace);
        JsonUtils::try_get_field(json_object, "channels", channels);
        JsonUtils::try_get_field(json_object, "options", options);
    }

    [[nodiscard]] const std::optional<std::string>& get_key() const {
        return key;
    }

    [[nodiscard]] const std::optional<std::string>& get_pusher_namespace() const {
        return pusher_namespace;
    }

    [[nodiscard]] const std::optional<PusherChannels>& get_channels() const {
        return channels;
    }

    [[nodiscard]] const std::optional<PusherOptions>& get_options() const {
        return options;
    }

    bool operator==(const Impl& rhs) const {
        return key == rhs.key
               && pusher_namespace == rhs.pusher_namespace
               && channels == rhs.channels
               && options == rhs.options;
    }

    bool operator!=(const Impl& rhs) const {
        return !(*this == rhs);
    }

private:
    std::optional<std::string> key;
    std::optional<std::string> pusher_namespace;
    std::optional<PusherChannels> channels;
    std::optional<PusherOptions> options;
};

void Pusher::deserialize(const std::string& json) {
    pimpl->deserialize(json);
}

const std::optional<std::string>& Pusher::get_key() const {
    return pimpl->get_key();
}

const std::optional<std::string>& Pusher::get_pusher_namespace() const {
    return pimpl->get_pusher_namespace();
}

const std::optional<PusherChannels>& Pusher::get_channels() const {
    return pimpl->get_channels();
}

const std::optional<PusherOptions>& Pusher::get_options() const {
    return pimpl->get_options();
}

bool Pusher::operator==(const Pusher& rhs) const {
    return *pimpl == *rhs.pimpl;
}

bool Pusher::operator!=(const Pusher& rhs) const {
    return *pimpl != *rhs.pimpl;
}

Pusher::Pusher() : pimpl(std::make_unique<Impl>()) {
}

Pusher::Pusher(const Pusher& other) : pimpl(std::make_unique<Impl>(*other.pimpl)) {
}

Pusher::Pusher(Pusher&& other) noexcept = default;

Pusher::~Pusher() = default;

Pusher& Pusher::operator=(const Pusher& rhs) {
    pimpl = std::make_unique<Impl>(*rhs.pimpl);
    return *this;
}
