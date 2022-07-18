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

#include "enjinsdk/models/PusherChannels.hpp"

#include "enjinsdk/JsonUtils.hpp"
#include "enjinsdk/JsonValue.hpp"

using namespace enjin::sdk::json;
using namespace enjin::sdk::models;
using namespace enjin::sdk::serialization;
using namespace enjin::sdk::utils;

class PusherChannels::Impl final : public IDeserializable {
public:
    Impl() = default;

    ~Impl() override = default;

    void deserialize(const std::string& json) override {
        JsonValue json_object;

        if (!json_object.try_parse_as_object(json)) {
            project.reset();
            player.reset();
            asset.reset();
            wallet.reset();

            return;
        }

        JsonUtils::try_get_field(json_object, "project", project);
        JsonUtils::try_get_field(json_object, "player", player);
        JsonUtils::try_get_field(json_object, "asset", asset);
        JsonUtils::try_get_field(json_object, "wallet", wallet);
    }

    [[nodiscard]] const std::optional<std::string>& get_project() const {
        return project;
    }

    [[nodiscard]] const std::optional<std::string>& get_player() const {
        return player;
    }

    [[nodiscard]] const std::optional<std::string>& get_asset() const {
        return asset;
    }

    [[nodiscard]] const std::optional<std::string>& get_wallet() const {
        return wallet;
    }

    bool operator==(const Impl& rhs) const {
        return project == rhs.project
               && player == rhs.player
               && asset == rhs.asset
               && wallet == rhs.wallet;
    }

    bool operator!=(const Impl& rhs) const {
        return !(*this == rhs);
    }

private:
    std::optional<std::string> project;
    std::optional<std::string> player;
    std::optional<std::string> asset;
    std::optional<std::string> wallet;
};

PusherChannels::PusherChannels() : pimpl(std::make_unique<Impl>()) {
}

PusherChannels::PusherChannels(const PusherChannels& other) : pimpl(std::make_unique<Impl>(*other.pimpl)) {
}

PusherChannels::PusherChannels(PusherChannels&& other) noexcept = default;

PusherChannels::~PusherChannels() = default;

void PusherChannels::deserialize(const std::string& json) {
    pimpl->deserialize(json);
}

const std::optional<std::string>& PusherChannels::get_project() const {
    return pimpl->get_project();
}

const std::optional<std::string>& PusherChannels::get_player() const {
    return pimpl->get_player();
}

const std::optional<std::string>& PusherChannels::get_asset() const {
    return pimpl->get_asset();
}

const std::optional<std::string>& PusherChannels::get_wallet() const {
    return pimpl->get_wallet();
}

bool PusherChannels::operator==(const PusherChannels& rhs) const {
    return *pimpl == *rhs.pimpl;
}

bool PusherChannels::operator!=(const PusherChannels& rhs) const {
    return *pimpl != *rhs.pimpl;
}

PusherChannels& PusherChannels::operator=(const PusherChannels& rhs) {
    pimpl = std::make_unique<Impl>(*rhs.pimpl);
    return *this;
}
