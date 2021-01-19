#include "RapidJsonUtils.hpp"
#include "gtest/gtest.h"
#include "../../utils/DummyObject.hpp"
#include <sstream>
#include <string>
#include <vector>

using namespace enjin::sdk::utils;
using namespace enjin::test::utils;

class RapidJsonUtilsTest : public testing::Test {
public:
    constexpr static char DEFAULT_KEY[] = "key";

    static rapidjson::Document create_object_document() {
        return rapidjson::Document(rapidjson::kObjectType);
    }
};

TEST_F(RapidJsonUtilsTest, DocumentToStringReturnsExpectedString) {
    // Arrange
    const std::string expected = DummyObject::create_default_dummy_object().serialize();
    rapidjson::Document document;
    document.Parse(expected.c_str());

    // Act
    std::string actual = document_to_string(document);

    // Assert
    ASSERT_EQ(expected, actual);
}

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

TEST_F(RapidJsonUtilsTest, SetMemberAssertDocumentIsNotObjectAndKeyIsEmptyThrowException) {
    // Arrange
    rapidjson::Document document;
    const std::string key;

    // Assert
    ASSERT_ANY_THROW(set_member_assert(document, key));
}

TEST_F(RapidJsonUtilsTest, SetMemberAssertDocumentIsObjectAndKeyIsEmptyThrowException) {
    // Arrange
    rapidjson::Document document = create_object_document();
    const std::string key;

    // Assert
    ASSERT_ANY_THROW(set_member_assert(document, key));
}

TEST_F(RapidJsonUtilsTest, SetMemberAssertDocumentIsNotObjectAndKeyIsNotEmptyThrowException) {
    // Arrange
    rapidjson::Document document;
    const std::string key(DEFAULT_KEY);

    // Assert
    ASSERT_ANY_THROW(set_member_assert(document, key));
}

TEST_F(RapidJsonUtilsTest, SetMemberAssertDocumentIsObjectAndKeyIsNotEmptyDoesNotThrowException) {
    // Arrange
    rapidjson::Document document = create_object_document();
    const std::string key(DEFAULT_KEY);

    // Assert
    ASSERT_NO_THROW(set_member_assert(document, key));
}

TEST_F(RapidJsonUtilsTest, SetArrayMemberFromTypeVectorArrayWithObjectsIsSet) {
    // Arrange
    const char* expected_key = DEFAULT_KEY;
    const DummyObject expected_value = DummyObject::create_default_dummy_object();
    rapidjson::Document document = create_object_document();
    std::vector<DummyObject> vector;
    vector.push_back(expected_value);
    vector.push_back(expected_value);
    vector.push_back(expected_value);

    // Act
    set_array_member_from_type_vector<DummyObject>(document, expected_key, vector);

    // Assert
    ASSERT_TRUE(document.HasMember(expected_key));
    ASSERT_TRUE(document[expected_key].IsArray());

    std::vector<DummyObject> actual_vector = get_array_as_type_vector<DummyObject>(document, expected_key);
    for (const DummyObject& actual_value : actual_vector) {
        EXPECT_EQ(expected_value, actual_value);
    }
}

TEST_F(RapidJsonUtilsTest, SetArrayMemberFromStringVectorArrayWithStringsIsSet) {
    // Arrange
    const char* expected_key = DEFAULT_KEY;
    const std::string expected_value("value");
    rapidjson::Document document = create_object_document();
    std::vector<std::string> vector;
    vector.push_back(expected_value);
    vector.push_back(expected_value);
    vector.push_back(expected_value);

    // Act
    set_array_member_from_string_vector(document, expected_key, vector);

    // Assert
    ASSERT_TRUE(document.HasMember(expected_key));
    ASSERT_TRUE(document[expected_key].IsArray());
    for (auto& e : document[expected_key].GetArray()) {
        bool e_is_string = e.IsString();
        EXPECT_TRUE(e_is_string);

        if (e_is_string) {
            std::string actual_value = e.GetString();
            EXPECT_EQ(expected_value, actual_value);
        }
    }
}

TEST_F(RapidJsonUtilsTest, SetIntegerMemberMemberIsSet) {
    // Arrange
    const char* expected_key = DEFAULT_KEY;
    const int expected_value = 1;
    rapidjson::Document document = create_object_document();

    // Act
    set_integer_member(document, expected_key, expected_value);

    // Assert
    ASSERT_TRUE(document.HasMember(expected_key));
    ASSERT_TRUE(document[expected_key].IsInt());
    ASSERT_EQ(expected_value, document[expected_key].GetInt());
}

TEST_F(RapidJsonUtilsTest, SetStringMemberMemberIsSet) {
    // Arrange
    const char* expected_key = DEFAULT_KEY;
    const std::string expected_value("1");
    rapidjson::Document document = create_object_document();

    // Act
    set_string_member(document, expected_key, expected_value);

    // Assert
    ASSERT_TRUE(document.HasMember(expected_key));
    ASSERT_TRUE(document[expected_key].IsString());
    ASSERT_EQ(expected_value, document[expected_key].GetString());
}
