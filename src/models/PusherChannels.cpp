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
using namespace enjin::sdk::utils;

void PusherChannels::deserialize(const std::string& json) {
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

const std::optional<std::string>& PusherChannels::get_project() const {
    return project;
}

const std::optional<std::string>& PusherChannels::get_player() const {
    return player;
}

const std::optional<std::string>& PusherChannels::get_asset() const {
    return asset;
}

const std::optional<std::string>& PusherChannels::get_wallet() const {
    return wallet;
}

bool PusherChannels::operator==(const PusherChannels& rhs) const {
    return project == rhs.project
           && player == rhs.player
           && asset == rhs.asset
           && wallet == rhs.wallet;
}

bool PusherChannels::operator!=(const PusherChannels& rhs) const {
    return !(*this == rhs);
}
