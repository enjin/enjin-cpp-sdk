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

#include "enjinsdk/internal/WalletFragmentArgumentsImpl.hpp"

#include "RapidJsonUtils.hpp"
#include <utility>

using namespace enjin::sdk::models;
using namespace enjin::sdk::shared;
using namespace enjin::sdk::utils;

std::string WalletFragmentArgumentsImpl::serialize() const {
    rapidjson::Document document(rapidjson::kObjectType);
    join_serialized_objects_to_document(document, {
            AssetFragmentArgumentsImpl::serialize(),
            BalanceFragmentArgumentsImpl::serialize(),
            TransactionFragmentArgumentsImpl::serialize(),
    });

    if (wallet_balance_filter.has_value()) {
        set_object_member_from_type<BalanceFilter>(document, "walletBalanceFilter", wallet_balance_filter.value());
    }

    if (with_assets_created.has_value()) {
        set_boolean_member(document, "withAssetsCreated", with_assets_created.value());
    }

    if (with_assets_created.has_value()) {
        set_boolean_member(document, "withWalletBalances", with_assets_created.value());
    }

    if (with_assets_created.has_value()) {
        set_boolean_member(document, "withWalletTransactions", with_assets_created.value());
    }

    return document_to_string(document);
}

void WalletFragmentArgumentsImpl::set_wallet_balance_filter(BalanceFilter filter) {
    wallet_balance_filter.emplace(std::move(filter));
}

void WalletFragmentArgumentsImpl::set_with_assets_created() {
    with_assets_created = true;
}

void WalletFragmentArgumentsImpl::set_with_wallet_balances() {
    with_wallet_balances = true;
}

void WalletFragmentArgumentsImpl::set_with_wallet_transactions() {
    with_wallet_transactions = true;
}

bool WalletFragmentArgumentsImpl::operator==(const WalletFragmentArgumentsImpl& rhs) const {
    return static_cast<const AssetFragmentArgumentsImpl&>(*this) == rhs
           && static_cast<const BalanceFragmentArgumentsImpl&>(*this) == rhs
           && static_cast<const TransactionFragmentArgumentsImpl&>(*this) == rhs
           && wallet_balance_filter == rhs.wallet_balance_filter
           && with_assets_created == rhs.with_assets_created
           && with_wallet_balances == rhs.with_wallet_balances
           && with_wallet_transactions == rhs.with_wallet_transactions;
}

bool WalletFragmentArgumentsImpl::operator!=(const WalletFragmentArgumentsImpl& rhs) const {
    return !(rhs == *this);
}
