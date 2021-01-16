#include "enjinsdk/models/Player.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::models {

void Player::deserialize(const std::string& json) {
    rapidjson::Document document;
    document.Parse(json.c_str());
    if (document.IsObject()) {
        if (document.HasMember(ID_KEY) && document[ID_KEY].IsString()) {
            id.emplace(document[ID_KEY].GetString());
        }
        if (document.HasMember(LINKING_INFO_KEY) && document[LINKING_INFO_KEY].IsObject()) {
            linking_info.emplace(utils::get_object_as_type<LinkingInfo>(document, LINKING_INFO_KEY));
        }
        if (document.HasMember(WALLET_KEY) && document[WALLET_KEY].IsObject()) {
            wallet.emplace(utils::get_object_as_type<Wallet>(document, WALLET_KEY));
        }
        if (document.HasMember(CREATED_AT_KEY) && document[CREATED_AT_KEY].IsString()) {
            created_at.emplace(document[CREATED_AT_KEY].GetString());
        }
        if (document.HasMember(UPDATED_AT_KEY) && document[UPDATED_AT_KEY].IsString()) {
            updated_at.emplace(document[UPDATED_AT_KEY].GetString());
        }
    }
}

const std::optional<std::string>& Player::get_id() const {
    return id;
}

const std::optional<LinkingInfo>& Player::get_linking_info() const {
    return linking_info;
}

const std::optional<Wallet>& Player::get_wallet() const {
    return wallet;
}

const std::optional<std::string>& Player::get_created_at() const {
    return created_at;
}

const std::optional<std::string>& Player::get_updated_at() const {
    return updated_at;
}

bool Player::operator==(const Player& rhs) const {
    return id == rhs.id &&
           linking_info == rhs.linking_info &&
           wallet == rhs.wallet &&
           created_at == rhs.created_at &&
           updated_at == rhs.updated_at;
}

bool Player::operator!=(const Player& rhs) const {
    return !(rhs == *this);
}

}
