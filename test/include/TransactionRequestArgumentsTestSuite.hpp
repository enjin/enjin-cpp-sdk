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

#ifndef ENJINSDK_TRANSACTIONREQUESTARGUMENTSTESTSUITE_HPP
#define ENJINSDK_TRANSACTIONREQUESTARGUMENTSTESTSUITE_HPP

#include "TransactionFragmentArgumentsTestSuite.hpp"
#include "enjinsdk/shared/TransactionRequestArguments.hpp"
#include <type_traits>

namespace enjin::test::suites {

template<class T>
class TransactionRequestArgumentsTestSuite : public TransactionFragmentArgumentsTestSuite<T> {
    static_assert(std::is_base_of<sdk::shared::TransactionRequestArguments<T>, T>::value,
                  "Type T does not inherit from TransactionRequestArguments.");

public:
    static void set_transaction_request_arguments(sdk::shared::TransactionRequestArguments<T>& o) {
        TransactionFragmentArgumentsTestSuite<T>::set_transaction_fragment_arguments(o);
        o.set_send(true);
    }
};

}

#endif //ENJINSDK_TRANSACTIONREQUESTARGUMENTSTESTSUITE_HPP
