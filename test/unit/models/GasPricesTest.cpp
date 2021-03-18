#include "gtest/gtest.h"
#include "JsonTestSuite.hpp"
#include "enjinsdk/models/GasPrices.hpp"

using namespace enjin::sdk::models;
using namespace enjin::test::suites;

class GasPricesTest : public JsonTestSuite,
                      public testing::Test {
public:
    GasPrices class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"safeLow":1.0,"average":1.0,"fast":1.0,"fastest":1.0})";
};

TEST_F(GasPricesTest, DeserializeEmptyStringFieldsDoNotHaveValues) {
    // Arrange
    const std::string json;

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_FALSE(class_under_test.get_safe_low().has_value());
    EXPECT_FALSE(class_under_test.get_average().has_value());
    EXPECT_FALSE(class_under_test.get_fast().has_value());
    EXPECT_FALSE(class_under_test.get_fastest().has_value());
}

TEST_F(GasPricesTest, DeserializeEmptyJsonObjectFieldsDoNotHaveValues) {
    // Arrange
    const std::string json(EMPTY_JSON_OBJECT);

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_FALSE(class_under_test.get_safe_low().has_value());
    EXPECT_FALSE(class_under_test.get_average().has_value());
    EXPECT_FALSE(class_under_test.get_fast().has_value());
    EXPECT_FALSE(class_under_test.get_fastest().has_value());
}

TEST_F(GasPricesTest, DeserializePopulatedJsonObjectFieldsHaveExpectedValues) {
    // Arrange
    const float expected_float = 1.0;
    const std::string json(POPULATED_JSON_OBJECT);

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_EQ(expected_float, class_under_test.get_safe_low().value());
    EXPECT_EQ(expected_float, class_under_test.get_average().value());
    EXPECT_EQ(expected_float, class_under_test.get_fast().value());
    EXPECT_EQ(expected_float, class_under_test.get_fastest().value());
}

TEST_F(GasPricesTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    GasPrices lhs;
    GasPrices rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(GasPricesTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    GasPrices lhs;
    GasPrices rhs;
    lhs.deserialize(POPULATED_JSON_OBJECT);
    rhs.deserialize(POPULATED_JSON_OBJECT);

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(GasPricesTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    GasPrices lhs;
    GasPrices rhs;
    lhs.deserialize(POPULATED_JSON_OBJECT);

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(GasPricesTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    GasPrices lhs;
    GasPrices rhs;
    rhs.deserialize(POPULATED_JSON_OBJECT);

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
