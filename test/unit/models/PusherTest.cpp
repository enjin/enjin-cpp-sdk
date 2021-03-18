#include "gtest/gtest.h"
#include "JsonTestSuite.hpp"
#include "enjinsdk/models/Pusher.hpp"
#include <string>

using namespace enjin::sdk::models;
using namespace enjin::test::suites;

class PusherTest : public JsonTestSuite,
                   public testing::Test {
public:
    Pusher class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"key":"1","namespace":"1","channels":{},"options":{}})";
};

TEST_F(PusherTest, DeserializeEmptyStringFieldsDoNotHaveValues) {
    // Arrange
    const std::string json;

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_FALSE(class_under_test.get_key().has_value());
    EXPECT_FALSE(class_under_test.get_pusher_namespace().has_value());
    EXPECT_FALSE(class_under_test.get_channels().has_value());
    EXPECT_FALSE(class_under_test.get_options().has_value());
}

TEST_F(PusherTest, DeserializeEmptyJsonObjectFieldsDoNotHaveValues) {
    // Arrange
    const std::string json(EMPTY_JSON_OBJECT);

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_FALSE(class_under_test.get_key().has_value());
    EXPECT_FALSE(class_under_test.get_pusher_namespace().has_value());
    EXPECT_FALSE(class_under_test.get_channels().has_value());
    EXPECT_FALSE(class_under_test.get_options().has_value());
}

TEST_F(PusherTest, DeserializePopulatedJsonObjectFieldsHaveExpectedValues) {
    // Arrange
    const std::string expected_string("1");
    const PusherChannels expected_channels;
    const PusherOptions expected_options;
    const std::string json(POPULATED_JSON_OBJECT);

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_EQ(expected_string, class_under_test.get_key().value());
    EXPECT_EQ(expected_string, class_under_test.get_pusher_namespace().value());
    EXPECT_EQ(expected_channels, class_under_test.get_channels().value());
    EXPECT_EQ(expected_options, class_under_test.get_options().value());
}

TEST_F(PusherTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    Pusher lhs;
    Pusher rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(PusherTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    Pusher lhs;
    Pusher rhs;
    lhs.deserialize(POPULATED_JSON_OBJECT);
    rhs.deserialize(POPULATED_JSON_OBJECT);

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(PusherTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    Pusher lhs;
    Pusher rhs;
    lhs.deserialize(POPULATED_JSON_OBJECT);

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(PusherTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    Pusher lhs;
    Pusher rhs;
    rhs.deserialize(POPULATED_JSON_OBJECT);

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
