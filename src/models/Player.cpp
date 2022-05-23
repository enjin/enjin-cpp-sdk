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

#include "enjinsdk/models/Player.hpp"

#include "RapidJsonUtils.hpp"

using namespace enjin::sdk::models;
using namespace enjin::sdk::serialization;
using namespace enjin::sdk::utils;

class Player::Impl : public IDeserializable {
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

        if (document.HasMember(LINKING_INFO_KEY) && document[LINKING_INFO_KEY].IsObject()) {
            linking_info.emplace(get_object_as_type<LinkingInfo>(document, LINKING_INFO_KEY));
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

    [[nodiscard]] const std::optional<std::string>& get_id() const {
        return id;
    }

    [[nodiscard]] const std::optional<LinkingInfo>& get_linking_info() const {
        return linking_info;
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
               && linking_info == rhs.linking_info
               && wallet == rhs.wallet
               && created_at == rhs.created_at
               && updated_at == rhs.updated_at;
    }

    bool operator!=(const Impl& rhs) const {
        return !(*this == rhs);
    }

private:
    std::optional<std::string> id;
    std::optional<LinkingInfo> linking_info;
    std::optional<Wallet> wallet;
    std::optional<std::string> created_at;
    std::optional<std::string> updated_at;

    constexpr static char ID_KEY[] = "id";
    constexpr static char LINKING_INFO_KEY[] = "linkingInfo";
    constexpr static char WALLET_KEY[] = "wallet";
    constexpr static char CREATED_AT_KEY[] = "createdAt";
    constexpr static char UPDATED_AT_KEY[] = "updatedAt";
};

Player::Player() : impl(std::make_unique<Impl>()) {
}

Player::Player(const Player& other) {
    impl = std::make_unique<Impl>(*other.impl);
}

Player::Player(Player&& other) noexcept = default;

Player::~Player() = default;

void Player::deserialize(const std::string& json) {
    impl->deserialize(json);
}

const std::optional<std::string>& Player::get_id() const {
    return impl->get_id();
}

const std::optional<LinkingInfo>& Player::get_linking_info() const {
    return impl->get_linking_info();
}

const std::optional<Wallet>& Player::get_wallet() const {
    return impl->get_wallet();
}

const std::optional<std::string>& Player::get_created_at() const {
    return impl->get_created_at();
}

const std::optional<std::string>& Player::get_updated_at() const {
    return impl->get_updated_at();
}

bool Player::operator==(const Player& rhs) const {
    return *impl == *rhs.impl;
}

bool Player::operator!=(const Player& rhs) const {
    return !(*this == rhs);
}

Player& enjin::sdk::models::Player::operator=(const Player& rhs) {
    impl = std::make_unique<Impl>(*rhs.impl);
    return *this;
}
