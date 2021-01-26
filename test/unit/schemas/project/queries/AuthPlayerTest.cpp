#include "../../../models/ModelsTestSuite.hpp"
#include "enjinsdk/project/AuthPlayer.hpp"
#include <string>

using namespace enjin::sdk::project;

class AuthPlayerTest : public ModelsTestSuite {
public:
    AuthPlayer class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"id":"1"})";

    static AuthPlayer create_default_request() {
        return AuthPlayer().set_id("1");
    }
};

TEST_F(AuthPlayerTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EMPTY_JSON_OBJECT);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(AuthPlayerTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_id("1");

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(AuthPlayerTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    AuthPlayer lhs;
    AuthPlayer rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(AuthPlayerTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    AuthPlayer lhs = create_default_request();
    AuthPlayer rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(AuthPlayerTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    AuthPlayer lhs = create_default_request();
    AuthPlayer rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(AuthPlayerTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    AuthPlayer lhs;
    AuthPlayer rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
