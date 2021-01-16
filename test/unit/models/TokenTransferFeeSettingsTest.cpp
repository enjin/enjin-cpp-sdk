#include "ModelsTestSuite.hpp"
#include "enjinsdk/models/TokenTransferFeeSettings.hpp"

using namespace enjin::sdk::models;

class TokenTransferFeeSettingsTest : public ModelsTestSuite {
public:
    TokenTransferFeeSettings class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"type":"NONE","tokenId":"1","value":"1"})";
};

TEST_F(TokenTransferFeeSettingsTest, DeserializeEmptyStringFieldsDoNotHaveValues) {
    // Arrange
    const std::string json;

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_FALSE(class_under_test.get_type().has_value());
    EXPECT_FALSE(class_under_test.get_token_id().has_value());
    EXPECT_FALSE(class_under_test.get_value().has_value());
}

TEST_F(TokenTransferFeeSettingsTest, DeserializeEmptyJsonObjectFieldsDoNotHaveValues) {
    // Arrange
    const std::string json(EMPTY_JSON_OBJECT);

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_FALSE(class_under_test.get_type().has_value());
    EXPECT_FALSE(class_under_test.get_token_id().has_value());
    EXPECT_FALSE(class_under_test.get_value().has_value());
}

TEST_F(TokenTransferFeeSettingsTest, DeserializePopulatedJsonObjectFieldsHaveExpectedValues) {
    // Arrange
    const std::string expected_string("1");
    const TokenTransferFeeType expected_type = TokenTransferFeeType::NONE;
    const std::string json(POPULATED_JSON_OBJECT);

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_EQ(expected_type, class_under_test.get_type().value());
    EXPECT_EQ(expected_string, class_under_test.get_token_id().value());
    EXPECT_EQ(expected_string, class_under_test.get_value().value());
}

TEST_F(TokenTransferFeeSettingsTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    TokenTransferFeeSettings lhs;
    TokenTransferFeeSettings rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(TokenTransferFeeSettingsTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    TokenTransferFeeSettings lhs;
    TokenTransferFeeSettings rhs;
    lhs.deserialize(POPULATED_JSON_OBJECT);
    rhs.deserialize(POPULATED_JSON_OBJECT);

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(TokenTransferFeeSettingsTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    TokenTransferFeeSettings lhs;
    TokenTransferFeeSettings rhs;
    lhs.deserialize(POPULATED_JSON_OBJECT);

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(TokenTransferFeeSettingsTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    TokenTransferFeeSettings lhs;
    TokenTransferFeeSettings rhs;
    rhs.deserialize(POPULATED_JSON_OBJECT);

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
