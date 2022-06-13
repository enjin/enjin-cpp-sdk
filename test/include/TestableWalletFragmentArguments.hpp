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

#ifndef ENJINSDK_TESTABLEWALLETFRAGMENTARGUMENTS_HPP
#define ENJINSDK_TESTABLEWALLETFRAGMENTARGUMENTS_HPP

#if(ENJINSDK_BUILD_SHARED == 0)

#include "enjinsdk/shared/WalletFragmentArguments.hpp"

namespace enjin::test::utils {

class TestableWalletFragmentArguments : public sdk::shared::WalletFragmentArguments<TestableWalletFragmentArguments> {
public:
    TestableWalletFragmentArguments() = default;

    ~TestableWalletFragmentArguments() override = default;

    bool operator==(const TestableWalletFragmentArguments& rhs) const;

    bool operator!=(const TestableWalletFragmentArguments& rhs) const;
};

}

namespace enjin::sdk::shared {

// region AssetFragmentArguments

template test::utils::TestableWalletFragmentArguments&
AssetFragmentArguments<test::utils::TestableWalletFragmentArguments>::set_asset_id_format(
        models::AssetIdFormat asset_id_format);

template test::utils::TestableWalletFragmentArguments&
AssetFragmentArguments<test::utils::TestableWalletFragmentArguments>::set_with_state_data();

template test::utils::TestableWalletFragmentArguments&
AssetFragmentArguments<test::utils::TestableWalletFragmentArguments>::set_with_config_data();

template test::utils::TestableWalletFragmentArguments&
AssetFragmentArguments<test::utils::TestableWalletFragmentArguments>::set_with_asset_blocks();

template test::utils::TestableWalletFragmentArguments&
AssetFragmentArguments<test::utils::TestableWalletFragmentArguments>::set_with_creator();

template test::utils::TestableWalletFragmentArguments&
AssetFragmentArguments<test::utils::TestableWalletFragmentArguments>::set_with_melt_details();

template test::utils::TestableWalletFragmentArguments&
AssetFragmentArguments<test::utils::TestableWalletFragmentArguments>::set_with_metadata_uri();

template test::utils::TestableWalletFragmentArguments&
AssetFragmentArguments<test::utils::TestableWalletFragmentArguments>::set_with_supply_details();

template test::utils::TestableWalletFragmentArguments&
AssetFragmentArguments<test::utils::TestableWalletFragmentArguments>::set_with_transfer_settings();

template test::utils::TestableWalletFragmentArguments&
AssetFragmentArguments<test::utils::TestableWalletFragmentArguments>::set_with_asset_variant_mode();

template test::utils::TestableWalletFragmentArguments&
AssetFragmentArguments<test::utils::TestableWalletFragmentArguments>::set_with_asset_variants();

template test::utils::TestableWalletFragmentArguments&
AssetFragmentArguments<test::utils::TestableWalletFragmentArguments>::set_with_variant_metadata();

// endregion AssetFragmentArguments

// region BalanceFragmentArguments

template test::utils::TestableWalletFragmentArguments&
BalanceFragmentArguments<test::utils::TestableWalletFragmentArguments>::set_bal_id_format(
        models::AssetIdFormat bal_id_format);

template test::utils::TestableWalletFragmentArguments&
BalanceFragmentArguments<test::utils::TestableWalletFragmentArguments>::set_bal_index_format(
        models::AssetIndexFormat bal_index_format);

template test::utils::TestableWalletFragmentArguments&
BalanceFragmentArguments<test::utils::TestableWalletFragmentArguments>::set_with_bal_project_uuid();

template test::utils::TestableWalletFragmentArguments&
BalanceFragmentArguments<test::utils::TestableWalletFragmentArguments>::set_with_bal_wallet_address();

// endregion BalanceFragmentArguments

// region WalletFragmentArguments

template test::utils::TestableWalletFragmentArguments&
WalletFragmentArguments<test::utils::TestableWalletFragmentArguments>::set_wallet_balance_filter(
        models::BalanceFilter filter);

template test::utils::TestableWalletFragmentArguments&
WalletFragmentArguments<test::utils::TestableWalletFragmentArguments>::set_with_assets_created();

template test::utils::TestableWalletFragmentArguments&
WalletFragmentArguments<test::utils::TestableWalletFragmentArguments>::set_with_wallet_balances();

template test::utils::TestableWalletFragmentArguments&
WalletFragmentArguments<test::utils::TestableWalletFragmentArguments>::set_with_wallet_transactions();

// endregion WalletFragmentArguments

}

#endif

#endif //ENJINSDK_TESTABLEWALLETFRAGMENTARGUMENTS_HPP
