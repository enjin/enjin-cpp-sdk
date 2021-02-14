#include "enjinsdk/models/PusherOptions.hpp"
#include "../../suites/JsonTestSuite.hpp"
#include <string>

using namespace enjin::sdk::models;

class PusherOptionsTest : public JsonTestSuite {
public:
    PusherOptions class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"cluster":"1","encrypted":true})";
};

TEST_F(PusherOptionsTest, DeserializeEmptyStringFieldsDoNotHaveValues) {
    // Arrange
    const std::string json;

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_FALSE(class_under_test.get_cluster().has_value());
    EXPECT_FALSE(class_under_test.get_encrypted().has_value());
}

TEST_F(PusherOptionsTest, DeserializeEmptyJsonObjectFieldsDoNotHaveValues) {
    // Arrange
    const std::string json(EMPTY_JSON_OBJECT);

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_FALSE(class_under_test.get_cluster().has_value());
    EXPECT_FALSE(class_under_test.get_encrypted().has_value());
}

TEST_F(PusherOptionsTest, DeserializePopulatedJsonObjectFieldsHaveExpectedValues) {
    // Arrange
    const bool expected_bool = true;
    const std::string expected_string("1");
    const std::string json(POPULATED_JSON_OBJECT);

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_EQ(expected_string, class_under_test.get_cluster().value());
    EXPECT_EQ(expected_bool, class_under_test.get_encrypted().value());
}

TEST_F(PusherOptionsTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    PusherOptions lhs;
    PusherOptions rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(PusherOptionsTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    PusherOptions lhs;
    PusherOptions rhs;
    lhs.deserialize(POPULATED_JSON_OBJECT);
    rhs.deserialize(POPULATED_JSON_OBJECT);

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(PusherOptionsTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    PusherOptions lhs;
    PusherOptions rhs;
    lhs.deserialize(POPULATED_JSON_OBJECT);

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(PusherOptionsTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    PusherOptions lhs;
    PusherOptions rhs;
    rhs.deserialize(POPULATED_JSON_OBJECT);

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
