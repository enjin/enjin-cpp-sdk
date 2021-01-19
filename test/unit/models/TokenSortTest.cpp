#include "ModelsTestSuite.hpp"
#include "enjinsdk/models/TokenSort.hpp"

using namespace enjin::sdk::models;

class TokenSortTest : public ModelsTestSuite {
public:
    TokenSort class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"field":"id","direction":"asc"})";

    static TokenSort create_default_sort() {
        return TokenSort().set_field(TokenField::ID)
                          .set_direction(SortDirection::ASCENDING);
    }
};

TEST_F(TokenSortTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EMPTY_JSON_OBJECT);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(TokenSortTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_field(TokenField::ID)
                    .set_direction(SortDirection::ASCENDING);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(TokenSortTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    TokenSort lhs;
    TokenSort rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(TokenSortTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    TokenSort lhs = create_default_sort();
    TokenSort rhs = create_default_sort();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(TokenSortTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    TokenSort lhs = create_default_sort();
    TokenSort rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(TokenSortTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    TokenSort lhs;
    TokenSort rhs = create_default_sort();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
