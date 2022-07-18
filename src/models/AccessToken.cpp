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

#include "enjinsdk/models/AccessToken.hpp"

#include "enjinsdk/JsonUtils.hpp"
#include "enjinsdk/JsonValue.hpp"

using namespace enjin::sdk::json;
using namespace enjin::sdk::models;
using namespace enjin::sdk::serialization;
using namespace enjin::sdk::utils;

class AccessToken::Impl final : public IDeserializable {
public:
    Impl() = default;

    ~Impl() override = default;

    void deserialize(const std::string& json) override {
        JsonValue json_object;

        if (!json_object.try_parse_as_object(json)) {
            token.reset();
            expires_in.reset();

            return;
        }

        JsonUtils::try_get_field(json_object, "accessToken", token);
        JsonUtils::try_get_field(json_object, "expiresIn", expires_in);
    }

    [[nodiscard]] const std::optional<std::string>& get_token() const {
        return token;
    }

    [[nodiscard]] const std::optional<long>& get_expires_in() const {
        return expires_in;
    }

    bool operator==(const Impl& rhs) const {
        return token == rhs.token
               && expires_in == rhs.expires_in;
    }

    bool operator!=(const Impl& rhs) const {
        return !(*this == rhs);
    }

private:
    std::optional<std::string> token;
    std::optional<long> expires_in;
};

AccessToken::AccessToken() : pimpl(std::make_unique<Impl>()) {
}

AccessToken::AccessToken(const AccessToken& other) : pimpl(std::make_unique<Impl>(*other.pimpl)) {
}

AccessToken::AccessToken(AccessToken&& other) noexcept = default;

AccessToken::~AccessToken() = default;

void AccessToken::deserialize(const std::string& json) {
    pimpl->deserialize(json);
}

const std::optional<std::string>& AccessToken::get_token() const {
    return pimpl->get_token();
}

const std::optional<long>& AccessToken::get_expires_in() const {
    return pimpl->get_expires_in();
}

bool AccessToken::operator==(const AccessToken& rhs) const {
    return *pimpl == *rhs.pimpl;
}

bool AccessToken::operator!=(const AccessToken& rhs) const {
    return *pimpl != *rhs.pimpl;
}

AccessToken& AccessToken::operator=(const AccessToken& rhs) {
    pimpl = std::make_unique<Impl>(*rhs.pimpl);
    return *this;
}
