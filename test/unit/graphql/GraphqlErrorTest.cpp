#include "enjinsdk/GraphqlError.hpp"
#include "gtest/gtest.h"

using namespace enjin::sdk::graphql;

class GraphqlErrorTest : public testing::Test {
public:
    GraphqlError class_under_test;

    constexpr static char EMPTY_JSON_OBJECT[] = "{}";
    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"message":"xyz","code":1,"details":"xyz","locations":[{"key":1}]})";
};

TEST_F(GraphqlErrorTest, DeserializeEmptyStringFieldsDoNotHaveValues) {
    // Arrange
    const char* json = "";

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_FALSE(class_under_test.get_message().has_value());
    EXPECT_FALSE(class_under_test.get_code().has_value());
    EXPECT_FALSE(class_under_test.get_locations().has_value());
    EXPECT_FALSE(class_under_test.get_details().has_value());
}

TEST_F(GraphqlErrorTest, DeserializeEmptyJsonObjectFieldsDoNotHaveValues) {
    // Arrange
    const char* json = EMPTY_JSON_OBJECT;

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_FALSE(class_under_test.get_message().has_value());
    EXPECT_FALSE(class_under_test.get_code().has_value());
    EXPECT_FALSE(class_under_test.get_locations().has_value());
    EXPECT_FALSE(class_under_test.get_details().has_value());
}

TEST_F(GraphqlErrorTest, DeserializePopulatedJsonObjectFieldsHaveValues) {
    // Arrange
    const int expected_int = 1;
    const std::string expected_string("xyz");
    const std::string expected_key("key");
    const char* json = POPULATED_JSON_OBJECT;

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_TRUE(class_under_test.get_message().has_value());
    EXPECT_TRUE(class_under_test.get_code().has_value());
    EXPECT_TRUE(class_under_test.get_details().has_value());
    EXPECT_TRUE(class_under_test.get_locations().has_value());
    EXPECT_EQ(expected_string, class_under_test.get_message().value());
    EXPECT_EQ(expected_int, class_under_test.get_code().value());
    EXPECT_EQ(expected_string, class_under_test.get_details().value());
    EXPECT_FALSE(class_under_test.get_locations().value().empty());
    for (auto l : class_under_test.get_locations().value()) {
        EXPECT_EQ(expected_int, l.at(expected_key));
    }
}

TEST_F(GraphqlErrorTest, SerializationFieldsHaveValuesReturnsPopulatedJsonObject) {
    // Arrange
    const std::string expected = POPULATED_JSON_OBJECT;
    class_under_test.deserialize(expected.c_str());

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(GraphqlErrorTest, SerializationFieldsHaveNoValuesReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected = EMPTY_JSON_OBJECT;

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}
