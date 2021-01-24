#include "../../../models/ModelsTestSuite.hpp"
#include "enjinsdk/shared/SendToken.hpp"
#include <string>

using namespace enjin::sdk::shared;

class SendTokenTest : public ModelsTestSuite {
public:
    SendToken class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"recipientAddress":"1","tokenId":"1","tokenIndex":"1","value":"1","data":"1"})";

    static SendToken create_default_request() {
        return SendToken().set_recipient_address("1")
                          .set_token_id("1")
                          .set_token_index("1")
                          .set_value("1")
                          .set_data("1");
    }
};

TEST_F(SendTokenTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EMPTY_JSON_OBJECT);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(SendTokenTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_recipient_address("1")
                    .set_token_id("1")
                    .set_token_index("1")
                    .set_value("1")
                    .set_data("1");

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(SendTokenTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    SendToken lhs;
    SendToken rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(SendTokenTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    SendToken lhs = create_default_request();
    SendToken rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(SendTokenTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    SendToken lhs = create_default_request();
    SendToken rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(SendTokenTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    SendToken lhs;
    SendToken rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
