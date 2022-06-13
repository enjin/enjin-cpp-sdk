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

#ifndef ENJINCPPSDK_SHAREDWALLETFRAGMENTARGUMENTS_HPP
#define ENJINCPPSDK_SHAREDWALLETFRAGMENTARGUMENTS_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/JsonUtils.hpp"
#include "enjinsdk/JsonValue.hpp"
#include "enjinsdk/models/BalanceFilter.hpp"
#include "enjinsdk/shared/AssetFragmentArguments.hpp"
#include "enjinsdk/shared/BalanceFragmentArguments.hpp"
#include "enjinsdk/shared/TransactionFragmentArguments.hpp"
#include <optional>
#include <string>
#include <type_traits>
#include <utility>

namespace enjin::sdk::shared {

/// \brief Fragment interface used to request certain information from wallets returned by the platform.
/// \tparam T The type of the implementing class.
template<class T>
class ENJINSDK_EXPORT WalletFragmentArguments : public AssetFragmentArguments<T>,
                                                public BalanceFragmentArguments<T>,
                                                public TransactionFragmentArguments<T> {
public:
    ~WalletFragmentArguments() override = default;

    [[nodiscard]] std::string serialize() const override {
        return to_json().to_string();
    }

    /// \brief Sets the balance filter when used with with_wallet_balances().
    /// \param filter The filter.
    /// \return This request for chaining.
    T& set_wallet_balance_filter(models::BalanceFilter filter) {
        wallet_balance_filter_opt.emplace(std::move(filter));
        return static_cast<T&>(*this);
    }

    /// Sets the request to include the assets created by the wallet.
    /// \return This request for chaining.
    T& set_with_assets_created() {
        with_assets_created_opt = true;
        return static_cast<T&>(*this);
    }

    /// \brief Sets the request to include the asset balances of the wallet.
    /// \return This request for chaining.
    T& set_with_wallet_balances() {
        with_wallet_balances_opt = true;
        return static_cast<T&>(*this);
    }

    /// \brief Sets the request to include the transactions the wallet has signed.
    /// \return This request for chaining.
    T& set_with_wallet_transactions() {
        with_wallet_transactions_opt = true;
        return static_cast<T&>(*this);
    }

    [[nodiscard]] json::JsonValue to_json() const override {
        json::JsonValue json = json::JsonValue::create_object();

        utils::JsonUtils::join_object(json, AssetFragmentArguments<T>::to_json());
        utils::JsonUtils::join_object(json, BalanceFragmentArguments<T>::to_json());
        utils::JsonUtils::join_object(json, TransactionFragmentArguments<T>::to_json());
        utils::JsonUtils::try_set_field(json, "walletBalanceFilter", wallet_balance_filter_opt);
        utils::JsonUtils::try_set_field(json, "withAssetsCreated", with_assets_created_opt);
        utils::JsonUtils::try_set_field(json, "withWalletBalances", with_wallet_balances_opt);
        utils::JsonUtils::try_set_field(json, "withWalletTransactions", with_wallet_transactions_opt);

        return json;
    }

    bool operator==(const WalletFragmentArguments& rhs) const {
        return static_cast<const AssetFragmentArguments<T>&>(*this) == rhs
               && static_cast<const BalanceFragmentArguments<T>&>(*this) == rhs
               && static_cast<const TransactionFragmentArguments<T>&>(*this) == rhs
               && wallet_balance_filter_opt == rhs.wallet_balance_filter_opt
               && with_assets_created_opt == rhs.with_assets_created_opt
               && with_wallet_balances_opt == rhs.with_wallet_balances_opt
               && with_wallet_transactions_opt == rhs.with_wallet_transactions_opt;
    }

    bool operator!=(const WalletFragmentArguments& rhs) const {
        return !(*this == rhs);
    }

protected:
    /// \brief Sole constructor.
    WalletFragmentArguments() : AssetFragmentArguments<T>(),
                                BalanceFragmentArguments<T>(),
                                TransactionFragmentArguments<T>() {
        static_assert(std::is_base_of<WalletFragmentArguments, T>::value,
                      "Class T does not inherit from WalletFragmentArguments.");
    }

private:
    std::optional<models::BalanceFilter> wallet_balance_filter_opt;
    std::optional<bool> with_assets_created_opt;
    std::optional<bool> with_wallet_balances_opt;
    std::optional<bool> with_wallet_transactions_opt;
};

}

#endif //ENJINCPPSDK_SHAREDWALLETFRAGMENTARGUMENTS_HPP
