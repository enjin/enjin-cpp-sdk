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

#include "enjinsdk/JsonUtils.hpp"
#include "enjinsdk/JsonValue.hpp"

using namespace enjin::sdk::json;
using namespace enjin::sdk::models;
using namespace enjin::sdk::serialization;
using namespace enjin::sdk::utils;

class Player::Impl final : public IDeserializable {
public:
    Impl() = default;

    ~Impl() override = default;

    void deserialize(const std::string& json) override {
        JsonValue json_object;

        if (!json_object.try_parse_as_object(json)) {
            id.reset();
            linking_info.reset();
            wallet.reset();
            created_at.reset();
            updated_at.reset();

            return;
        }

        JsonUtils::try_get_field(json_object, "id", id);
        JsonUtils::try_get_field(json_object, "linkingInfo", linking_info);
        JsonUtils::try_get_field(json_object, "wallet", wallet);
        JsonUtils::try_get_field(json_object, "createdAt", created_at);
        JsonUtils::try_get_field(json_object, "updatedAt", updated_at);
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
};

Player::Player() : pimpl(std::make_unique<Impl>()) {
}

Player::Player(const Player& other) : pimpl(std::make_unique<Impl>(*other.pimpl)) {
}

Player::Player(Player&& other) noexcept = default;

Player::~Player() = default;

void Player::deserialize(const std::string& json) {
    pimpl->deserialize(json);
}

const std::optional<std::string>& Player::get_id() const {
    return pimpl->get_id();
}

const std::optional<LinkingInfo>& Player::get_linking_info() const {
    return pimpl->get_linking_info();
}

const std::optional<Wallet>& Player::get_wallet() const {
    return pimpl->get_wallet();
}

const std::optional<std::string>& Player::get_created_at() const {
    return pimpl->get_created_at();
}

const std::optional<std::string>& Player::get_updated_at() const {
    return pimpl->get_updated_at();
}

bool Player::operator==(const Player& rhs) const {
    return *pimpl == *rhs.pimpl;
}

bool Player::operator!=(const Player& rhs) const {
    return *pimpl != *rhs.pimpl;
}

Player& enjin::sdk::models::Player::operator=(const Player& rhs) {
    pimpl = std::make_unique<Impl>(*rhs.pimpl);
    return *this;
}
