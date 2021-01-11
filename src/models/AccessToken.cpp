#include "enjinsdk/models/AccessToken.hpp"
#include "rapidjson/document.h"

namespace enjin::sdk::models {

void AccessToken::deserialize(const std::string& json) {
    rapidjson::Document document;
    document.Parse(json.c_str());
    if (document.IsObject()) {
        if (document.HasMember(TOKEN_KEY) && document[TOKEN_KEY].IsString()) {
            token.emplace(document[TOKEN_KEY].GetString());
        }
        if (document.HasMember(EXPIRES_IN_KEY) && document[EXPIRES_IN_KEY].IsInt()) {
            expires_in.emplace(document[EXPIRES_IN_KEY].GetInt());
        }
    }
}

std::optional<std::string> AccessToken::get_token() {
    return token;
}

std::optional<long> AccessToken::get_expires_in() {
    return expires_in;
}

bool AccessToken::operator==(const AccessToken& rhs) const {
    return token == rhs.token &&
           expires_in == rhs.expires_in;
}

bool AccessToken::operator!=(const AccessToken& rhs) const {
    return !(rhs == *this);
}

}
