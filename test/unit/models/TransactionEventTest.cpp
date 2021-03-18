#include "gtest/gtest.h"
#include "JsonTestSuite.hpp"
#include "enjinsdk/models/TransactionEvent.hpp"

using namespace enjin::sdk::models;
using namespace enjin::test::suites;

class TransactionEventTest : public JsonTestSuite,
                             public testing::Test {
public:
    TransactionEvent class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"name":"1","inputs":[],"nonIndexedInputs":[],"indexedInputs":[],"signature":"1","encodedSignature":"1"})";
};

TEST_F(TransactionEventTest, DeserializeEmptyStringFieldsDoNotHaveValues) {
    // Arrange
    const std::string json;

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_FALSE(class_under_test.get_name().has_value());
    EXPECT_FALSE(class_under_test.get_inputs().has_value());
    EXPECT_FALSE(class_under_test.get_non_indexed_inputs().has_value());
    EXPECT_FALSE(class_under_test.get_indexed_inputs().has_value());
    EXPECT_FALSE(class_under_test.get_signature().has_value());
    EXPECT_FALSE(class_under_test.get_encoded_signature().has_value());
}

TEST_F(TransactionEventTest, DeserializeEmptyJsonObjectFieldsDoNotHaveValues) {
    // Arrange
    const std::string json(EMPTY_JSON_OBJECT);

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_FALSE(class_under_test.get_name().has_value());
    EXPECT_FALSE(class_under_test.get_inputs().has_value());
    EXPECT_FALSE(class_under_test.get_non_indexed_inputs().has_value());
    EXPECT_FALSE(class_under_test.get_indexed_inputs().has_value());
    EXPECT_FALSE(class_under_test.get_signature().has_value());
    EXPECT_FALSE(class_under_test.get_encoded_signature().has_value());
}

TEST_F(TransactionEventTest, DeserializePopulatedJsonObjectFieldsHaveExpectedValues) {
    // Arrange
    const std::string expected_string("1");
    const std::string json(POPULATED_JSON_OBJECT);

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_EQ(expected_string, class_under_test.get_name().value());
    EXPECT_TRUE(class_under_test.get_inputs().has_value());
    EXPECT_TRUE(class_under_test.get_non_indexed_inputs().has_value());
    EXPECT_TRUE(class_under_test.get_indexed_inputs().has_value());
    EXPECT_EQ(expected_string, class_under_test.get_signature().value());
    EXPECT_EQ(expected_string, class_under_test.get_encoded_signature().value());
}

TEST_F(TransactionEventTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    TransactionEvent lhs;
    TransactionEvent rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(TransactionEventTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    TransactionEvent lhs;
    TransactionEvent rhs;
    lhs.deserialize(POPULATED_JSON_OBJECT);
    rhs.deserialize(POPULATED_JSON_OBJECT);

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(TransactionEventTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    TransactionEvent lhs;
    TransactionEvent rhs;
    lhs.deserialize(POPULATED_JSON_OBJECT);

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(TransactionEventTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    TransactionEvent lhs;
    TransactionEvent rhs;
    rhs.deserialize(POPULATED_JSON_OBJECT);

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
