/* Copyright 2021 Enjin Pte Ltd.
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

#ifndef ENJINSDK_BALANCEFRAGMENTARGUMENTSTESTSUITE_HPP
#define ENJINSDK_BALANCEFRAGMENTARGUMENTSTESTSUITE_HPP

#include "enjinsdk/shared/BalanceFragmentArguments.hpp"
#include <type_traits>

namespace enjin::test::suites {

template<class T>
class BalanceFragmentArgumentsTestSuite {
    static_assert(std::is_base_of<sdk::shared::BalanceFragmentArguments<T>, T>::value,
                  "Type T does not inherit from BalanceFragmentArguments.");

public:
    static void set_balance_fragment_arguments(sdk::shared::BalanceFragmentArguments<T>& o) {
        o.set_bal_id_format(sdk::models::AssetIdFormat::HEX64)
         .set_bal_index_format(sdk::models::AssetIndexFormat::HEX64)
         .set_with_bal_project_id()
         .set_with_bal_wallet_address();
    }
};

}

#endif //ENJINSDK_BALANCEFRAGMENTARGUMENTSTESTSUITE_HPP