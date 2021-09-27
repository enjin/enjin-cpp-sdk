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

#include "enjinsdk/models/Balance.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::models {

void Balance::deserialize(const std::string& json) {
    rapidjson::Document document;
    document.Parse(json.c_str());
    if (document.IsObject()) {
        if (document.HasMember(ID_KEY) && document[ID_KEY].IsString()) {
            id.emplace(document[ID_KEY].GetString());
        }
        if (document.HasMember(INDEX_KEY) && document[INDEX_KEY].IsString()) {
            index.emplace(document[INDEX_KEY].GetString());
        }
        if (document.HasMember(VALUE_KEY) && document[VALUE_KEY].IsInt()) {
            value.emplace(document[VALUE_KEY].GetInt());
        }
        if (document.HasMember(PROJECT_KEY) && document[PROJECT_KEY].IsObject()) {
            project.emplace(utils::get_object_as_type<Project>(document, PROJECT_KEY));
        }
        if (document.HasMember(WALLET_KEY) && document[WALLET_KEY].IsObject()) {
            wallet.emplace(utils::get_object_as_type<Wallet>(document, WALLET_KEY));
        }
    }
}

const std::optional<std::string>& Balance::get_id() const {
    return id;
}

const std::optional<std::string>& Balance::get_index() const {
    return index;
}

const std::optional<int>& Balance::get_value() const {
    return value;
}

const std::optional<Project>& Balance::get_project() const {
    return project;
}

const std::optional<Wallet>& Balance::get_wallet() const {
    return wallet;
}

bool Balance::operator==(const Balance& rhs) const {
    return id == rhs.id &&
           index == rhs.index &&
           value == rhs.value &&
           project == rhs.project &&
           wallet == rhs.wallet;
}

bool Balance::operator!=(const Balance& rhs) const {
    return !(rhs == *this);
}

}
