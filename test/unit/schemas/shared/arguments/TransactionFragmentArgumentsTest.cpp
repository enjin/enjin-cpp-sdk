#include "enjinsdk/internal/TransactionFragmentArguments.hpp"
#include "../../../../suites/JsonTestSuite.hpp"

using namespace enjin::sdk::shared;

class TransactionFragmentArgumentsTest : public JsonTestSuite {
public:
    TransactionFragmentArguments class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"withBlockchainData":true,"withMeta":true,"withEncodedData":true,"withTokenData":true,"withSignedTxs":true,"withError":true,"withNonce":true,"withState":true,"withReceipt":true,"withReceiptLogs":true,"withLogEvent":true})";

    static TransactionFragmentArguments create_default_arguments() {
        TransactionFragmentArguments arguments;
        arguments.set_with_blockchain_data();
        arguments.set_with_meta();
        arguments.set_with_encoded_data();
        arguments.set_with_token_data();
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

TEST_F(TransactionFragmentArgumentsTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EMPTY_JSON_OBJECT);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(TransactionFragmentArgumentsTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_with_blockchain_data();
    class_under_test.set_with_meta();
    class_under_test.set_with_encoded_data();
    class_under_test.set_with_token_data();
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

TEST_F(TransactionFragmentArgumentsTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    TransactionFragmentArguments lhs;
    TransactionFragmentArguments rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(TransactionFragmentArgumentsTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    TransactionFragmentArguments lhs = create_default_arguments();
    TransactionFragmentArguments rhs = create_default_arguments();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(TransactionFragmentArgumentsTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    TransactionFragmentArguments lhs = create_default_arguments();
    TransactionFragmentArguments rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(TransactionFragmentArgumentsTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    TransactionFragmentArguments lhs;
    TransactionFragmentArguments rhs = create_default_arguments();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
