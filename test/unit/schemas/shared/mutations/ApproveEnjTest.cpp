#include "JsonTestSuite.hpp"
#include "enjinsdk/shared/ApproveEnj.hpp"
#include <string>

using namespace enjin::sdk::shared;

class ApproveEnjTest : public JsonTestSuite {
public:
    ApproveEnj class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"value":"1"})";

    static ApproveEnj create_default_request() {
        return ApproveEnj().set_value("1");
    }
};

TEST_F(ApproveEnjTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EMPTY_JSON_OBJECT);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(ApproveEnjTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_value("1");

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(ApproveEnjTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    ApproveEnj lhs;
    ApproveEnj rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(ApproveEnjTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    ApproveEnj lhs = create_default_request();
    ApproveEnj rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(ApproveEnjTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    ApproveEnj lhs = create_default_request();
    ApproveEnj rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(ApproveEnjTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    ApproveEnj lhs;
    ApproveEnj rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
