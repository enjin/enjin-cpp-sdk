#include "JsonTestSuite.hpp"
#include "TransactionRequestArgumentsTestSuite.hpp"
#include "enjinsdk/shared/SendEnj.hpp"
#include "gtest/gtest.h"
#include <string>

using namespace enjin::sdk::shared;
using namespace enjin::test::suites;

class SendEnjTest : public TransactionRequestArgumentsTestSuite<SendEnj>,
                    public JsonTestSuite,
                    public testing::Test {
public:
    SendEnj class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"recipientAddress":"1","value":"1"})";

    static SendEnj create_default_request() {
        SendEnj request = SendEnj()
                .set_recipient_address("1")
                .set_value("1");
        set_transaction_request_arguments(request);
        return request;
    }
};

TEST_F(SendEnjTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EMPTY_JSON_OBJECT);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(SendEnjTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_recipient_address("1")
                    .set_value("1");

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(SendEnjTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    SendEnj lhs;
    SendEnj rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(SendEnjTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    SendEnj lhs = create_default_request();
    SendEnj rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(SendEnjTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    SendEnj lhs = create_default_request();
    SendEnj rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(SendEnjTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    SendEnj lhs;
    SendEnj rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
