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

#ifndef ENJINSDK_WALLETFRAGMENTARGUMENTSTESTSUITE_HPP
#define ENJINSDK_WALLETFRAGMENTARGUMENTSTESTSUITE_HPP

#include "AssetFragmentArgumentsTestSuite.hpp"
#include "BalanceFragmentArgumentsTestSuite.hpp"
#include "TransactionFragmentArgumentsTestSuite.hpp"
#include "enjinsdk/JsonValue.hpp"
#include "enjinsdk/shared/WalletFragmentArguments.hpp"
#include <type_traits>

namespace enjin::test::suites {

template<class T>
class WalletFragmentArgumentsTestSuite : public AssetFragmentArgumentsTestSuite<T>,
                                         public BalanceFragmentArgumentsTestSuite<T>,
                                         public TransactionFragmentArgumentsTestSuite<T> {
    static_assert(std::is_base_of<sdk::shared::WalletFragmentArguments<T>, T>::value,
                  "Type T does not inherit from WalletFragmentArguments.");

public:
    static constexpr char WalletFragmentJson[] =
            R"({"walletBalanceFilter":{},"withAssetsCreated":true,"withWalletBalances":true,"withWalletTransactions":true})";

    static sdk::json::JsonValue create_json_object() {
        sdk::json::JsonValue json;

        json.try_parse_as_object(WalletFragmentJson);
        return json;
    }

    static void set_wallet_fragment_arguments(sdk::shared::WalletFragmentArguments<T>& o) {
        o.set_wallet_balance_filter({})
         .set_with_assets_created()
         .set_with_wallet_balances()
         .set_with_wallet_transactions();
    }
};

}

#endif //ENJINSDK_WALLETFRAGMENTARGUMENTSTESTSUITE_HPP
