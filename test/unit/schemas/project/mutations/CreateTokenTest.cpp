#include "enjinsdk/project/CreateAsset.hpp"
#include "../../../../suites/JsonTestSuite.hpp"
#include <string>

using namespace enjin::sdk::project;

class CreateTokenTest : public JsonTestSuite {
public:
    CreateAsset class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"name":"1","totalSupply":"1","initialReserve":"1","supplyModel":"FIXED","meltValue":"1","meltFeeRatio":1,"transferable":"PERMANENT","transferFeeSettings":{},"nonFungible":true})";

    static CreateAsset create_default_request() {
        return CreateAsset().set_name("1")
                            .set_total_supply("1")
                            .set_initial_reserve("1")
                            .set_supply_model(enjin::sdk::models::AssetSupplyModel::FIXED)
                            .set_melt_value("1")
                            .set_melt_fee_ratio(1)
                            .set_transferable(enjin::sdk::models::AssetTransferable::PERMANENT)
                            .set_transfer_fee_settings(enjin::sdk::models::AssetTransferFeeSettingsInput())
                            .set_non_fungible(true);
    }
};

TEST_F(CreateTokenTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EMPTY_JSON_OBJECT);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(CreateTokenTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_name("1")
                    .set_total_supply("1")
                    .set_initial_reserve("1")
                    .set_supply_model(enjin::sdk::models::AssetSupplyModel::FIXED)
                    .set_melt_value("1")
                    .set_melt_fee_ratio(1)
                    .set_transferable(enjin::sdk::models::AssetTransferable::PERMANENT)
                    .set_transfer_fee_settings(enjin::sdk::models::AssetTransferFeeSettingsInput())
                    .set_non_fungible(true);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(CreateTokenTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    CreateAsset lhs;
    CreateAsset rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(CreateTokenTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    CreateAsset lhs = create_default_request();
    CreateAsset rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(CreateTokenTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    CreateAsset lhs = create_default_request();
    CreateAsset rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(CreateTokenTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    CreateAsset lhs;
    CreateAsset rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
