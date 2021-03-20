#include "enjinsdk_utils/StringUtils.hpp"
#include "gtest/gtest.h"
#include <string>

using namespace enjin::utils;

class StringUtilTest : public testing::Test {

};

TEST_F(StringUtilTest, IsEmptyOrWhiteSpaceGivenEmptyReturnsTrue) {
    // Arrange
    const std::string input;

    // Act
    bool actual = is_empty_or_whitespace(input);

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(StringUtilTest, IsEmptyOrWhiteSpaceGivenWhitespaceReturnsTrue) {
    // Arrange
    const std::string input(" ");

    // Act
    bool actual = is_empty_or_whitespace(input);

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(StringUtilTest, IsEmptyOrWhiteSpaceGivenCharacterStringReturnsFalse) {
    // Arrange
    const std::string input("string");

    // Act
    bool actual = is_empty_or_whitespace(input);

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(StringUtilTest, JoinReturnsStringWithJoinedValues) {
    // Arrange
    std::string expected("aaa.bbb.ccc");
    std::string separator(".");
    std::list<std::string> input;
    input.emplace_back("aaa");
    input.emplace_back("bbb");
    input.emplace_back("ccc");

    // Act
    std::string actual = join(separator, input);

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(StringUtilTest, ToLowerGivenUppercaseStringReturnsLowercaseString) {
    // Arrange
    const std::string input("STRING");
    const std::string expected("string");

    // Act
    std::string actual = to_lower(input);

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(StringUtilTest, ToLowerInputIsLowercaseStringReturnsInputString) {
    // Arrange
    const std::string expected("string");

    // Act
    std::string actual = to_lower(expected);

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(StringUtilTest, ToLowerInputHasNoLettersReturnsInputString) {
    // Arrange
    const std::string expected("`~!@#$%^&*()-=_+[]{}\\|;:'\",./<>?1234567890");

    // Act
    std::string actual = to_lower(expected);

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(StringUtilTest, ToUpperGivenLowercaseStringReturnsUppercaseString) {
    // Arrange
    const std::string input("string");
    const std::string expected("STRING");

    // Act
    std::string actual = to_upper(input);

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(StringUtilTest, ToUpperInputIsUppercaseStringReturnsInputString) {
    // Arrange
    const std::string expected("STRING");

    // Act
    std::string actual = to_upper(expected);

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(StringUtilTest, ToUpperInputHasNoLettersReturnsInputString) {
    // Arrange
    const std::string expected("`~!@#$%^&*()-=_+[]{}\\|;:'\",./<>?1234567890");

    // Act
    std::string actual = to_upper(expected);

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(StringUtilTest, TrimInputDoesHaveWhitespaceReturnsStringWithNoWhitespace) {
    // Arrange
    const std::string input("   string   ");
    const std::string expected("string");

    // Act
    std::string actual = trim(input);

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(StringUtilTest, TrimInputDoesNotHaveWhitespaceReturnsInputString) {
    // Arrange
    const std::string expected("string");

    // Act
    std::string actual = trim(expected);

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(StringUtilTest, TrimInputIsOnlyWhitespaceReturnsEmptyString) {
    // Arrange
    const std::string input(" ");

    // Act
    std::string actual = trim(input);

    // Assert
    ASSERT_TRUE(actual.empty());
}

TEST_F(StringUtilTest, ReplaceInputDoesHaveOldValueReturnsStringWithNewValues) {
    // Arrange
    const std::string input("aaabbbcccbbb");
    const std::string old_value("bbb");
    const std::string new_value("ddd");
    const std::string expected("aaadddcccddd");

    // Act
    std::string actual = replace(input, old_value, new_value);

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(StringUtilTest, ReplaceInputDoesNotHaveOldValueReturnsInputString) {
    // Arrange
    const std::string expected("aaa");
    const std::string old_value("bbb");
    const std::string new_value("ddd");

    // Act
    std::string actual = replace(expected, old_value, new_value);

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(StringUtilTest, SplitInputDoesHaveSeparatorReturnsVectorWithSeparatedStrings) {
    // Arrange
    const std::string input("aaa.aaa.aaa");
    const std::string separator(".");
    const std::string expected("aaa");

    // Act
    const std::vector<std::string> result = split(input, separator);

    // Assert
    for (const std::string& actual : result) {
        EXPECT_EQ(expected, actual);
    }
}

TEST_F(StringUtilTest, SplitInputDoesNotHaveSeparatorReturnsVectorWithOnlyInput) {
    // Arrange
    const std::string input("aaa");
    const std::string separator(".");
    const std::string expected("aaa");

    // Act
    const std::vector<std::string> result = split(input, separator);

    // Assert
    EXPECT_TRUE(result.size() == 1);
    for (const std::string& actual : result) {
        EXPECT_EQ(expected, actual);
    }
}

TEST_F(StringUtilTest, SplitInputIsSeparatorReturnsVectorWithEmptyStrings) {
    // Arrange
    const std::string input(".");

    // Act
    const std::vector<std::string> result = split(input, input);

    // Assert
    for (const std::string& actual : result) {
        EXPECT_TRUE(actual.empty());
    }
}
