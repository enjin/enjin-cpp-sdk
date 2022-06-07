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

#ifndef ENJINSDK_PROJECTTRANSACTIONREQUESTARGUMENTSTESTSUITE_HPP
#define ENJINSDK_PROJECTTRANSACTIONREQUESTARGUMENTSTESTSUITE_HPP

#include "enjinsdk/JsonValue.hpp"
#include "TransactionFragmentArgumentsTestSuite.hpp"
#include "enjinsdk/project/ProjectTransactionRequestArguments.hpp"
#include <type_traits>

namespace enjin::test::suites {

template<class T>
class ProjectTransactionRequestArgumentsTestSuite : public TransactionFragmentArgumentsTestSuite<T> {
    static_assert(std::is_base_of<sdk::project::ProjectTransactionRequestArguments<T>, T>::value,
                  "Type T does not inherit from ProjectTransactionRequestArguments.");

public:
    static constexpr char ProjectTransactionRequestJson[] =
            R"({"ethAddress":"1"})";

    static sdk::json::JsonValue create_json_object() {
        sdk::json::JsonValue json;

        json.try_parse_as_object(ProjectTransactionRequestJson);
        return json;
    }

    static void set_project_transaction_request_arguments(sdk::project::ProjectTransactionRequestArguments<T>& o) {
        o.set_eth_address("1");
    }
};

}

#endif //ENJINSDK_PROJECTTRANSACTIONREQUESTARGUMENTSTESTSUITE_HPP
