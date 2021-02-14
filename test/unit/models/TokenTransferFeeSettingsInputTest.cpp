#include "enjinsdk/models/TokenTransferFeeSettings.hpp"
#include "../../suites/JsonTestSuite.hpp"
#include <string>

using namespace enjin::sdk::models;

class TokenTransferFeeSettingsInputTest : public JsonTestSuite {
public:
    TokenTransferFeeSettingsInput class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"type":"NONE","tokenId":"1","value":"1"})";

    static TokenTransferFeeSettingsInput create_default_transfer_fee_settings_input() {
        return TokenTransferFeeSettingsInput().set_type(TokenTransferFeeType::NONE)
                                              .set_token_id("1")
                                              .set_value("1");
    }
};

TEST_F(TokenTransferFeeSettingsInputTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EMPTY_JSON_OBJECT);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(TokenTransferFeeSettingsInputTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_type(TokenTransferFeeType::NONE)
                    .set_token_id("1")
                    .set_value("1");

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(TokenTransferFeeSettingsInputTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    TokenTransferFeeSettingsInput lhs;
    TokenTransferFeeSettingsInput rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(TokenTransferFeeSettingsInputTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    TokenTransferFeeSettingsInput lhs = create_default_transfer_fee_settings_input();
    TokenTransferFeeSettingsInput rhs = create_default_transfer_fee_settings_input();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(TokenTransferFeeSettingsInputTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    TokenTransferFeeSettingsInput lhs = create_default_transfer_fee_settings_input();
    TokenTransferFeeSettingsInput rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(TokenTransferFeeSettingsInputTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    TokenTransferFeeSettingsInput lhs;
    TokenTransferFeeSettingsInput rhs = create_default_transfer_fee_settings_input();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
