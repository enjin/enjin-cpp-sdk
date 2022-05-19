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

#ifndef ENJINSDK_TESTABLESHAREDTRANSACTIONFRAGMENTARGUMENTS_HPP
#define ENJINSDK_TESTABLESHAREDTRANSACTIONFRAGMENTARGUMENTS_HPP

#if(ENJINSDK_BUILD_SHARED == 0)

#include "enjinsdk/shared/TransactionFragmentArguments.hpp"

namespace enjin::test::utils {

class TestableSharedTransactionFragmentArguments
        : public sdk::shared::TransactionFragmentArguments<TestableSharedTransactionFragmentArguments> {
public:
    TestableSharedTransactionFragmentArguments() = default;

    ~TestableSharedTransactionFragmentArguments() override = default;

    bool operator==(const TestableSharedTransactionFragmentArguments& rhs) const;

    bool operator!=(const TestableSharedTransactionFragmentArguments& rhs) const;
};

}

namespace enjin::sdk::shared {

template test::utils::TestableSharedTransactionFragmentArguments&
TransactionFragmentArguments<test::utils::TestableSharedTransactionFragmentArguments>::set_asset_id_format(
        models::AssetIdFormat asset_id_format);

template test::utils::TestableSharedTransactionFragmentArguments&
TransactionFragmentArguments<test::utils::TestableSharedTransactionFragmentArguments>::set_with_blockchain_data();

template test::utils::TestableSharedTransactionFragmentArguments&
TransactionFragmentArguments<test::utils::TestableSharedTransactionFragmentArguments>::set_with_meta();

template test::utils::TestableSharedTransactionFragmentArguments&
TransactionFragmentArguments<test::utils::TestableSharedTransactionFragmentArguments>::set_with_encoded_data();

template test::utils::TestableSharedTransactionFragmentArguments&
TransactionFragmentArguments<test::utils::TestableSharedTransactionFragmentArguments>::set_with_asset_data();

template test::utils::TestableSharedTransactionFragmentArguments&
TransactionFragmentArguments<test::utils::TestableSharedTransactionFragmentArguments>::set_with_signed_txs();

template test::utils::TestableSharedTransactionFragmentArguments&
TransactionFragmentArguments<test::utils::TestableSharedTransactionFragmentArguments>::set_with_error();

template test::utils::TestableSharedTransactionFragmentArguments&
TransactionFragmentArguments<test::utils::TestableSharedTransactionFragmentArguments>::set_with_nonce();

template test::utils::TestableSharedTransactionFragmentArguments&
TransactionFragmentArguments<test::utils::TestableSharedTransactionFragmentArguments>::set_with_state();

template test::utils::TestableSharedTransactionFragmentArguments&
TransactionFragmentArguments<test::utils::TestableSharedTransactionFragmentArguments>::set_with_receipt();

template test::utils::TestableSharedTransactionFragmentArguments&
TransactionFragmentArguments<test::utils::TestableSharedTransactionFragmentArguments>::set_with_receipt_logs();

template test::utils::TestableSharedTransactionFragmentArguments&
TransactionFragmentArguments<test::utils::TestableSharedTransactionFragmentArguments>::set_with_log_event();

template test::utils::TestableSharedTransactionFragmentArguments&
TransactionFragmentArguments<test::utils::TestableSharedTransactionFragmentArguments>::set_with_transaction_project_uuid();

}

#endif

#endif //ENJINSDK_TESTABLESHAREDTRANSACTIONFRAGMENTARGUMENTS_HPP
