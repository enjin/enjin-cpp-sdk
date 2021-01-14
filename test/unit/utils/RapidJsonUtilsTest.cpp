#include "RapidJsonUtils.hpp"
#include "gtest/gtest.h"
#include <string>
#include <vector>

using namespace enjin::sdk::utils;

class RapidJsonUtilsTest : public testing::Test {
};

TEST_F(RapidJsonUtilsTest, GetArrayAsSerializedVectorNoKeyArgDocumentIsNotArrayThrowsException) {
    // Arrange
    const std::string json;
    rapidjson::Document document;
    document.Parse(json.c_str());

    // Assert
    ASSERT_ANY_THROW(get_array_as_serialized_vector(document));
}

TEST_F(RapidJsonUtilsTest, GetArrayAsSerializedVectorWithKeyArgKeyIsNotArrayThrowsException) {
    // Arrange
    const std::string key("key");
    const std::string json(R"({"key":1})");
    rapidjson::Document document;
    document.Parse(json.c_str());

    // Assert
    ASSERT_ANY_THROW(get_array_as_serialized_vector(document, key));
}

TEST_F(RapidJsonUtilsTest, GetArrayAsSerializedVectorNoKeyArgDocumentIsArrayReturnsVectorWithExpectedElements) {
    // Arrange
    const std::string expected(R"({})");
    const std::string json(R"([{}, {}, {}])");
    rapidjson::Document document;
    document.Parse(json.c_str());

    // Act
    std::vector<std::string> v = get_array_as_serialized_vector(document);

    // Assert
    for (const std::string& actual : v) {
        EXPECT_EQ(expected, actual);
    }
}

TEST_F(RapidJsonUtilsTest, GetArrayAsSerializedVectorWithKeyArgKeyIsArrayReturnsVectorWithExpectedElements) {
    // Arrange
    const std::string expected(R"({})");
    const std::string key("key");
    const std::string json(R"({"key":[{}, {}, {}]})");
    rapidjson::Document document;
    document.Parse(json.c_str());

    // Act
    std::vector<std::string> v = get_array_as_serialized_vector(document, key);

    // Assert
    for (const std::string& actual : v) {
        EXPECT_EQ(expected, actual);
    }
}

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

TEST_F(RapidJsonUtilsTest, GetObjectAsStringWithKeyArgKeyIsObjectReturnsExpectedString) {
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
