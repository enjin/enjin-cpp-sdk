#include "ModelsTestSuite.hpp"
#include "enjinsdk/models/AccessToken.hpp"

using namespace enjin::sdk::models;

class AccessTokenTest : public ModelsTestSuite {
public:
    AccessToken class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"accessToken":"xyz","expiresIn":1})";
};

TEST_F(AccessTokenTest, DeserializeEmptyStringFieldsDoNotHaveValues) {
    // Arrange
    const std::string json;

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_FALSE(class_under_test.get_token().has_value());
    EXPECT_FALSE(class_under_test.get_expires_in().has_value());
}

TEST_F(AccessTokenTest, DeserializeEmptyJsonObjectFieldsDoNotHaveValues) {
    // Arrange
    const std::string json(EMPTY_JSON_OBJECT);

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_FALSE(class_under_test.get_token().has_value());
    EXPECT_FALSE(class_under_test.get_expires_in().has_value());
}

TEST_F(AccessTokenTest, DeserializePopulatedJsonObjectFieldsHaveExpectedValues) {
    // Arrange
    const std::string expected_token("xyz");
    const long expected_expires_in = 1;
    const std::string json(POPULATED_JSON_OBJECT);

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_EQ(expected_token, class_under_test.get_token().value());
    EXPECT_EQ(expected_expires_in, class_under_test.get_expires_in().value());
}
