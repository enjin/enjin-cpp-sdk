#include "enjinsdk/models/Platform.hpp"
#include "../../suites/JsonTestSuite.hpp"
#include <string>

using namespace enjin::sdk::models;

class PlatformTest : public JsonTestSuite {
public:
    Platform class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"id":1,"name":"1","network":"1","contracts":{},"notifications":{}})";
};

TEST_F(PlatformTest, DeserializeEmptyStringFieldsDoNotHaveValues) {
    // Arrange
    const std::string json;

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_FALSE(class_under_test.get_id().has_value());
    EXPECT_FALSE(class_under_test.get_name().has_value());
    EXPECT_FALSE(class_under_test.get_network().has_value());
    EXPECT_FALSE(class_under_test.get_contracts().has_value());
    EXPECT_FALSE(class_under_test.get_notifications().has_value());
}

TEST_F(PlatformTest, DeserializeEmptyJsonObjectFieldsDoNotHaveValues) {
    // Arrange
    const std::string json(EMPTY_JSON_OBJECT);

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_FALSE(class_under_test.get_id().has_value());
    EXPECT_FALSE(class_under_test.get_name().has_value());
    EXPECT_FALSE(class_under_test.get_network().has_value());
    EXPECT_FALSE(class_under_test.get_contracts().has_value());
    EXPECT_FALSE(class_under_test.get_notifications().has_value());
}

TEST_F(PlatformTest, DeserializePopulatedJsonObjectFieldsHaveExpectedValues) {
    // Arrange
    const int expected_int = 1;
    const std::string expected_string("1");
    const Contracts expected_contracts;
    const Notifications expected_notifications;
    const std::string json(POPULATED_JSON_OBJECT);

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_EQ(expected_int, class_under_test.get_id().value());
    EXPECT_EQ(expected_string, class_under_test.get_name().value());
    EXPECT_EQ(expected_string, class_under_test.get_network().value());
    EXPECT_EQ(expected_contracts, class_under_test.get_contracts().value());
    EXPECT_EQ(expected_notifications, class_under_test.get_notifications().value());
}

TEST_F(PlatformTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    Platform lhs;
    Platform rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(PlatformTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    Platform lhs;
    Platform rhs;
    lhs.deserialize(POPULATED_JSON_OBJECT);
    rhs.deserialize(POPULATED_JSON_OBJECT);

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(PlatformTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    Platform lhs;
    Platform rhs;
    lhs.deserialize(POPULATED_JSON_OBJECT);

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(PlatformTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    Platform lhs;
    Platform rhs;
    rhs.deserialize(POPULATED_JSON_OBJECT);

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
