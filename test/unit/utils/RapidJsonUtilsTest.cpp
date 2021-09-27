/* Copyright 2021 Enjin Pte. Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "RapidJsonUtils.hpp"
#include "DummyObject.hpp"
#include "JsonTestSuite.hpp"
#include "gtest/gtest.h"
#include <sstream>
#include <string>
#include <vector>

using namespace enjin::sdk::utils;
using namespace enjin::test::suites;
using namespace enjin::test::utils;

class RapidJsonUtilsTest : public JsonTestSuite,
                           public testing::Test {
public:
    constexpr static char DEFAULT_KEY[] = "key";

    static rapidjson::Document create_object_document() {
        return rapidjson::Document(rapidjson::kObjectType);
    }
};

TEST_F(RapidJsonUtilsTest, JoinSerializedObjectToDocumentDocumentIsNotObjectThrowsException) {
    // Arrange
    const std::string expected_key(DEFAULT_KEY);
    rapidjson::Document document(rapidjson::kArrayType);
    std::stringstream s;
    s << R"({")"
      << expected_key
      << R"(":1})";

    // Assert
    ASSERT_ANY_THROW(join_serialized_object_to_document(document, s.str()));
}

TEST_F(RapidJsonUtilsTest, JoinSerializedObjectToDocumentJsonIsNotObjectDoesNothing) {
    // Arrange
    const std::string expected(EMPTY_JSON_OBJECT);
    const std::string json(R"("1":1)");
    rapidjson::Document document;
    document.Parse(expected.c_str());

    // Act
    join_serialized_object_to_document(document, json);

    // Assert
    ASSERT_EQ(expected, document_to_string(document));
}

TEST_F(RapidJsonUtilsTest, JoinSerializedObjectToDocumentDocumentIsObjectAddsMemberFields) {
    // Arrange
    const std::string expected_key(DEFAULT_KEY);
    rapidjson::Document document;
    document.Parse(EMPTY_JSON_OBJECT);
    std::stringstream s;
    s << R"({")"
      << expected_key
      << R"(":1})";

    // Act
    join_serialized_object_to_document(document, s.str());

    // Assert
    ASSERT_TRUE(document.HasMember(expected_key.c_str()));
    ASSERT_TRUE(document[expected_key.c_str()].IsInt());
}

TEST_F(RapidJsonUtilsTest, JoinSerializedObjectsToDocumentDocumentIsNotObjectThrowsException) {
    // Arrange
    const std::string expected_key1("key1");
    const std::string expected_key2("key2");
    rapidjson::Document document(rapidjson::kArrayType);
    std::stringstream s1;
    s1 << R"({")"
       << expected_key1
       << R"(":1})";
    std::stringstream s2;
    s2 << R"({")"
       << expected_key2
       << R"(":1})";
    std::vector<std::string> objects({s1.str(), s2.str()});

    // Assert
    ASSERT_ANY_THROW(join_serialized_objects_to_document(document, objects));
}

TEST_F(RapidJsonUtilsTest, JoinSerializedObjectsToDocumentJsonsAreNotObjectsDoesNothing) {
    // Arrange
    const std::string expected(EMPTY_JSON_OBJECT);
    const std::vector<std::string> jsons({R"("1":1)"});
    rapidjson::Document document;
    document.Parse(expected.c_str());

    // Act
    join_serialized_objects_to_document(document, jsons);

    // Assert
    ASSERT_EQ(expected, document_to_string(document));
}

TEST_F(RapidJsonUtilsTest, JoinSerializedObjectsToDocumentDocumentIsObjectAddsMemberFields) {
    // Arrange
    const std::string expected_key1("key1");
    const std::string expected_key2("key2");
    rapidjson::Document document;
    document.Parse(EMPTY_JSON_OBJECT);
    std::stringstream s1;
    s1 << R"({")"
       << expected_key1
       << R"(":1})";
    std::stringstream s2;
    s2 << R"({")"
       << expected_key2
       << R"(":1})";
    std::vector<std::string> objects({s1.str(), s2.str()});

    // Act
    join_serialized_objects_to_document(document, objects);

    // Assert
    ASSERT_TRUE(document.HasMember(expected_key1.c_str()));
    ASSERT_TRUE(document[expected_key1.c_str()].IsInt());
    ASSERT_TRUE(document.HasMember(expected_key2.c_str()));
    ASSERT_TRUE(document[expected_key2.c_str()].IsInt());
}

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

TEST_F(RapidJsonUtilsTest, SetBooleanMemberMemberIsSet) {
    // Arrange
    const char* expected_key = DEFAULT_KEY;
    const bool expected_value = true;
    rapidjson::Document document = create_object_document();

    // Act
    set_boolean_member(document, expected_key, expected_value);

    // Assert
    ASSERT_TRUE(document.HasMember(expected_key));
    ASSERT_TRUE(document[expected_key].IsBool());
    ASSERT_EQ(expected_value, document[expected_key].GetBool());
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

TEST_F(RapidJsonUtilsTest, SetObjectMemberFromStringStringIsJsonObjectMemberIsSet) {
    // Arrange
    const char* expected_key = "key";
    const std::string expected_value = DummyObject::create_default_dummy_object().serialize();
    rapidjson::Document document = create_object_document();

    // Act
    set_object_member_from_string(document, expected_key, expected_value);

    // Assert
    ASSERT_TRUE(document.HasMember(expected_key));
    ASSERT_TRUE(document[expected_key].IsObject());
    ASSERT_EQ(expected_value, get_object_as_string(document, expected_key));
}

TEST_F(RapidJsonUtilsTest, SetObjectMemberFromStringStringIsNotJsonObjectMemberIsNotSet) {
    // Arrange
    const char* expected_key = "key";
    const std::string value;
    rapidjson::Document document = create_object_document();

    // Act
    set_object_member_from_string(document, expected_key, value);

    // Assert
    ASSERT_FALSE(document.HasMember(expected_key));
}

TEST_F(RapidJsonUtilsTest, SetObjectMemberFromTypeMemberIsSet) {
    // Arrange
    const char* expected_key = DEFAULT_KEY;
    const DummyObject expected_value = DummyObject::create_default_dummy_object();
    rapidjson::Document document = create_object_document();

    // Act
    set_object_member_from_type<DummyObject>(document, expected_key, expected_value);

    // Assert
    ASSERT_TRUE(document.HasMember(expected_key));
    ASSERT_TRUE(document[expected_key].IsObject());
    ASSERT_EQ(expected_value, get_object_as_type<DummyObject>(document, expected_key));
}
