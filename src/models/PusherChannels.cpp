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
