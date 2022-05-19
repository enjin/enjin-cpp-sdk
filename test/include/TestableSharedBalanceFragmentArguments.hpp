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

#ifndef ENJINSDK_TESTABLESHAREDBALANCEFRAGMENTARGUMENTS_HPP
#define ENJINSDK_TESTABLESHAREDBALANCEFRAGMENTARGUMENTS_HPP

#if(ENJINSDK_BUILD_SHARED == 0)

#include "enjinsdk/shared/BalanceFragmentArguments.hpp"

namespace enjin::test::utils {

class TestableSharedBalanceFragmentArguments
        : public sdk::shared::BalanceFragmentArguments<TestableSharedBalanceFragmentArguments> {
public:
    TestableSharedBalanceFragmentArguments() = default;

    ~TestableSharedBalanceFragmentArguments() override = default;

    bool operator==(const TestableSharedBalanceFragmentArguments& rhs) const;

    bool operator!=(const TestableSharedBalanceFragmentArguments& rhs) const;
};

}

namespace enjin::sdk::shared {

template test::utils::TestableSharedBalanceFragmentArguments&
BalanceFragmentArguments<test::utils::TestableSharedBalanceFragmentArguments>::set_bal_id_format(
        models::AssetIdFormat bal_id_format);

template test::utils::TestableSharedBalanceFragmentArguments&
BalanceFragmentArguments<test::utils::TestableSharedBalanceFragmentArguments>::set_bal_index_format(
        models::AssetIndexFormat bal_index_format);

template test::utils::TestableSharedBalanceFragmentArguments&
BalanceFragmentArguments<test::utils::TestableSharedBalanceFragmentArguments>::set_with_bal_project_uuid();

template test::utils::TestableSharedBalanceFragmentArguments&
BalanceFragmentArguments<test::utils::TestableSharedBalanceFragmentArguments>::set_with_bal_wallet_address();

}

#endif

#endif //ENJINSDK_TESTABLESHAREDBALANCEFRAGMENTARGUMENTS_HPP
