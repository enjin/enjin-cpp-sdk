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

using namespace enjin::sdk::models;
using namespace enjin::sdk::serialization;
using namespace enjin::sdk::utils;

class Request::Impl : public IDeserializable {
public:
    Impl() = default;

    ~Impl() override = default;

    void deserialize(const std::string& json) override {
        rapidjson::Document document;
        document.Parse(json.c_str());

        if (!document.IsObject()) {
            return;
        }

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
            state.emplace(deserialize_request_state(document[STATE_KEY].GetString()));
        }

        if (document.HasMember(ACCEPTED_KEY) && document[ACCEPTED_KEY].IsBool()) {
            accepted.emplace(document[ACCEPTED_KEY].GetBool());
        }

        if (document.HasMember(PROJECT_WALLET_KEY) && document[PROJECT_WALLET_KEY].IsBool()) {
            project_wallet.emplace(document[PROJECT_WALLET_KEY].GetBool());
        }

        if (document.HasMember(BLOCKCHAIN_DATA_KEY) && document[BLOCKCHAIN_DATA_KEY].IsObject()) {
            blockchain_data.emplace(get_object_as_type<BlockchainData>(document, BLOCKCHAIN_DATA_KEY));
        }

        if (document.HasMember(PROJECT_KEY) && document[PROJECT_KEY].IsObject()) {
            project.emplace(get_object_as_type<Project>(document, PROJECT_KEY));
        }

        if (document.HasMember(ASSET_KEY) && document[ASSET_KEY].IsObject()) {
            asset.emplace(get_object_as_type<Asset>(document, ASSET_KEY));
        }

        if (document.HasMember(WALLET_KEY) && document[WALLET_KEY].IsObject()) {
            wallet.emplace(get_object_as_type<Wallet>(document, WALLET_KEY));
        }

        if (document.HasMember(CREATED_AT_KEY) && document[CREATED_AT_KEY].IsString()) {
            created_at.emplace(document[CREATED_AT_KEY].GetString());
        }

        if (document.HasMember(UPDATED_AT_KEY) && document[UPDATED_AT_KEY].IsString()) {
            updated_at.emplace(document[UPDATED_AT_KEY].GetString());
        }
    }

    [[nodiscard]] const std::optional<int>& get_id() const {
        return id;
    }

    [[nodiscard]] const std::optional<std::string>& get_transaction_id() const {
        return transaction_id;
    }

    [[nodiscard]] const std::optional<std::string>& get_title() const {
        return title;
    }

    [[nodiscard]] const std::optional<std::string>& get_contract() const {
        return contract;
    }

    [[nodiscard]] const std::optional<RequestType>& get_type() const {
        return type;
    }

    [[nodiscard]] const std::optional<std::string>& get_value() const {
        return value;
    }

    [[nodiscard]] const std::optional<std::string>& get_retry_state() const {
        return retry_state;
    }

    [[nodiscard]] const std::optional<RequestState>& get_state() const {
        return state;
    }

    [[nodiscard]] const std::optional<bool>& get_accepted() const {
        return accepted;
    }

    [[nodiscard]] const std::optional<bool>& get_project_wallet() const {
        return project_wallet;
    }

    [[nodiscard]] const std::optional<BlockchainData>& get_blockchain_data() const {
        return blockchain_data;
    }

    [[nodiscard]] const std::optional<Project>& get_project() const {
        return project;
    }

    [[nodiscard]] const std::optional<Asset>& get_asset() const {
        return asset;
    }

    [[nodiscard]] const std::optional<Wallet>& get_wallet() const {
        return wallet;
    }

    [[nodiscard]] const std::optional<std::string>& get_created_at() const {
        return created_at;
    }

    [[nodiscard]] const std::optional<std::string>& get_updated_at() const {
        return updated_at;
    }

    bool operator==(const Impl& rhs) const {
        return id == rhs.id
               && transaction_id == rhs.transaction_id
               && title == rhs.title
               && contract == rhs.contract
               && type == rhs.type
               && value == rhs.value
               && retry_state == rhs.retry_state
               && state == rhs.state
               && accepted == rhs.accepted
               && blockchain_data == rhs.blockchain_data
               && project == rhs.project
               && asset == rhs.asset
               && wallet == rhs.wallet
               && created_at == rhs.created_at
               && updated_at == rhs.updated_at;
    }

    bool operator!=(const Impl& rhs) const {
        return !(*this == rhs);
    }

