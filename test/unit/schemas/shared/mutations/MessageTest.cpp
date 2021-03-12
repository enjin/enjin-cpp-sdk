#include "JsonTestSuite.hpp"
#include "enjinsdk/shared/Message.hpp"
#include <string>

using namespace enjin::sdk::shared;

class MessageTest : public JsonTestSuite {
public:
    Message class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"message":"1"})";

    static Message create_default_request() {
        return Message().set_message("1");
    }
};

TEST_F(MessageTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EMPTY_JSON_OBJECT);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(MessageTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_message("1");

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(MessageTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    Message lhs;
    Message rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(MessageTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    Message lhs = create_default_request();
    Message rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(MessageTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    Message lhs = create_default_request();
    Message rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(MessageTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    Message lhs;
    Message rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
