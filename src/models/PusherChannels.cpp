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

#include "enjinsdk/models/PusherChannels.hpp"

#include "rapidjson/document.h"

namespace enjin::sdk::models {

void PusherChannels::deserialize(const std::string& json) {
    rapidjson::Document document;
    document.Parse(json.c_str());
    if (document.IsObject()) {
        if (document.HasMember(PROJECT_KEY) && document[PROJECT_KEY].IsString()) {
            project.emplace(document[PROJECT_KEY].GetString());
        }
        if (document.HasMember(PLAYER_KEY) && document[PLAYER_KEY].IsString()) {
            player.emplace(document[PLAYER_KEY].GetString());
        }
        if (document.HasMember(ASSET_KEY) && document[ASSET_KEY].IsString()) {
            asset.emplace(document[ASSET_KEY].GetString());
        }
        if (document.HasMember(WALLET_KEY) && document[WALLET_KEY].IsString()) {
            wallet.emplace(document[WALLET_KEY].GetString());
        }
    }
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
    return project == rhs.project &&
           player == rhs.player &&
           asset == rhs.asset &&
           wallet == rhs.wallet;
}

bool PusherChannels::operator!=(const PusherChannels& rhs) const {
    return !(rhs == *this);
}

}
