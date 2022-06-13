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

#include "enjinsdk/JsonUtils.hpp"
#include "enjinsdk/JsonValue.hpp"

using namespace enjin::sdk::json;
using namespace enjin::sdk::models;
using namespace enjin::sdk::serialization;
using namespace enjin::sdk::utils;

class Balance::Impl : public IDeserializable {
public:
    Impl() = default;

    ~Impl() override = default;

    void deserialize(const std::string& json) override {
        JsonValue json_object;

        if (!json_object.try_parse_as_object(json)) {
            id.reset();
            index.reset();
            value.reset();
            project.reset();
            wallet.reset();

            return;
        }

        JsonUtils::try_get_field(json_object, "id", id);
        JsonUtils::try_get_field(json_object, "index", index);
        JsonUtils::try_get_field(json_object, "value", value);
        JsonUtils::try_get_field(json_object, "project", project);
        JsonUtils::try_get_field(json_object, "wallet", wallet);
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
    return *impl != *rhs.impl;
}

Balance& enjin::sdk::models::Balance::operator=(const Balance& rhs) {
    impl = std::make_unique<Impl>(*rhs.impl);
    return *this;
}
