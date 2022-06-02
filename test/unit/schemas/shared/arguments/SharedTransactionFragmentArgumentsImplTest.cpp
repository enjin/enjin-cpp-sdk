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

#include "gtest/gtest.h"
#include "JsonTestSuite.hpp"
#include "enjinsdk/internal/TransactionFragmentArgumentsImpl.hpp"
#include <string>

using namespace enjin::sdk::models;
using namespace enjin::sdk::shared;
using namespace enjin::test::suites;

class SharedTransactionFragmentArgumentsImplTest : public JsonTestSuite,
                                                   public testing::Test {
public:
    TransactionFragmentArgumentsImpl class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"transactionAssetIdFormat":"hex64","withBlockchainData":true,"withMeta":true,"withEncodedData":true,"withAssetData":true,"withSignedTxs":true,"withError":true,"withNonce":true,"withState":true,"withReceipt":true,"withReceiptLogs":true,"withLogEvent":true,"withTransactionProjectUuid":true,"withTransactionWalletAddress":true})";

    static TransactionFragmentArgumentsImpl create_default_arguments() {
        TransactionFragmentArgumentsImpl arguments;
        arguments.set_transaction_asset_id_format(AssetIdFormat::Hex64);
        arguments.set_with_blockchain_data();
        arguments.set_with_meta();
        arguments.set_with_encoded_data();
        arguments.set_with_asset_data();
        arguments.set_with_signed_txs();
        arguments.set_with_error();
        arguments.set_with_nonce();
        arguments.set_with_state();
        arguments.set_with_receipt();
        arguments.set_with_receipt_logs();
        arguments.set_with_log_event();
        arguments.set_with_transaction_project_uuid();
        arguments.set_with_transaction_wallet_address();
        return arguments;
    }
};

TEST_F(SharedTransactionFragmentArgumentsImplTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EMPTY_JSON_OBJECT);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(SharedTransactionFragmentArgumentsImplTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_transaction_asset_id_format(AssetIdFormat::Hex64);
    class_under_test.set_with_blockchain_data();
    class_under_test.set_with_meta();
    class_under_test.set_with_encoded_data();
    class_under_test.set_with_asset_data();
    class_under_test.set_with_signed_txs();
    class_under_test.set_with_error();
    class_under_test.set_with_nonce();
    class_under_test.set_with_state();
    class_under_test.set_with_receipt();
    class_under_test.set_with_receipt_logs();
    class_under_test.set_with_log_event();
    class_under_test.set_with_transaction_project_uuid();
    class_under_test.set_with_transaction_wallet_address();

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(SharedTransactionFragmentArgumentsImplTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    TransactionFragmentArgumentsImpl lhs;
    TransactionFragmentArgumentsImpl rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(SharedTransactionFragmentArgumentsImplTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    TransactionFragmentArgumentsImpl lhs = create_default_arguments();
    TransactionFragmentArgumentsImpl rhs = create_default_arguments();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(SharedTransactionFragmentArgumentsImplTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    TransactionFragmentArgumentsImpl lhs = create_default_arguments();
    TransactionFragmentArgumentsImpl rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(SharedTransactionFragmentArgumentsImplTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    TransactionFragmentArgumentsImpl lhs;
    TransactionFragmentArgumentsImpl rhs = create_default_arguments();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
