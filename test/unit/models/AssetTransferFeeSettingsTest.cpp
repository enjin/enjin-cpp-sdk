#include "JsonTestSuite.hpp"
#include "enjinsdk/models/AssetTransferFeeSettings.hpp"

using namespace enjin::sdk::models;

class AssetTransferFeeSettingsTest : public JsonTestSuite {
public:
    AssetTransferFeeSettings class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"type":"NONE","assetId":"1","value":"1"})";
};

TEST_F(AssetTransferFeeSettingsTest, DeserializeEmptyStringFieldsDoNotHaveValues) {
    // Arrange
    const std::string json;

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_FALSE(class_under_test.get_type().has_value());
    EXPECT_FALSE(class_under_test.get_asset_id().has_value());
    EXPECT_FALSE(class_under_test.get_value().has_value());
}

TEST_F(AssetTransferFeeSettingsTest, DeserializeEmptyJsonObjectFieldsDoNotHaveValues) {
    // Arrange
    const std::string json(EMPTY_JSON_OBJECT);

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_FALSE(class_under_test.get_type().has_value());
    EXPECT_FALSE(class_under_test.get_asset_id().has_value());
    EXPECT_FALSE(class_under_test.get_value().has_value());
}

TEST_F(AssetTransferFeeSettingsTest, DeserializePopulatedJsonObjectFieldsHaveExpectedValues) {
    // Arrange
    const std::string expected_string("1");
    const AssetTransferFeeType expected_type = AssetTransferFeeType::NONE;
    const std::string json(POPULATED_JSON_OBJECT);

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_EQ(expected_type, class_under_test.get_type().value());
    EXPECT_EQ(expected_string, class_under_test.get_asset_id().value());
    EXPECT_EQ(expected_string, class_under_test.get_value().value());
}

TEST_F(AssetTransferFeeSettingsTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    AssetTransferFeeSettings lhs;
    AssetTransferFeeSettings rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(AssetTransferFeeSettingsTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    AssetTransferFeeSettings lhs;
    AssetTransferFeeSettings rhs;
    lhs.deserialize(POPULATED_JSON_OBJECT);
    rhs.deserialize(POPULATED_JSON_OBJECT);

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(AssetTransferFeeSettingsTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    AssetTransferFeeSettings lhs;
    AssetTransferFeeSettings rhs;
    lhs.deserialize(POPULATED_JSON_OBJECT);

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(AssetTransferFeeSettingsTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    AssetTransferFeeSettings lhs;
    AssetTransferFeeSettings rhs;
    rhs.deserialize(POPULATED_JSON_OBJECT);

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
