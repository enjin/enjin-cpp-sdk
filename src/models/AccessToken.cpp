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

const std::optional<std::string>& AccessToken::get_token() const {
    return token;
}

const std::optional<long>& AccessToken::get_expires_in() const {
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
