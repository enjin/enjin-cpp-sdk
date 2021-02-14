#include "enjinsdk/models/BlockchainData.hpp"
#include "../../suites/JsonTestSuite.hpp"

using namespace enjin::sdk::models;

class BlockchainDataTest : public JsonTestSuite {
public:
    BlockchainData class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"encodedData":"1","signedTransaction":"1","signedBackupTransaction":"1","signedCancelTransaction":"1","receipt":{},"error":"1","nonce":"1"})";
};

TEST_F(BlockchainDataTest, DeserializeEmptyStringFieldsDoNotHaveValues) {
    // Arrange
    const std::string json;

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_FALSE(class_under_test.get_encoded_data().has_value());
    EXPECT_FALSE(class_under_test.get_signed_transaction().has_value());
    EXPECT_FALSE(class_under_test.get_signed_backup_transaction().has_value());
    EXPECT_FALSE(class_under_test.get_signed_cancel_transaction().has_value());
    EXPECT_FALSE(class_under_test.get_receipt().has_value());
    EXPECT_FALSE(class_under_test.get_error().has_value());
    EXPECT_FALSE(class_under_test.get_nonce().has_value());
}

TEST_F(BlockchainDataTest, DeserializeEmptyJsonObjectFieldsDoNotHaveValues) {
    // Arrange
    const std::string json(EMPTY_JSON_OBJECT);

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_FALSE(class_under_test.get_encoded_data().has_value());
    EXPECT_FALSE(class_under_test.get_signed_transaction().has_value());
    EXPECT_FALSE(class_under_test.get_signed_backup_transaction().has_value());
    EXPECT_FALSE(class_under_test.get_signed_cancel_transaction().has_value());
    EXPECT_FALSE(class_under_test.get_receipt().has_value());
    EXPECT_FALSE(class_under_test.get_error().has_value());
    EXPECT_FALSE(class_under_test.get_nonce().has_value());
}

TEST_F(BlockchainDataTest, DeserializePopulatedJsonObjectFieldsHaveExpectedValues) {
    // Arrange
    const std::string expected_string("1");
    const TransactionReceipt expected_receipt;
    const std::string json(POPULATED_JSON_OBJECT);

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_EQ(expected_string, class_under_test.get_encoded_data().value());
    EXPECT_EQ(expected_string, class_under_test.get_signed_transaction().value());
    EXPECT_EQ(expected_string, class_under_test.get_signed_backup_transaction().value());
    EXPECT_EQ(expected_string, class_under_test.get_signed_cancel_transaction().value());
    EXPECT_EQ(expected_receipt, class_under_test.get_receipt().value());
    EXPECT_EQ(expected_string, class_under_test.get_error().value());
    EXPECT_EQ(expected_string, class_under_test.get_nonce().value());
}

TEST_F(BlockchainDataTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    BlockchainData lhs;
    BlockchainData rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(BlockchainDataTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    BlockchainData lhs;
    BlockchainData rhs;
    lhs.deserialize(POPULATED_JSON_OBJECT);
    rhs.deserialize(POPULATED_JSON_OBJECT);

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(BlockchainDataTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    BlockchainData lhs;
    BlockchainData rhs;
    lhs.deserialize(POPULATED_JSON_OBJECT);

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(BlockchainDataTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    BlockchainData lhs;
    BlockchainData rhs;
    rhs.deserialize(POPULATED_JSON_OBJECT);

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
