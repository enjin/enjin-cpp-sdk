#include "RapidJsonUtils.hpp"
#include "gtest/gtest.h"
#include "../../utils/DummyObject.hpp"
#include <sstream>
#include <string>
#include <vector>

using namespace enjin::sdk::utils;
using namespace enjin::test::utils;

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

TEST_F(RapidJsonUtilsTest, GetArrayAsTypeVectorNoKeyArgDocumentIsNotArrayThrowsException) {
    // Arrange
    const std::string json;
    rapidjson::Document document;
    document.Parse(json.c_str());

    // Assert
    ASSERT_ANY_THROW(get_array_as_type_vector<DummyObject>(document));
}

TEST_F(RapidJsonUtilsTest, GetArrayAsTypeVectorWithKeyArgKeyIsNotArrayThrowsException) {
    // Arrange
    const std::string key("key");
    const std::string json(R"({"key":1})");
    rapidjson::Document document;
    document.Parse(json.c_str());

    // Assert
    ASSERT_ANY_THROW(get_array_as_type_vector<DummyObject>(document, key));
}

TEST_F(RapidJsonUtilsTest, GetArrayAsTypeVectorNoKeyArgDocumentIsArrayParsedVector) {
    // Arrange
    DummyObject expected = DummyObject::create_default_dummy_object();
    std::stringstream s;
    s << R"([)"
      << expected.serialize()
      << R"(,)"
      << expected.serialize()
      << R"(])";
    rapidjson::Document document;
    document.Parse(s.str().c_str());

    // Act
    std::vector<DummyObject> v = get_array_as_type_vector<DummyObject>(document);

    // Assert
    for (const DummyObject& actual : v) {
        EXPECT_EQ(expected, actual);
    }
}

TEST_F(RapidJsonUtilsTest, GetArrayAsTypeVectorWithKeyArgKeyIsArrayReturnsParsedVector) {
    // Arrange
    DummyObject expected = DummyObject::create_default_dummy_object();
    const std::string key("key");
    std::stringstream s;
    s << R"({"key":[)"
      << expected.serialize()
      << R"(,)"
      << expected.serialize()
      << R"(]})";
    rapidjson::Document document;
    document.Parse(s.str().c_str());

    // Act
    std::vector<DummyObject> v = get_array_as_type_vector<DummyObject>(document, key);

    // Assert
    for (const DummyObject& actual : v) {
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

TEST_F(RapidJsonUtilsTest, GetObjectAsTypeNoKeyArgDocumentIsObjectReturnsExpected) {
    // Arrange
    DummyObject expected = DummyObject::create_default_dummy_object();
    const std::string json(expected.serialize());
    rapidjson::Document document;
    document.Parse(json.c_str());

    // Act
    auto actual = get_object_as_type<DummyObject>(document);

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(RapidJsonUtilsTest, GetObjectAsTypeWithKeyArgKeyIsObjectReturnsExpected) {
    // Arrange
    DummyObject expected = DummyObject::create_default_dummy_object();
    const std::string key("key");
    std::stringstream s;
    s << R"({"key":)"
      << expected.serialize()
      << R"(})";
    rapidjson::Document document;
    document.Parse(s.str().c_str());

    // Act
    auto actual = get_object_as_type<DummyObject>(document, key);

    // Assert
    ASSERT_EQ(expected, actual);
}
