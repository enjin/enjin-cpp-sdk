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

#include "gtest/gtest.h"
#include "JsonTestSuite.hpp"
#include "enjinsdk/internal/TransactionFragmentArgumentsImpl.hpp"
#include <string>

using namespace enjin::sdk::shared;
using namespace enjin::test::suites;

class TransactionFragmentArgumentsImplTest : public JsonTestSuite,
                                             public testing::Test {
public:
    TransactionFragmentArgumentsImpl class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"withBlockchainData":true,"withMeta":true,"withEncodedData":true,"withAssetData":true,"withSignedTxs":true,"withError":true,"withNonce":true,"withState":true,"withReceipt":true,"withReceiptLogs":true,"withLogEvent":true})";

    static TransactionFragmentArgumentsImpl create_default_arguments() {
        TransactionFragmentArgumentsImpl arguments;
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
        return arguments;
    }
};

TEST_F(TransactionFragmentArgumentsImplTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EMPTY_JSON_OBJECT);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(TransactionFragmentArgumentsImplTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
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

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(TransactionFragmentArgumentsImplTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    TransactionFragmentArgumentsImpl lhs;
    TransactionFragmentArgumentsImpl rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(TransactionFragmentArgumentsImplTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    TransactionFragmentArgumentsImpl lhs = create_default_arguments();
    TransactionFragmentArgumentsImpl rhs = create_default_arguments();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(TransactionFragmentArgumentsImplTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    TransactionFragmentArgumentsImpl lhs = create_default_arguments();
    TransactionFragmentArgumentsImpl rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(TransactionFragmentArgumentsImplTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    TransactionFragmentArgumentsImpl lhs;
    TransactionFragmentArgumentsImpl rhs = create_default_arguments();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
