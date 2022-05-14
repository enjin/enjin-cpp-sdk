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

using namespace enjin::sdk::models;
using namespace enjin::sdk::serialization;
using namespace enjin::sdk::utils;

class Balance::Impl : public IDeserializable {
public:
    Impl() = default;

    ~Impl() override = default;

    void deserialize(const std::string& json) override {
        rapidjson::Document document;
        document.Parse(json.c_str());

        if (!document.IsObject()) {
            return;
        }

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
            project.emplace(get_object_as_type<Project>(document, PROJECT_KEY));
        }

        if (document.HasMember(WALLET_KEY) && document[WALLET_KEY].IsObject()) {
            wallet.emplace(get_object_as_type<Wallet>(document, WALLET_KEY));
        }
    }

    [[nodiscard]] const std::optional<std::string>& get_id() const {
        return id;
    }

    [[nodiscard]] const std::optional<std::string>& get_index() const {
        return index;
    }

    [[nodiscard]] const std::optional<int>& get_value() const {
        return value;
    }

    [[nodiscard]] const std::optional<Project>& get_project() const {
        return project;
    }

    [[nodiscard]] const std::optional<Wallet>& get_wallet() const {
        return wallet;
    }

    bool operator==(const Impl& rhs) const {
        return id == rhs.id
               && index == rhs.index
               && value == rhs.value
               && project == rhs.project
               && wallet == rhs.wallet;
    }

    bool operator!=(const Impl& rhs) const {
        return !(*this == rhs);
    }

private:
    std::optional<std::string> id;
    std::optional<std::string> index;
    std::optional<int> value;
    std::optional<Project> project;
    std::optional<Wallet> wallet;

    constexpr static char ID_KEY[] = "id";
    constexpr static char INDEX_KEY[] = "index";
    constexpr static char VALUE_KEY[] = "value";
    constexpr static char PROJECT_KEY[] = "project";
    constexpr static char WALLET_KEY[] = "wallet";
};

Balance::Balance() : impl(std::make_unique<Impl>()) {
}

Balance::Balance(const Balance& other) {
    impl = std::make_unique<Impl>(*other.impl);
}

Balance::Balance(Balance&& other) noexcept = default;

Balance::~Balance() = default;

void Balance::deserialize(const std::string& json) {
    impl->deserialize(json);
}

const std::optional<std::string>& Balance::get_id() const {
    return impl->get_id();
}

const std::optional<std::string>& Balance::get_index() const {
    return impl->get_index();
}

const std::optional<int>& Balance::get_value() const {
    return impl->get_value();
}

const std::optional<Project>& Balance::get_project() const {
    return impl->get_project();
}

const std::optional<Wallet>& Balance::get_wallet() const {
    return impl->get_wallet();
}

bool Balance::operator==(const Balance& rhs) const {
    return *impl == *rhs.impl;
}

bool Balance::operator!=(const Balance& rhs) const {
    return !(*this == rhs);
}
