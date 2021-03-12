#include "JsonTestSuite.hpp"
#include "enjinsdk/internal/PaginationArguments.hpp"
#include <string>

using namespace enjin::sdk::shared;

class PaginationArgumentsTest : public JsonTestSuite {
public:
    PaginationArguments class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"pagination":{"page":1,"limit":1}})";

    static PaginationArguments create_default_arguments() {
        PaginationArguments arguments;
        arguments.set_pagination(1, 1);
        return arguments;
    }
};

TEST_F(PaginationArgumentsTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EMPTY_JSON_OBJECT);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(PaginationArgumentsTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_pagination(1, 1);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(PaginationArgumentsTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    PaginationArguments lhs;
    PaginationArguments rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(PaginationArgumentsTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    PaginationArguments lhs = create_default_arguments();
    PaginationArguments rhs = create_default_arguments();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(PaginationArgumentsTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    PaginationArguments lhs = create_default_arguments();
    PaginationArguments rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(PaginationArgumentsTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    PaginationArguments lhs;
    PaginationArguments rhs = create_default_arguments();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
