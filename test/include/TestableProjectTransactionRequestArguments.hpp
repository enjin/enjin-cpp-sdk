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

#ifndef ENJINSDK_TESTABLEPROJECTTRANSACTIONREQUESTARGUMENTS_HPP
#define ENJINSDK_TESTABLEPROJECTTRANSACTIONREQUESTARGUMENTS_HPP

#if(ENJINSDK_BUILD_SHARED == 0)

#include "enjinsdk/project/ProjectTransactionRequestArguments.hpp"

namespace enjin::test::utils {

class TestableProjectTransactionRequestArguments
        : public sdk::project::ProjectTransactionRequestArguments<TestableProjectTransactionRequestArguments> {
public:
    TestableProjectTransactionRequestArguments() = default;

    ~TestableProjectTransactionRequestArguments() override = default;

    bool operator==(const TestableProjectTransactionRequestArguments& rhs) const;

    bool operator!=(const TestableProjectTransactionRequestArguments& rhs) const;
};

}

namespace enjin::sdk::project {

template test::utils::TestableProjectTransactionRequestArguments&
ProjectTransactionRequestArguments<test::utils::TestableProjectTransactionRequestArguments>::set_eth_address(
        std::string address);

}

namespace enjin::sdk::shared {

template test::utils::TestableProjectTransactionRequestArguments&
TransactionFragmentArguments<test::utils::TestableProjectTransactionRequestArguments>::set_transaction_asset_id_format(
        models::AssetIdFormat asset_id_format);

template test::utils::TestableProjectTransactionRequestArguments&
TransactionFragmentArguments<test::utils::TestableProjectTransactionRequestArguments>::set_with_blockchain_data();

template test::utils::TestableProjectTransactionRequestArguments&
TransactionFragmentArguments<test::utils::TestableProjectTransactionRequestArguments>::set_with_meta();

template test::utils::TestableProjectTransactionRequestArguments&
TransactionFragmentArguments<test::utils::TestableProjectTransactionRequestArguments>::set_with_encoded_data();

template test::utils::TestableProjectTransactionRequestArguments&
TransactionFragmentArguments<test::utils::TestableProjectTransactionRequestArguments>::set_with_asset_data();

template test::utils::TestableProjectTransactionRequestArguments&
TransactionFragmentArguments<test::utils::TestableProjectTransactionRequestArguments>::set_with_signed_txs();

template test::utils::TestableProjectTransactionRequestArguments&
TransactionFragmentArguments<test::utils::TestableProjectTransactionRequestArguments>::set_with_error();

template test::utils::TestableProjectTransactionRequestArguments&
TransactionFragmentArguments<test::utils::TestableProjectTransactionRequestArguments>::set_with_nonce();

template test::utils::TestableProjectTransactionRequestArguments&
TransactionFragmentArguments<test::utils::TestableProjectTransactionRequestArguments>::set_with_state();

template test::utils::TestableProjectTransactionRequestArguments&
TransactionFragmentArguments<test::utils::TestableProjectTransactionRequestArguments>::set_with_receipt();

template test::utils::TestableProjectTransactionRequestArguments&
TransactionFragmentArguments<test::utils::TestableProjectTransactionRequestArguments>::set_with_receipt_logs();

template test::utils::TestableProjectTransactionRequestArguments&
TransactionFragmentArguments<test::utils::TestableProjectTransactionRequestArguments>::set_with_log_event();

template test::utils::TestableProjectTransactionRequestArguments&
TransactionFragmentArguments<test::utils::TestableProjectTransactionRequestArguments>::set_with_transaction_project_uuid();

}

#endif

#endif //ENJINSDK_TESTABLEPROJECTTRANSACTIONREQUESTARGUMENTS_HPP
