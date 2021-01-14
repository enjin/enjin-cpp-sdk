#include "ModelsTestSuite.hpp"
#include "enjinsdk/models/PaginationCursor.hpp"

using namespace enjin::sdk::models;

class PaginationCursorTest : public ModelsTestSuite {
public:
    PaginationCursor class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"total":1,"perPage":1,"currentPage":1,"hasPages":true,"from":1,"to":1,"lastPage":1,"hasMorePages":true})";
};

TEST_F(PaginationCursorTest, DeserializeEmptyStringFieldsDoNotHaveValues) {
    // Arrange
    const char* json = "";

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_FALSE(class_under_test.get_total().has_value());
    EXPECT_FALSE(class_under_test.get_per_page().has_value());
    EXPECT_FALSE(class_under_test.get_current_page().has_value());
    EXPECT_FALSE(class_under_test.get_has_pages().has_value());
    EXPECT_FALSE(class_under_test.get_from().has_value());
    EXPECT_FALSE(class_under_test.get_to().has_value());
    EXPECT_FALSE(class_under_test.get_last_page().has_value());
    EXPECT_FALSE(class_under_test.get_has_more_pages().has_value());
}

TEST_F(PaginationCursorTest, DeserializeEmptyJsonObjectFieldsDoNotHaveValues) {
    // Arrange
    const char* json = EMPTY_JSON_OBJECT;

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_FALSE(class_under_test.get_total().has_value());
    EXPECT_FALSE(class_under_test.get_per_page().has_value());
    EXPECT_FALSE(class_under_test.get_current_page().has_value());
    EXPECT_FALSE(class_under_test.get_has_pages().has_value());
    EXPECT_FALSE(class_under_test.get_from().has_value());
    EXPECT_FALSE(class_under_test.get_to().has_value());
    EXPECT_FALSE(class_under_test.get_last_page().has_value());
    EXPECT_FALSE(class_under_test.get_has_more_pages().has_value());
}

TEST_F(PaginationCursorTest, DeserializePopulatedJsonObjectFieldsHaveExpectedValues) {
    // Arrange
    const int expected_int = 1;
    const bool expected_bool = true;
    const char* json = POPULATED_JSON_OBJECT;

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_EQ(expected_int, class_under_test.get_total().value());
    EXPECT_EQ(expected_int, class_under_test.get_per_page().value());
    EXPECT_EQ(expected_int, class_under_test.get_current_page().value());
    EXPECT_EQ(expected_bool, class_under_test.get_has_pages().value());
    EXPECT_EQ(expected_int, class_under_test.get_from().value());
    EXPECT_EQ(expected_int, class_under_test.get_to().value());
    EXPECT_EQ(expected_int, class_under_test.get_last_page().value());
    EXPECT_EQ(expected_bool, class_under_test.get_has_more_pages().value());
}

TEST_F(PaginationCursorTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    PaginationCursor lhs;
    PaginationCursor rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(PaginationCursorTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    PaginationCursor lhs;
    PaginationCursor rhs;
    lhs.deserialize(POPULATED_JSON_OBJECT);
    rhs.deserialize(POPULATED_JSON_OBJECT);

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(PaginationCursorTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    PaginationCursor lhs;
    PaginationCursor rhs;
    lhs.deserialize(POPULATED_JSON_OBJECT);

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(PaginationCursorTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    PaginationCursor lhs;
    PaginationCursor rhs;
    rhs.deserialize(POPULATED_JSON_OBJECT);

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
