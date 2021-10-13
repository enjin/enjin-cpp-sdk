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

#include "enjinsdk/models/Request.hpp"

#include "EnumUtils.hpp"
#include "RapidJsonUtils.hpp"

namespace enjin::sdk::models {

void Request::deserialize(const std::string& json) {
    rapidjson::Document document;
    document.Parse(json.c_str());
    if (document.IsObject()) {
        if (document.HasMember(ID_KEY) && document[ID_KEY].IsInt()) {
            id.emplace(document[ID_KEY].GetInt());
        }
        if (document.HasMember(TRANSACTION_ID_KEY) && document[TRANSACTION_ID_KEY].IsString()) {
            transaction_id.emplace(document[TRANSACTION_ID_KEY].GetString());
        }
        if (document.HasMember(TITLE_KEY) && document[TITLE_KEY].IsString()) {
            title.emplace(document[TITLE_KEY].GetString());
        }
        if (document.HasMember(CONTRACT_KEY) && document[CONTRACT_KEY].IsString()) {
            contract.emplace(document[CONTRACT_KEY].GetString());
        }
        if (document.HasMember(TYPE_KEY) && document[TYPE_KEY].IsString()) {
            type.emplace(utils::deserialize_request_type(document[TYPE_KEY].GetString()));
        }
        if (document.HasMember(VALUE_KEY) && document[VALUE_KEY].IsString()) {
            value.emplace(document[VALUE_KEY].GetString());
        }
        if (document.HasMember(RETRY_STATE_KEY) && document[RETRY_STATE_KEY].IsString()) {
            retry_state.emplace(document[RETRY_STATE_KEY].GetString());
        }
        if (document.HasMember(STATE_KEY) && document[STATE_KEY].IsString()) {
            state.emplace(utils::deserialize_request_state(document[STATE_KEY].GetString()));
        }
        if (document.HasMember(ACCEPTED_KEY) && document[ACCEPTED_KEY].IsBool()) {
            accepted.emplace(document[ACCEPTED_KEY].GetBool());
        }
        if (document.HasMember(PROJECT_WALLET_KEY) && document[PROJECT_WALLET_KEY].IsBool()) {
            project_wallet.emplace(document[PROJECT_WALLET_KEY].GetBool());
        }
        if (document.HasMember(BLOCKCHAIN_DATA_KEY) && document[BLOCKCHAIN_DATA_KEY].IsObject()) {
            blockchain_data.emplace(utils::get_object_as_type<BlockchainData>(document, BLOCKCHAIN_DATA_KEY));
        }
        if (document.HasMember(PROJECT_KEY) && document[PROJECT_KEY].IsObject()) {
            project.emplace(utils::get_object_as_type<Project>(document, PROJECT_KEY));
        }
        if (document.HasMember(ASSET_KEY) && document[ASSET_KEY].IsObject()) {
            asset.emplace(utils::get_object_as_type<Asset>(document, ASSET_KEY));
        }
        if (document.HasMember(CREATED_AT_KEY) && document[CREATED_AT_KEY].IsString()) {
            created_at.emplace(document[CREATED_AT_KEY].GetString());
        }
        if (document.HasMember(UPDATED_AT_KEY) && document[UPDATED_AT_KEY].IsString()) {
            updated_at.emplace(document[UPDATED_AT_KEY].GetString());
        }
    }
}

const std::optional<int>& Request::get_id() const {
    return id;
}

const std::optional<std::string>& Request::get_transaction_id() const {
    return transaction_id;
}

const std::optional<std::string>& Request::get_title() const {
    return title;
}

const std::optional<std::string>& Request::get_contract() const {
    return contract;
}

const std::optional<RequestType>& Request::get_type() const {
    return type;
}

const std::optional<std::string>& Request::get_value() const {
    return value;
}

const std::optional<std::string>& Request::get_retry_state() const {
    return retry_state;
}

const std::optional<RequestState>& Request::get_state() const {
    return state;
}

const std::optional<bool>& Request::get_accepted() const {
    return accepted;
}

const std::optional<bool>& Request::get_project_wallet() const {
    return project_wallet;
}

const std::optional<BlockchainData>& Request::get_blockchain_data() const {
    return blockchain_data;
}

const std::optional<Project>& Request::get_project() const {
    return project;
}

const std::optional<Asset>& Request::get_asset() const {
    return asset;
}

const std::optional<std::string>& Request::get_created_at() const {
    return created_at;
}

const std::optional<std::string>& Request::get_updated_at() const {
    return updated_at;
}

bool Request::operator==(const Request& rhs) const {
    return id == rhs.id &&
           transaction_id == rhs.transaction_id &&
           title == rhs.title &&
           contract == rhs.contract &&
           type == rhs.type &&
           value == rhs.value &&
           retry_state == rhs.retry_state &&
           state == rhs.state &&
           accepted == rhs.accepted &&
           blockchain_data == rhs.blockchain_data &&
           project == rhs.project &&
           created_at == rhs.created_at &&
           updated_at == rhs.updated_at;
}

bool Request::operator!=(const Request& rhs) const {
    return !(rhs == *this);
}

}
