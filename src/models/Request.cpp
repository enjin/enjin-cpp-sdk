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

#include "enjinsdk/JsonUtils.hpp"
#include "enjinsdk/JsonValue.hpp"

using namespace enjin::sdk::json;
using namespace enjin::sdk::models;
using namespace enjin::sdk::serialization;
using namespace enjin::sdk::utils;

class Request::Impl : public IDeserializable {
public:
    Impl() = default;

    ~Impl() override = default;

    void deserialize(const std::string& json) override {
        JsonValue json_object;

        if (!json_object.try_parse_as_object(json)) {
            id.reset();
            transaction_id.reset();
            title.reset();
            contract.reset();
            type.reset();
            value.reset();
            retry_state.reset();
            state.reset();
            accepted.reset();
            project_wallet.reset();
            blockchain_data.reset();
            project.reset();
            asset.reset();
            wallet.reset();
            created_at.reset();
            updated_at.reset();

            return;
        }

        JsonUtils::try_get_field(json_object, "id", id);
        JsonUtils::try_get_field(json_object, "transactionId", transaction_id);
        JsonUtils::try_get_field(json_object, "title", title);
        JsonUtils::try_get_field(json_object, "contract", contract);
        JsonUtils::try_get_field(json_object, "type", type);
        JsonUtils::try_get_field(json_object, "value", value);
        JsonUtils::try_get_field(json_object, "retryState", retry_state);
        JsonUtils::try_get_field(json_object, "state", state);
        JsonUtils::try_get_field(json_object, "accepted", accepted);
        JsonUtils::try_get_field(json_object, "projectWallet", project_wallet);
        JsonUtils::try_get_field(json_object, "blockchainData", blockchain_data);
        JsonUtils::try_get_field(json_object, "project", project);
        JsonUtils::try_get_field(json_object, "asset", asset);
        JsonUtils::try_get_field(json_object, "wallet", wallet);
        JsonUtils::try_get_field(json_object, "createdAt", created_at);
        JsonUtils::try_get_field(json_object, "updatedAt", updated_at);
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
    return *impl != *rhs.impl;
}

Request& Request::operator=(const Request& rhs) {
    impl = std::make_unique<Impl>(*rhs.impl);
    return *this;
}
