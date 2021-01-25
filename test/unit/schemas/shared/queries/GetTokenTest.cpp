#include "../../../models/ModelsTestSuite.hpp"
#include "enjinsdk/shared/GetToken.hpp"
#include <string>

using namespace enjin::sdk::shared;

class GetTokenTest : public ModelsTestSuite {
public:
    GetToken class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"id":"1"})";

    static GetToken create_default_request() {
        return GetToken().set_id("1");
    }
};

TEST_F(GetTokenTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EMPTY_JSON_OBJECT);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(GetTokenTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_id("1");

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(GetTokenTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    GetToken lhs;
    GetToken rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(GetTokenTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    GetToken lhs = create_default_request();
    GetToken rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(GetTokenTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    GetToken lhs = create_default_request();
    GetToken rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(GetTokenTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    GetToken lhs;
    GetToken rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
