#include "gtest/gtest.h"
#include "JsonTestSuite.hpp"
#include "enjinsdk/models/AssetSort.hpp"

using namespace enjin::sdk::models;
using namespace enjin::test::suites;

class AssetSortTest : public JsonTestSuite,
                      public testing::Test {
public:
    AssetSort class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"field":"id","direction":"asc"})";

    static AssetSort create_default_sort() {
        return AssetSort().set_field(AssetField::ID)
                          .set_direction(SortDirection::ASCENDING);
    }
};

TEST_F(AssetSortTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EMPTY_JSON_OBJECT);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(AssetSortTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_field(AssetField::ID)
                    .set_direction(SortDirection::ASCENDING);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(AssetSortTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    AssetSort lhs;
    AssetSort rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(AssetSortTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    AssetSort lhs = create_default_sort();
    AssetSort rhs = create_default_sort();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(AssetSortTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    AssetSort lhs = create_default_sort();
    AssetSort rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(AssetSortTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    AssetSort lhs;
    AssetSort rhs = create_default_sort();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
