#include "JsonTestSuite.hpp"
#include "enjinsdk/models/LinkingInfo.hpp"
#include <string>

using namespace enjin::sdk::models;

class LinkingInfoTest : public JsonTestSuite {
public:
    LinkingInfo class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"code":"1","qr":"1"})";
};

TEST_F(LinkingInfoTest, DeserializeEmptyStringFieldsDoNotHaveValues) {
    // Arrange
    const std::string json;

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_FALSE(class_under_test.get_code().has_value());
    EXPECT_FALSE(class_under_test.get_qr().has_value());
}

TEST_F(LinkingInfoTest, DeserializeEmptyJsonObjectFieldsDoNotHaveValues) {
    // Arrange
    const std::string json(EMPTY_JSON_OBJECT);

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_FALSE(class_under_test.get_code().has_value());
    EXPECT_FALSE(class_under_test.get_qr().has_value());
}

TEST_F(LinkingInfoTest, DeserializePopulatedJsonObjectFieldsHaveExpectedValues) {
    // Arrange
    const std::string expected_string("1");
    const std::string json(POPULATED_JSON_OBJECT);

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_EQ(expected_string, class_under_test.get_code().value());
    EXPECT_EQ(expected_string, class_under_test.get_qr().value());
}

TEST_F(LinkingInfoTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    LinkingInfo lhs;
    LinkingInfo rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(LinkingInfoTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    LinkingInfo lhs;
    LinkingInfo rhs;
    lhs.deserialize(POPULATED_JSON_OBJECT);
    rhs.deserialize(POPULATED_JSON_OBJECT);

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(LinkingInfoTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    LinkingInfo lhs;
    LinkingInfo rhs;
    lhs.deserialize(POPULATED_JSON_OBJECT);

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(LinkingInfoTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    LinkingInfo lhs;
    LinkingInfo rhs;
    rhs.deserialize(POPULATED_JSON_OBJECT);

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
