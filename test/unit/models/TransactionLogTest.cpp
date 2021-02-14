#include "enjinsdk/models/TransactionLog.hpp"
#include "../../suites/JsonTestSuite.hpp"
#include <string>

using namespace enjin::sdk::models;

class TransactionLogTest : public JsonTestSuite {
public:
    TransactionLog class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"blockNumber":1,"address":"1","transactionHash":"1","data":[],"topics":[],"event":{}})";
};

TEST_F(TransactionLogTest, DeserializeEmptyStringFieldsDoNotHaveValues) {
    // Arrange
    const std::string json;

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_FALSE(class_under_test.get_block_number().has_value());
    EXPECT_FALSE(class_under_test.get_address().has_value());
    EXPECT_FALSE(class_under_test.get_transaction_hash().has_value());
    EXPECT_FALSE(class_under_test.get_data().has_value());
    EXPECT_FALSE(class_under_test.get_topics().has_value());
    EXPECT_FALSE(class_under_test.get_event().has_value());
}

TEST_F(TransactionLogTest, DeserializeEmptyJsonObjectFieldsDoNotHaveValues) {
    // Arrange
    const std::string json(EMPTY_JSON_OBJECT);

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_FALSE(class_under_test.get_block_number().has_value());
    EXPECT_FALSE(class_under_test.get_address().has_value());
    EXPECT_FALSE(class_under_test.get_transaction_hash().has_value());
    EXPECT_FALSE(class_under_test.get_data().has_value());
    EXPECT_FALSE(class_under_test.get_topics().has_value());
    EXPECT_FALSE(class_under_test.get_event().has_value());
}

TEST_F(TransactionLogTest, DeserializePopulatedJsonObjectFieldsHaveExpectedValues) {
    // Arrange
    const int expected_int = 1;
    const std::string expected_string("1");
    const TransactionEvent expected_event;
    const std::string json(POPULATED_JSON_OBJECT);

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_EQ(expected_int, class_under_test.get_block_number().value());
    EXPECT_EQ(expected_string, class_under_test.get_address().value());
    EXPECT_EQ(expected_string, class_under_test.get_transaction_hash().value());
    EXPECT_TRUE(class_under_test.get_data().has_value());
    EXPECT_TRUE(class_under_test.get_topics().has_value());
    EXPECT_EQ(expected_event, class_under_test.get_event().value());
}

TEST_F(TransactionLogTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    TransactionLog lhs;
    TransactionLog rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(TransactionLogTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    TransactionLog lhs;
    TransactionLog rhs;
    lhs.deserialize(POPULATED_JSON_OBJECT);
    rhs.deserialize(POPULATED_JSON_OBJECT);

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(TransactionLogTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    TransactionLog lhs;
    TransactionLog rhs;
    lhs.deserialize(POPULATED_JSON_OBJECT);

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(TransactionLogTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    TransactionLog lhs;
    TransactionLog rhs;
    rhs.deserialize(POPULATED_JSON_OBJECT);

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