private:
    std::optional<int> id;
    std::optional<std::string> transaction_id;
    std::optional<std::string> title;
    std::optional<std::string> contract;
    std::optional<RequestType> type;
    std::optional<std::string> value;
    std::optional<std::string> retry_state;
    std::optional<RequestState> state;
    std::optional<bool> accepted;
    std::optional<bool> project_wallet;
    std::optional<BlockchainData> blockchain_data;
    std::optional<Project> project;
    std::optional<Asset> asset;
    std::optional<Wallet> wallet;
    std::optional<std::string> created_at;
    std::optional<std::string> updated_at;

    constexpr static char ID_KEY[] = "id";
    constexpr static char TRANSACTION_ID_KEY[] = "transactionId";
    constexpr static char TITLE_KEY[] = "title";
    constexpr static char CONTRACT_KEY[] = "contract";
    constexpr static char TYPE_KEY[] = "type";
    constexpr static char VALUE_KEY[] = "value";
    constexpr static char RETRY_STATE_KEY[] = "retryState";
    constexpr static char STATE_KEY[] = "state";
    constexpr static char ACCEPTED_KEY[] = "accepted";
    constexpr static char PROJECT_WALLET_KEY[] = "projectWallet";
    constexpr static char BLOCKCHAIN_DATA_KEY[] = "blockchainData";
    constexpr static char PROJECT_KEY[] = "project";
    constexpr static char ASSET_KEY[] = "asset";
    constexpr static char WALLET_KEY[] = "wallet";
    constexpr static char CREATED_AT_KEY[] = "createdAt";
    constexpr static char UPDATED_AT_KEY[] = "updatedAt";
};

Request::Request() : impl(std::make_unique<Impl>()) {
}

Request::Request(const Request& other) {
    impl = std::make_unique<Impl>(*other.impl);
}

Request::Request(Request&& other) noexcept = default;

Request::~Request() = default;

void Request::deserialize(const std::string& json) {
    impl->deserialize(json);
}

const std::optional<int>& Request::get_id() const {
    return impl->get_id();
}

const std::optional<std::string>& Request::get_transaction_id() const {
    return impl->get_transaction_id();
}

const std::optional<std::string>& Request::get_title() const {
    return impl->get_title();
}

const std::optional<std::string>& Request::get_contract() const {
    return impl->get_contract();
}

const std::optional<RequestType>& Request::get_type() const {
    return impl->get_type();
}

const std::optional<std::string>& Request::get_value() const {
    return impl->get_value();
}

const std::optional<std::string>& Request::get_retry_state() const {
    return impl->get_retry_state();
}

const std::optional<RequestState>& Request::get_state() const {
    return impl->get_state();
}

const std::optional<bool>& Request::get_accepted() const {
    return impl->get_accepted();
}

const std::optional<bool>& Request::get_project_wallet() const {
    return impl->get_project_wallet();
}

const std::optional<BlockchainData>& Request::get_blockchain_data() const {
    return impl->get_blockchain_data();
}

const std::optional<Project>& Request::get_project() const {
    return impl->get_project();
}

const std::optional<Asset>& Request::get_asset() const {
    return impl->get_asset();
}

const std::optional<Wallet>& Request::get_wallet() const {
    return impl->get_wallet();
}

const std::optional<std::string>& Request::get_created_at() const {
    return impl->get_created_at();
}

const std::optional<std::string>& Request::get_updated_at() const {
    return impl->get_updated_at();
}

bool Request::operator==(const Request& rhs) const {
    return *impl == *rhs.impl;
}

bool Request::operator!=(const Request& rhs) const {
    return !(*this == rhs);
}
