#include "../../../models/ModelsTestSuite.hpp"
#include "enjinsdk/internal/TokenFragmentArguments.hpp"

using namespace enjin::sdk::shared;

class TokenFragmentArgumentsTest : public ModelsTestSuite {
public:
    TokenFragmentArguments class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"tokenIdFormat":"hex64","withStateData":true,"withConfigData":true,"withTokenBlocks":true,"withCreator":true,"withMeltDetails":true,"withMetadataUri":true,"withSupplyDetails":true,"withTransferSettings":true,"withTokenVariantMode":true,"withTokenVariants":true,"withVariantMetadata":true})";

    static TokenFragmentArguments create_default_arguments() {
        TokenFragmentArguments arguments;
        arguments.set_token_id_format(enjin::sdk::models::TokenIdFormat::HEX64);
        arguments.set_with_state_data();
        arguments.set_with_config_data();
        arguments.set_with_token_blocks();
        arguments.set_with_creator();
        arguments.set_with_melt_details();
        arguments.set_with_metadata_uri();
        arguments.set_with_supply_details();
        arguments.set_with_transfer_settings();
        arguments.set_with_token_variant_mode();
        arguments.set_with_token_variants();
        arguments.set_with_variant_metadata();
        return arguments;
    }
};

TEST_F(TokenFragmentArgumentsTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EMPTY_JSON_OBJECT);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(TokenFragmentArgumentsTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_token_id_format(enjin::sdk::models::TokenIdFormat::HEX64);
    class_under_test.set_with_state_data();
    class_under_test.set_with_config_data();
    class_under_test.set_with_token_blocks();
    class_under_test.set_with_creator();
    class_under_test.set_with_melt_details();
    class_under_test.set_with_metadata_uri();
    class_under_test.set_with_supply_details();
    class_under_test.set_with_transfer_settings();
    class_under_test.set_with_token_variant_mode();
    class_under_test.set_with_token_variants();
    class_under_test.set_with_variant_metadata();

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(TokenFragmentArgumentsTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    TokenFragmentArguments lhs;
    TokenFragmentArguments rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(TokenFragmentArgumentsTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    TokenFragmentArguments lhs = create_default_arguments();
    TokenFragmentArguments rhs = create_default_arguments();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(TokenFragmentArgumentsTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    TokenFragmentArguments lhs = create_default_arguments();
    TokenFragmentArguments rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(TokenFragmentArgumentsTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    TokenFragmentArguments lhs;
    TokenFragmentArguments rhs = create_default_arguments();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
