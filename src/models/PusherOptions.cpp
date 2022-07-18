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

#include "enjinsdk/models/PusherOptions.hpp"

#include "enjinsdk/JsonUtils.hpp"
#include "enjinsdk/JsonValue.hpp"

using namespace enjin::sdk::json;
using namespace enjin::sdk::models;
using namespace enjin::sdk::serialization;
using namespace enjin::sdk::utils;

class PusherOptions::Impl final : public IDeserializable {
public:
    Impl() = default;

    ~Impl() override = default;

    void deserialize(const std::string& json) override {
        JsonValue json_object;

        if (!json_object.try_parse_as_object(json)) {
            cluster.reset();
            encrypted.reset();

            return;
        }

        JsonUtils::try_get_field(json_object, "cluster", cluster);
        JsonUtils::try_get_field(json_object, "encrypted", encrypted);
    }

    [[nodiscard]] const std::optional<std::string>& get_cluster() const {
        return cluster;
    }

    [[nodiscard]] const std::optional<bool>& get_encrypted() const {
        return encrypted;
    }

    bool operator==(const Impl& rhs) const {
        return cluster == rhs.cluster
               && encrypted == rhs.encrypted;
    }

    bool operator!=(const Impl& rhs) const {
        return !(*this == rhs);
    }

private:
    std::optional<std::string> cluster;
    std::optional<bool> encrypted;
};

PusherOptions::PusherOptions() : pimpl(std::make_unique<Impl>()) {
}

PusherOptions::PusherOptions(const PusherOptions& other) : pimpl(std::make_unique<Impl>(*other.pimpl)) {
}

PusherOptions::PusherOptions(PusherOptions&& other) noexcept = default;

PusherOptions::~PusherOptions() = default;

void PusherOptions::deserialize(const std::string& json) {
    pimpl->deserialize(json);
}

const std::optional<std::string>& PusherOptions::get_cluster() const {
    return pimpl->get_cluster();
}

const std::optional<bool>& PusherOptions::get_encrypted() const {
    return pimpl->get_encrypted();
}

bool PusherOptions::operator==(const PusherOptions& rhs) const {
    return *pimpl == *rhs.pimpl;
}

bool PusherOptions::operator!=(const PusherOptions& rhs) const {
    return *pimpl != *rhs.pimpl;
}

PusherOptions& PusherOptions::operator=(const PusherOptions& rhs) {
    pimpl = std::make_unique<Impl>(*rhs.pimpl);
    return *this;
}
