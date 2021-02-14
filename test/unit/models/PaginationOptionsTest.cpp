#include "enjinsdk/models/PaginationOptions.hpp"
#include "../../suites/JsonTestSuite.hpp"

using namespace enjin::sdk::models;

class PaginationOptionsTest : public JsonTestSuite {
public:
    PaginationOptions class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"page":1,"limit":1})";

    static PaginationOptions create_default_pagination_options() {
        return PaginationOptions().set_page(1)
                                  .set_limit(1);
    }
};

TEST_F(PaginationOptionsTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EMPTY_JSON_OBJECT);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(PaginationOptionsTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_page(1)
                    .set_limit(1);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(PaginationOptionsTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    PaginationOptions lhs;
    PaginationOptions rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(PaginationOptionsTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    PaginationOptions lhs = create_default_pagination_options();
    PaginationOptions rhs = create_default_pagination_options();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(PaginationOptionsTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    PaginationOptions lhs = create_default_pagination_options();
    PaginationOptions rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(PaginationOptionsTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    PaginationOptions lhs;
    PaginationOptions rhs = create_default_pagination_options();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
