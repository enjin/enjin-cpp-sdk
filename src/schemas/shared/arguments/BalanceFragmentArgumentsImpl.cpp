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

#include "enjinsdk/internal/BalanceFragmentArgumentsImpl.hpp"

#include "RapidJsonUtils.hpp"
#include "enjinsdk/EnumUtils.hpp"

using namespace enjin::sdk::models;
using namespace enjin::sdk::shared;
using namespace enjin::sdk::utils;

std::string BalanceFragmentArgumentsImpl::serialize() const {
    rapidjson::Document document(rapidjson::kObjectType);

    if (bal_id_format.has_value()) {
        set_string_member(document,
                          "balIdFormat",
                          EnumUtils::serialize_asset_id_format(bal_id_format.value()));
    }

    if (bal_index_format.has_value()) {
        set_string_member(document,
                          "balIndexFormat",
                          EnumUtils::serialize_asset_index_format(bal_index_format.value()));
    }

    if (with_bal_project_uuid.has_value()) {
        set_boolean_member(document, "withBalProjectUuid", with_bal_project_uuid.value());
    }

    if (with_bal_wallet_address.has_value()) {
        set_boolean_member(document, "withBalWalletAddress", with_bal_wallet_address.value());
    }

    return document_to_string(document);
}

void BalanceFragmentArgumentsImpl::set_bal_id_format(AssetIdFormat bal_id_format) {
    BalanceFragmentArgumentsImpl::bal_id_format = bal_id_format;
}

void BalanceFragmentArgumentsImpl::set_bal_index_format(AssetIndexFormat bal_index_format) {
    BalanceFragmentArgumentsImpl::bal_index_format = bal_index_format;
}

void BalanceFragmentArgumentsImpl::set_with_bal_project_uuid() {
    with_bal_project_uuid = true;
}

void BalanceFragmentArgumentsImpl::set_with_bal_wallet_address() {
    with_bal_wallet_address = true;
}

bool BalanceFragmentArgumentsImpl::operator==(const BalanceFragmentArgumentsImpl& rhs) const {
    return bal_id_format == rhs.bal_id_format
           && bal_index_format == rhs.bal_index_format
           && with_bal_project_uuid == rhs.with_bal_project_uuid
           && with_bal_wallet_address == rhs.with_bal_wallet_address;
}

bool BalanceFragmentArgumentsImpl::operator!=(const BalanceFragmentArgumentsImpl& rhs) const {
    return !(rhs == *this);
}
