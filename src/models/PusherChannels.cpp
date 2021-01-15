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
        if (document.HasMember(TOKEN_KEY) && document[TOKEN_KEY].IsString()) {
            token.emplace(document[TOKEN_KEY].GetString());
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

const std::optional<std::string>& PusherChannels::get_token() const {
    return token;
}

const std::optional<std::string>& PusherChannels::get_wallet() const {
    return wallet;
}

bool PusherChannels::operator==(const PusherChannels& rhs) const {
    return project == rhs.project &&
           player == rhs.player &&
           token == rhs.token &&
           wallet == rhs.wallet;
}

bool PusherChannels::operator!=(const PusherChannels& rhs) const {
    return !(rhs == *this);
}

}
