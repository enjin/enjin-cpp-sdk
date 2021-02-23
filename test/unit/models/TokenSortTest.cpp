#include "enjinsdk/models/AssetSort.hpp"
#include "../../suites/JsonTestSuite.hpp"

using namespace enjin::sdk::models;

class TokenSortTest : public JsonTestSuite {
public:
    AssetSort class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"field":"id","direction":"asc"})";

    static AssetSort create_default_sort() {
        return AssetSort().set_field(AssetField::ID)
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
    class_under_test.set_field(AssetField::ID)
                    .set_direction(SortDirection::ASCENDING);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(TokenSortTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    AssetSort lhs;
    AssetSort rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(TokenSortTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    AssetSort lhs = create_default_sort();
    AssetSort rhs = create_default_sort();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(TokenSortTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    AssetSort lhs = create_default_sort();
    AssetSort rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(TokenSortTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    AssetSort lhs;
    AssetSort rhs = create_default_sort();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
