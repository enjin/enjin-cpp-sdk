#include "../models/ModelsTestSuite.hpp"
#include "enjinsdk/GraphqlError.hpp"
#include <string>

using namespace enjin::sdk::graphql;

class GraphqlErrorTest : public ModelsTestSuite {
public:
    GraphqlError class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"message":"xyz","code":1,"details":"xyz","locations":[{"key":1}]})";
};

TEST_F(GraphqlErrorTest, DeserializeEmptyStringFieldsDoNotHaveValues) {
    // Arrange
    const std::string json;

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
    const std::string json(EMPTY_JSON_OBJECT);

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
    const std::string json(POPULATED_JSON_OBJECT);

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

TEST_F(GraphqlErrorTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    GraphqlError lhs;
    GraphqlError rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(GraphqlErrorTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    GraphqlError lhs;
    GraphqlError rhs;
    lhs.deserialize(POPULATED_JSON_OBJECT);
    rhs.deserialize(POPULATED_JSON_OBJECT);

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(GraphqlErrorTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    GraphqlError lhs;
    GraphqlError rhs;
    lhs.deserialize(POPULATED_JSON_OBJECT);

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(GraphqlErrorTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    GraphqlError lhs;
    GraphqlError rhs;
    rhs.deserialize(POPULATED_JSON_OBJECT);

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
