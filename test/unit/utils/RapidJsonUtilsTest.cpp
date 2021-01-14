#include "RapidJsonUtils.hpp"
#include "gtest/gtest.h"
#include <string>

using namespace enjin::sdk::utils;

class RapidJsonUtilsTest : public testing::Test {
};

TEST_F(RapidJsonUtilsTest, GetObjectAsStringNoKeyArgDocumentIsNotObjectThrowsException) {
    // Arrange
    const std::string json;
    rapidjson::Document document;
    document.Parse(json.c_str());

    // Assert
    ASSERT_ANY_THROW(get_object_as_string(document));
}

TEST_F(RapidJsonUtilsTest, GetObjectAsStringWithKeyArgKeyIsNotObjectThrowsException) {
    // Arrange
    const std::string key("key");
    const std::string json(R"({"key":1})");
    rapidjson::Document document;
    document.Parse(json.c_str());

    // Assert
    ASSERT_ANY_THROW(get_object_as_string(document, key));
}

TEST_F(RapidJsonUtilsTest, GetObjectAsStringNoKeyArgDocumentIsObjectReturnsExpectedString) {
    // Arrange
    const std::string expected(R"({"el":1})");
    rapidjson::Document document;
    document.Parse(expected.c_str());

    // Act
    std::string actual = get_object_as_string(document);

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(RapidJsonUtilsTest, GetObjectAsStringWithKeyArgKeyIsNotObjectReturnsExpectedString) {
    // Arrange
    const std::string expected(R"({"el":1})");
    const std::string key("key");
    const std::string json(R"({"key":{"el":1}})");
    rapidjson::Document document;
    document.Parse(json.c_str());

    // Act
    std::string actual = get_object_as_string(document, key);

    // Assert
    ASSERT_EQ(expected, actual);
}
