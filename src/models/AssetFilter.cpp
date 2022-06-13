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
using namespace enjin::sdk::utils;

std::string AssetFilter::serialize() const {
    return to_json().to_string();
}

AssetFilter& AssetFilter::set_and(std::vector<AssetFilter> others) {
    and_filters_opt = std::move(others);
    return *this;
}

AssetFilter& AssetFilter::set_or(std::vector<AssetFilter> others) {
    or_filters_opt = std::move(others);
    return *this;
}

AssetFilter& AssetFilter::set_id(std::string id) {
    id_opt = std::move(id);
    return *this;
}

AssetFilter& AssetFilter::set_id_in(std::vector<std::string> ids) {
    id_in_opt = std::move(ids);
    return *this;
}

AssetFilter& AssetFilter::set_name(std::string name) {
    name_opt = std::move(name);
    return *this;
}

AssetFilter& AssetFilter::set_name_contains(std::string text) {
    name_contains_opt = std::move(text);
    return *this;
}

AssetFilter& AssetFilter::set_name_in(std::vector<std::string> names) {
    name_in_opt = std::move(names);
    return *this;
}

AssetFilter& AssetFilter::set_name_starts_with(std::string prefix) {
    name_starts_with_opt = std::move(prefix);
    return *this;
}

AssetFilter& AssetFilter::set_name_ends_with(std::string suffix) {
    name_ends_with_opt = std::move(suffix);
    return *this;
}

AssetFilter& AssetFilter::set_wallet(std::string wallet) {
    wallet_opt = std::move(wallet);
    return *this;
}

AssetFilter& AssetFilter::set_wallet_in(std::vector<std::string> wallets) {
    wallet_in_opt = std::move(wallets);
    return *this;
}

JsonValue AssetFilter::to_json() const {
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

bool AssetFilter::operator==(const AssetFilter& rhs) const {
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

bool AssetFilter::operator!=(const AssetFilter& rhs) const {
    return !(*this == rhs);
}
