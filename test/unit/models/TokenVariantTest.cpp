#include "enjinsdk/models/TokenVariant.hpp"
#include "../../suites/JsonTestSuite.hpp"

using namespace enjin::sdk::models;

class TokenVariantTest : public JsonTestSuite {
public:
    TokenVariant class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"id":1,"tokenId":"1","variantMetadata":"{}","usageCount":1,"createdAt":"1","updatedAt":"1"})";
};

TEST_F(TokenVariantTest, DeserializeEmptyStringFieldsDoNotHaveValues) {
    // Arrange
    const std::string json;

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_FALSE(class_under_test.get_id().has_value());
    EXPECT_FALSE(class_under_test.get_token_id().has_value());
    EXPECT_FALSE(class_under_test.get_variant_metadata().has_value());
    EXPECT_FALSE(class_under_test.get_usage_count().has_value());
    EXPECT_FALSE(class_under_test.get_created_at().has_value());
    EXPECT_FALSE(class_under_test.get_updated_at().has_value());
}

TEST_F(TokenVariantTest, DeserializeEmptyJsonObjectFieldsDoNotHaveValues) {
    // Arrange
    const std::string json(EMPTY_JSON_OBJECT);

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_FALSE(class_under_test.get_id().has_value());
    EXPECT_FALSE(class_under_test.get_token_id().has_value());
    EXPECT_FALSE(class_under_test.get_variant_metadata().has_value());
    EXPECT_FALSE(class_under_test.get_usage_count().has_value());
    EXPECT_FALSE(class_under_test.get_created_at().has_value());
    EXPECT_FALSE(class_under_test.get_updated_at().has_value());
}

TEST_F(TokenVariantTest, DeserializePopulatedJsonObjectFieldsHaveExpectedValues) {
    // Arrange
    const int expected_id = 1;
    const std::string expected_token_id("1");
    const std::string expected_variant_metadata("{}");
    const int expected_usage_count = 1;
    const std::string expected_created_at("1");
    const std::string expected_updated_at("1");
    const std::string json(POPULATED_JSON_OBJECT);

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_EQ(expected_id, class_under_test.get_id().value());
    EXPECT_EQ(expected_token_id, class_under_test.get_token_id().value());
    EXPECT_EQ(expected_variant_metadata, class_under_test.get_variant_metadata().value());
    EXPECT_EQ(expected_usage_count, class_under_test.get_usage_count().value());
    EXPECT_EQ(expected_created_at, class_under_test.get_created_at().value());
    EXPECT_EQ(expected_updated_at, class_under_test.get_updated_at().value());
}

TEST_F(TokenVariantTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    TokenVariant lhs;
    TokenVariant rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(TokenVariantTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    TokenVariant lhs;
    TokenVariant rhs;
    lhs.deserialize(POPULATED_JSON_OBJECT);
    rhs.deserialize(POPULATED_JSON_OBJECT);

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(TokenVariantTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    TokenVariant lhs;
    TokenVariant rhs;
    lhs.deserialize(POPULATED_JSON_OBJECT);

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(TokenVariantTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    TokenVariant lhs;
    TokenVariant rhs;
    rhs.deserialize(POPULATED_JSON_OBJECT);

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
