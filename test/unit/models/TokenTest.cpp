#include "ModelsTestSuite.hpp"
#include "enjinsdk/models/Token.hpp"

using namespace enjin::sdk::models;

class TokenTest : public ModelsTestSuite {
public:
    Token class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"id":"1","name":"1","stateData":{},"configData":{},"variantMode":"NONE","variants":[{}, {}, {}],"createdAt":"1","updatedAt":"1"})";
};

TEST_F(TokenTest, DeserializeEmptyStringFieldsDoNotHaveValues) {
    // Arrange
    const std::string json;

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_FALSE(class_under_test.get_id().has_value());
    EXPECT_FALSE(class_under_test.get_name().has_value());
    EXPECT_FALSE(class_under_test.get_state_data().has_value());
    EXPECT_FALSE(class_under_test.get_config_data().has_value());
    EXPECT_FALSE(class_under_test.get_variant_mode().has_value());
    EXPECT_FALSE(class_under_test.get_variants().has_value());
    EXPECT_FALSE(class_under_test.get_created_at().has_value());
    EXPECT_FALSE(class_under_test.get_updated_at().has_value());
}

TEST_F(TokenTest, DeserializeEmptyJsonObjectFieldsDoNotHaveValues) {
    // Arrange
    const std::string json(EMPTY_JSON_OBJECT);

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_FALSE(class_under_test.get_id().has_value());
    EXPECT_FALSE(class_under_test.get_name().has_value());
    EXPECT_FALSE(class_under_test.get_state_data().has_value());
    EXPECT_FALSE(class_under_test.get_config_data().has_value());
    EXPECT_FALSE(class_under_test.get_variant_mode().has_value());
    EXPECT_FALSE(class_under_test.get_variants().has_value());
    EXPECT_FALSE(class_under_test.get_created_at().has_value());
    EXPECT_FALSE(class_under_test.get_updated_at().has_value());
}

TEST_F(TokenTest, DeserializePopulatedJsonObjectFieldsHaveExpectedValues) {
    // Arrange
    const std::string expected_string("1");
    const TokenStateData expected_state_data;
    const TokenConfigData expected_config_data;
    const TokenVariantMode expected_variant_mode = TokenVariantMode::NONE;
    const std::string json(POPULATED_JSON_OBJECT);

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_EQ(expected_string, class_under_test.get_id().value());
    EXPECT_EQ(expected_string, class_under_test.get_name().value());
    EXPECT_EQ(expected_state_data, class_under_test.get_state_data().value());
    EXPECT_EQ(expected_config_data, class_under_test.get_config_data().value());
    EXPECT_EQ(expected_variant_mode, class_under_test.get_variant_mode().value());
    EXPECT_TRUE(class_under_test.get_variants().has_value());
    EXPECT_FALSE(class_under_test.get_variants().value().empty());
    EXPECT_EQ(expected_string, class_under_test.get_created_at().value());
    EXPECT_EQ(expected_string, class_under_test.get_updated_at().value());
}

TEST_F(TokenTest, DeserializePopulatedVariantsArrayHaveExpectedElements) {
    // Arrange
    const std::string json(R"({"variants":[{"id":1}, {"id":1}, {"id":1}]})");
    TokenVariant expected;
    expected.deserialize(R"({"id":1})");

    // Act
    class_under_test.deserialize(json);

    // Assert
    ASSERT_TRUE(class_under_test.get_variants().has_value());
    for (const TokenVariant& actual : class_under_test.get_variants().value()) {
        EXPECT_EQ(expected, actual);
    }
}

TEST_F(TokenTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    Token lhs;
    Token rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(TokenTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    Token lhs;
    Token rhs;
    lhs.deserialize(POPULATED_JSON_OBJECT);
    rhs.deserialize(POPULATED_JSON_OBJECT);

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(TokenTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    Token lhs;
    Token rhs;
    lhs.deserialize(POPULATED_JSON_OBJECT);

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(TokenTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    Token lhs;
    Token rhs;
    rhs.deserialize(POPULATED_JSON_OBJECT);

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
