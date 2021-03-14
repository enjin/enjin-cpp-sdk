#include "JsonTestSuite.hpp"
#include "enjinsdk/models/AssetStateData.hpp"

using namespace enjin::sdk::models;

class AssetStateDataTest : public JsonTestSuite {
public:
    AssetStateData class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"nonFungible":true,"blockHeight":1,"creator":"1","firstBlock":1,"reserve":"1","supplyModel":"FIXED","circulatingSupply":"1","mintableSupply":"1","totalSupply":"1"})";
};

TEST_F(AssetStateDataTest, DeserializeEmptyStringFieldsDoNotHaveValues) {
    // Arrange
    const std::string json;

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_FALSE(class_under_test.get_non_fungible().has_value());
    EXPECT_FALSE(class_under_test.get_block_height().has_value());
    EXPECT_FALSE(class_under_test.get_creator().has_value());
    EXPECT_FALSE(class_under_test.get_first_block().has_value());
    EXPECT_FALSE(class_under_test.get_reserve().has_value());
    EXPECT_FALSE(class_under_test.get_supply_model().has_value());
    EXPECT_FALSE(class_under_test.get_circulating_supply().has_value());
    EXPECT_FALSE(class_under_test.get_mintable_supply().has_value());
    EXPECT_FALSE(class_under_test.get_total_supply().has_value());
}

TEST_F(AssetStateDataTest, DeserializeEmptyJsonObjectFieldsDoNotHaveValues) {
    // Arrange
    const std::string json(EMPTY_JSON_OBJECT);

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_FALSE(class_under_test.get_non_fungible().has_value());
    EXPECT_FALSE(class_under_test.get_block_height().has_value());
    EXPECT_FALSE(class_under_test.get_creator().has_value());
    EXPECT_FALSE(class_under_test.get_first_block().has_value());
    EXPECT_FALSE(class_under_test.get_reserve().has_value());
    EXPECT_FALSE(class_under_test.get_supply_model().has_value());
    EXPECT_FALSE(class_under_test.get_circulating_supply().has_value());
    EXPECT_FALSE(class_under_test.get_mintable_supply().has_value());
    EXPECT_FALSE(class_under_test.get_total_supply().has_value());
}

TEST_F(AssetStateDataTest, DeserializePopulatedJsonObjectFieldsHaveExpectedValues) {
    // Arrange
    const bool expected_bool = true;
    const int expected_int = 1;
    const std::string expected_string("1");
    const AssetSupplyModel expected_supply_model = AssetSupplyModel::FIXED;
    const std::string json(POPULATED_JSON_OBJECT);

    // Act
    class_under_test.deserialize(json);

    // Assert
    EXPECT_EQ(expected_bool, class_under_test.get_non_fungible().value());
    EXPECT_EQ(expected_int, class_under_test.get_block_height().value());
    EXPECT_EQ(expected_string, class_under_test.get_creator().value());
    EXPECT_EQ(expected_int, class_under_test.get_first_block().value());
    EXPECT_EQ(expected_string, class_under_test.get_reserve().value());
    EXPECT_EQ(expected_supply_model, class_under_test.get_supply_model().value());
    EXPECT_EQ(expected_string, class_under_test.get_circulating_supply().value());
    EXPECT_EQ(expected_string, class_under_test.get_mintable_supply().value());
    EXPECT_EQ(expected_string, class_under_test.get_total_supply().value());
}

TEST_F(AssetStateDataTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    AssetStateData lhs;
    AssetStateData rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(AssetStateDataTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    AssetStateData lhs;
    AssetStateData rhs;
    lhs.deserialize(POPULATED_JSON_OBJECT);
    rhs.deserialize(POPULATED_JSON_OBJECT);

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(AssetStateDataTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    AssetStateData lhs;
    AssetStateData rhs;
    lhs.deserialize(POPULATED_JSON_OBJECT);

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(AssetStateDataTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    AssetStateData lhs;
    AssetStateData rhs;
    rhs.deserialize(POPULATED_JSON_OBJECT);

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
