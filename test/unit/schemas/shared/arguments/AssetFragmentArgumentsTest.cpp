#include "enjinsdk/internal/AssetFragmentArguments.hpp"
#include "../../../../suites/JsonTestSuite.hpp"

using namespace enjin::sdk::shared;

class AssetFragmentArgumentsTest : public JsonTestSuite {
public:
    AssetFragmentArguments class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"assetIdFormat":"hex64","withStateData":true,"withConfigData":true,"withAssetBlocks":true,"withCreator":true,"withMeltDetails":true,"withMetadataURI":true,"withSupplyDetails":true,"withTransferSettings":true,"withAssetVariantMode":true,"withAssetVariants":true,"withVariantMetadata":true})";

    static AssetFragmentArguments create_default_arguments() {
        AssetFragmentArguments arguments;
        arguments.set_asset_id_format(enjin::sdk::models::AssetIdFormat::HEX64);
        arguments.set_with_state_data();
        arguments.set_with_config_data();
        arguments.set_with_asset_blocks();
        arguments.set_with_creator();
        arguments.set_with_melt_details();
        arguments.set_with_metadata_uri();
        arguments.set_with_supply_details();
        arguments.set_with_transfer_settings();
        arguments.set_with_asset_variant_mode();
        arguments.set_with_asset_variants();
        arguments.set_with_variant_metadata();
        return arguments;
    }
};

TEST_F(AssetFragmentArgumentsTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EMPTY_JSON_OBJECT);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(AssetFragmentArgumentsTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_asset_id_format(enjin::sdk::models::AssetIdFormat::HEX64);
    class_under_test.set_with_state_data();
    class_under_test.set_with_config_data();
    class_under_test.set_with_asset_blocks();
    class_under_test.set_with_creator();
    class_under_test.set_with_melt_details();
    class_under_test.set_with_metadata_uri();
    class_under_test.set_with_supply_details();
    class_under_test.set_with_transfer_settings();
    class_under_test.set_with_asset_variant_mode();
    class_under_test.set_with_asset_variants();
    class_under_test.set_with_variant_metadata();

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(AssetFragmentArgumentsTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    AssetFragmentArguments lhs;
    AssetFragmentArguments rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(AssetFragmentArgumentsTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    AssetFragmentArguments lhs = create_default_arguments();
    AssetFragmentArguments rhs = create_default_arguments();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(AssetFragmentArgumentsTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    AssetFragmentArguments lhs = create_default_arguments();
    AssetFragmentArguments rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(AssetFragmentArgumentsTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    AssetFragmentArguments lhs;
    AssetFragmentArguments rhs = create_default_arguments();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
