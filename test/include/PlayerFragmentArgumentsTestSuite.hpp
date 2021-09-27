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

#ifndef ENJINSDK_PLAYERFRAGMENTARGUMENTSTESTSUITE_HPP
#define ENJINSDK_PLAYERFRAGMENTARGUMENTSTESTSUITE_HPP

#include "WalletFragmentArgumentsTestSuite.hpp"
#include "enjinsdk/shared/PlayerFragmentArguments.hpp"
#include <type_traits>

namespace enjin::test::suites {

template<class T>
class PlayerFragmentArgumentsTestSuite : public WalletFragmentArgumentsTestSuite<T> {
    static_assert(std::is_base_of<sdk::shared::PlayerFragmentArguments<T>, T>::value,
                  "Type T does not inherit from PlayerFragmentArguments.");

public:
    static void set_player_fragment_arguments(sdk::shared::PlayerFragmentArguments<T>& o) {
        WalletFragmentArgumentsTestSuite<T>::set_wallet_fragment_arguments(o);
        o.set_with_linking_info()
         .set_qr_size(0)
         .set_with_wallet();
    }
};

}

#endif //ENJINSDK_PLAYERFRAGMENTARGUMENTSTESTSUITE_HPP
