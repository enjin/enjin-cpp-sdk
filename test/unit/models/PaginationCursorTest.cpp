#include "enjinsdk/models/PaginationCursor.hpp"
#include "gtest/gtest.h"

#include <optional>

using namespace enjin::sdk::models;

class PaginationCursorTest : public testing::Test {
public:
    PaginationCursor class_under_test;

    constexpr static char EMPTY_JSON_OBJECT[] = "{}";
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
    EXPECT_TRUE(class_under_test.get_total().has_value());
    EXPECT_TRUE(class_under_test.get_per_page().has_value());
    EXPECT_TRUE(class_under_test.get_current_page().has_value());
    EXPECT_TRUE(class_under_test.get_has_pages().has_value());
    EXPECT_TRUE(class_under_test.get_from().has_value());
    EXPECT_TRUE(class_under_test.get_to().has_value());
    EXPECT_TRUE(class_under_test.get_last_page().has_value());
    EXPECT_TRUE(class_under_test.get_has_more_pages().has_value());
    EXPECT_EQ(expected_int, class_under_test.get_total().value());
    EXPECT_EQ(expected_int, class_under_test.get_per_page().value());
    EXPECT_EQ(expected_int, class_under_test.get_current_page().value());
    EXPECT_EQ(expected_bool, class_under_test.get_has_pages().value());
    EXPECT_EQ(expected_int, class_under_test.get_from().value());
    EXPECT_EQ(expected_int, class_under_test.get_to().value());
    EXPECT_EQ(expected_int, class_under_test.get_last_page().value());
    EXPECT_EQ(expected_bool, class_under_test.get_has_more_pages().value());
}

TEST_F(PaginationCursorTest, SerializationFieldsHaveValuesReturnsPopulatedJsonObject) {
    // Arrange
    const std::string expected = POPULATED_JSON_OBJECT;
    class_under_test.deserialize(expected.c_str());

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(PaginationCursorTest, SerializationFieldsHaveNoValuesReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected = EMPTY_JSON_OBJECT;

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(PaginationCursorTest, EquilityObjectsDoHaveSameValuesReturnsTrue) {
    // Arrange
    const char* json = POPULATED_JSON_OBJECT;
    PaginationCursor cursor1;
    PaginationCursor cursor2;
    cursor1.deserialize(json);
    cursor2.deserialize(json);

    // Act
    bool actual = cursor1 == cursor2;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(PaginationCursorTest, EquilityObjectsDoNotHaveSameValuesReturnsFalse) {
    // Arrange
    const char* json = POPULATED_JSON_OBJECT;
    PaginationCursor cursor1;
    PaginationCursor cursor2;
    cursor1.deserialize(json);

    // Act
    bool actual = cursor1 == cursor2;

    // Assert
    ASSERT_FALSE(actual);
}
