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

#include "enjinsdk/models/AssetFilter.hpp"

#include "enjinsdk/JsonUtils.hpp"

using namespace enjin::sdk::json;
using namespace enjin::sdk::models;
using namespace enjin::sdk::serialization;
using namespace enjin::sdk::utils;

class AssetFilter::Impl final : public ISerializable {
public:
    Impl() = default;

    ~Impl() override = default;

    [[nodiscard]] std::string serialize() const override {
        return to_json().to_string();
    }

    void set_and(std::vector<AssetFilter> others) {
        and_filters_opt = std::move(others);
    }

    void set_or(std::vector<AssetFilter> others) {
        or_filters_opt = std::move(others);
    }

    void set_id(std::string id) {
        id_opt = std::move(id);
    }

    void set_id_in(std::vector<std::string> ids) {
        id_in_opt = std::move(ids);
    }

    void set_name(std::string name) {
        name_opt = std::move(name);
    }

    void set_name_contains(std::string text) {
        name_contains_opt = std::move(text);
    }

    void set_name_in(std::vector<std::string> names) {
        name_in_opt = std::move(names);
    }

    void set_name_starts_with(std::string prefix) {
        name_starts_with_opt = std::move(prefix);
    }

    void set_name_ends_with(std::string suffix) {
        name_ends_with_opt = std::move(suffix);
    }

    void set_wallet(std::string wallet) {
        wallet_opt = std::move(wallet);
    }

    void set_wallet_in(std::vector<std::string> wallets) {
        wallet_in_opt = std::move(wallets);
    }

    [[nodiscard]] json::JsonValue to_json() const override {
        JsonValue json = JsonValue::create_object();

        JsonUtils::try_set_field(json, "and", and_filters_opt);
        JsonUtils::try_set_field(json, "or", or_filters_opt);
        JsonUtils::try_set_field(json, "id", id_opt);
        JsonUtils::try_set_field(json, "id_in", id_in_opt);
        JsonUtils::try_set_field(json, "name", name_opt);
        JsonUtils::try_set_field(json, "name_contains", name_contains_opt);
        JsonUtils::try_set_field(json, "name_in", name_in_opt);
        JsonUtils::try_set_field(json, "name_starts_with", name_starts_with_opt);
        JsonUtils::try_set_field(json, "name_ends_with", name_ends_with_opt);
        JsonUtils::try_set_field(json, "wallet", wallet_opt);
        JsonUtils::try_set_field(json, "wallet_in", wallet_in_opt);

        return json;
    }

    bool operator==(const Impl& rhs) const {
        return and_filters_opt == rhs.and_filters_opt
               && or_filters_opt == rhs.or_filters_opt
               && id_opt == rhs.id_opt
               && id_in_opt == rhs.id_in_opt
               && name_opt == rhs.name_opt
               && name_contains_opt == rhs.name_contains_opt
               && name_in_opt == rhs.name_in_opt
               && name_starts_with_opt == rhs.name_starts_with_opt
               && name_ends_with_opt == rhs.name_ends_with_opt
               && wallet_opt == rhs.wallet_opt
               && wallet_in_opt == rhs.wallet_in_opt;
    }

    bool operator!=(const Impl& rhs) const {
        return !(*this == rhs);
    }

private:
    std::optional<std::vector<AssetFilter>> and_filters_opt;
    std::optional<std::vector<AssetFilter>> or_filters_opt;
    std::optional<std::string> id_opt;
    std::optional<std::vector<std::string>> id_in_opt;
    std::optional<std::string> name_opt;
    std::optional<std::string> name_contains_opt;
    std::optional<std::vector<std::string>> name_in_opt;
    std::optional<std::string> name_starts_with_opt;
    std::optional<std::string> name_ends_with_opt;
    std::optional<std::string> wallet_opt;
    std::optional<std::vector<std::string>> wallet_in_opt;
};

AssetFilter::AssetFilter() : pimpl(std::make_unique<Impl>()) {
}

AssetFilter::AssetFilter(const AssetFilter& other) : pimpl(std::make_unique<Impl>(*other.pimpl)) {
}

AssetFilter::AssetFilter(AssetFilter&& other) noexcept = default;

AssetFilter::~AssetFilter() = default;

std::string AssetFilter::serialize() const {
    return pimpl->serialize();
}

AssetFilter& AssetFilter::set_and(std::vector<AssetFilter> others) {
    pimpl->set_and(std::move(others));
    return *this;
}

AssetFilter& AssetFilter::set_or(std::vector<AssetFilter> others) {
    pimpl->set_or(std::move(others));
    return *this;
}

AssetFilter& AssetFilter::set_id(std::string id) {
    pimpl->set_id(std::move(id));
    return *this;
}

AssetFilter& AssetFilter::set_id_in(std::vector<std::string> ids) {
    pimpl->set_id_in(std::move(ids));
    return *this;
}

AssetFilter& AssetFilter::set_name(std::string name) {
    pimpl->set_name(std::move(name));
    return *this;
}

AssetFilter& AssetFilter::set_name_contains(std::string text) {
    pimpl->set_name_contains(std::move(text));
    return *this;
}

AssetFilter& AssetFilter::set_name_in(std::vector<std::string> names) {
    pimpl->set_name_in(std::move(names));
    return *this;
}

AssetFilter& AssetFilter::set_name_starts_with(std::string prefix) {
    pimpl->set_name_starts_with(std::move(prefix));
    return *this;
}

AssetFilter& AssetFilter::set_name_ends_with(std::string suffix) {
    pimpl->set_name_ends_with(std::move(suffix));
    return *this;
}

AssetFilter& AssetFilter::set_wallet(std::string wallet) {
    pimpl->set_wallet(std::move(wallet));
    return *this;
}

AssetFilter& AssetFilter::set_wallet_in(std::vector<std::string> wallets) {
    pimpl->set_wallet_in(std::move(wallets));
    return *this;
}

JsonValue AssetFilter::to_json() const {
    return pimpl->to_json();
}

bool AssetFilter::operator==(const AssetFilter& rhs) const {
    return *pimpl == *rhs.pimpl;
}

bool AssetFilter::operator!=(const AssetFilter& rhs) const {
    return *pimpl != *rhs.pimpl;
}

AssetFilter& AssetFilter::operator=(const AssetFilter& rhs) {
    pimpl = std::make_unique<Impl>(*rhs.pimpl);
    return *this;
}
