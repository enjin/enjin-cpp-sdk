#include "gtest/gtest.h"
#include "JsonTestSuite.hpp"
#include "enjinsdk/project/AuthProject.hpp"
#include <string>

using namespace enjin::sdk::project;
using namespace enjin::test::suites;

class AuthProjectTest : public JsonTestSuite,
                        public testing::Test {
public:
    AuthProject class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"id":1,"secret":"1"})";

    static AuthProject create_default_request() {
        return AuthProject().set_id(1)
                            .set_secret("1");
    }
};

TEST_F(AuthProjectTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EMPTY_JSON_OBJECT);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(AuthProjectTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_id(1)
                    .set_secret("1");

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(AuthProjectTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    AuthProject lhs;
    AuthProject rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(AuthProjectTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    AuthProject lhs = create_default_request();
    AuthProject rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(AuthProjectTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    AuthProject lhs = create_default_request();
    AuthProject rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(AuthProjectTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    AuthProject lhs;
    AuthProject rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
