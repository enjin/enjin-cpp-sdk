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

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::models {

std::string AssetFilter::serialize() const {
    rapidjson::Document document(rapidjson::kObjectType);

    if (and_filters.has_value()) {
        utils::set_array_member_from_type_vector<AssetFilter>(document, AND_KEY, and_filters.value());
    }
    if (or_filters.has_value()) {
        utils::set_array_member_from_type_vector<AssetFilter>(document, OR_KEY, or_filters.value());
    }
    if (id.has_value()) {
        utils::set_string_member(document, ID_KEY, id.value());
    }
    if (id_in.has_value()) {
        utils::set_array_member_from_string_vector(document, ID_IN_KEY, id_in.value());
    }
    if (name.has_value()) {
        utils::set_string_member(document, NAME_KEY, name.value());
    }
    if (name_contains.has_value()) {
        utils::set_string_member(document, NAME_CONTAINS_KEY, name_contains.value());
    }
    if (name_in.has_value()) {
        utils::set_array_member_from_string_vector(document, NAME_IN_KEY, name_in.value());
    }
    if (name_starts_with.has_value()) {
        utils::set_string_member(document, NAME_STARTS_WITH_KEY, name_starts_with.value());
    }
    if (name_ends_with.has_value()) {
        utils::set_string_member(document, NAME_ENDS_WITH_KEY, name_ends_with.value());
    }
    if (wallet.has_value()) {
        utils::set_string_member(document, WALLET_KEY, wallet.value());
    }
    if (wallet_in.has_value()) {
        utils::set_array_member_from_string_vector(document, WALLET_IN_KEY, wallet_in.value());
    }

    return utils::document_to_string(document);
}

AssetFilter& AssetFilter::set_and(std::vector<AssetFilter> others) {
    and_filters = std::move(others);
    return *this;
}

AssetFilter& AssetFilter::set_or(std::vector<AssetFilter> others) {
    or_filters = std::move(others);
    return *this;
}

AssetFilter& AssetFilter::set_id(std::string id) {
    AssetFilter::id = std::move(id);
    return *this;
}

AssetFilter& AssetFilter::set_id_in(std::vector<std::string> ids) {
    id_in = std::move(ids);
    return *this;
}

AssetFilter& AssetFilter::set_name(std::string name) {
    AssetFilter::name = std::move(name);
    return *this;
}

AssetFilter& AssetFilter::set_name_contains(std::string text) {
    name_contains = std::move(text);
    return *this;
}

AssetFilter& AssetFilter::set_name_in(std::vector<std::string> names) {
    name_in = std::move(names);
    return *this;
}

AssetFilter& AssetFilter::set_name_starts_with(std::string prefix) {
    name_starts_with = std::move(prefix);
    return *this;
}

AssetFilter& AssetFilter::set_name_ends_with(std::string suffix) {
    name_ends_with = std::move(suffix);
    return *this;
}

AssetFilter& AssetFilter::set_wallet(std::string wallet) {
    AssetFilter::wallet = std::move(wallet);
    return *this;
}

AssetFilter& AssetFilter::set_wallet_in(std::vector<std::string> wallets) {
    wallet_in = std::move(wallets);
    return *this;
}

bool AssetFilter::operator==(const AssetFilter& rhs) const {
    return and_filters == rhs.and_filters &&
           or_filters == rhs.or_filters &&
           id == rhs.id &&
           id_in == rhs.id_in &&
           name == rhs.name &&
           name_contains == rhs.name_contains &&
           name_in == rhs.name_in &&
           name_starts_with == rhs.name_starts_with &&
           name_ends_with == rhs.name_ends_with &&
           wallet == rhs.wallet &&
           wallet_in == rhs.wallet_in;
}

bool AssetFilter::operator!=(const AssetFilter& rhs) const {
    return !(rhs == *this);
}

}
