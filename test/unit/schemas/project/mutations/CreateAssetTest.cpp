#include "JsonTestSuite.hpp"
#include "TransactionRequestArgumentsTestSuite.hpp"
#include "enjinsdk/project/CreateAsset.hpp"
#include "gtest/gtest.h"
#include <string>

using namespace enjin::sdk::models;
using namespace enjin::sdk::project;
using namespace enjin::test::suites;

class CreateAssetTest : public TransactionRequestArgumentsTestSuite<CreateAsset>,
                        public JsonTestSuite,
                        public testing::Test {
public:
    CreateAsset class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"name":"1","totalSupply":"1","initialReserve":"1","supplyModel":"FIXED","meltValue":"1","meltFeeRatio":1,"transferable":"PERMANENT","transferFeeSettings":{},"nonFungible":true})";

    static CreateAsset create_default_request() {
        CreateAsset request = CreateAsset()
                .set_name("1")
                .set_total_supply("1")
                .set_initial_reserve("1")
                .set_supply_model(AssetSupplyModel::FIXED)
                .set_melt_value("1")
                .set_melt_fee_ratio(1)
                .set_transferable(AssetTransferable::PERMANENT)
                .set_transfer_fee_settings(AssetTransferFeeSettingsInput())
                .set_non_fungible(true);
        set_transaction_request_arguments(request);
        return request;
    }
};

TEST_F(CreateAssetTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EMPTY_JSON_OBJECT);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(CreateAssetTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_name("1")
                    .set_total_supply("1")
                    .set_initial_reserve("1")
                    .set_supply_model(AssetSupplyModel::FIXED)
                    .set_melt_value("1")
                    .set_melt_fee_ratio(1)
                    .set_transferable(AssetTransferable::PERMANENT)
                    .set_transfer_fee_settings(AssetTransferFeeSettingsInput())
                    .set_non_fungible(true);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(CreateAssetTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    CreateAsset lhs;
    CreateAsset rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(CreateAssetTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    CreateAsset lhs = create_default_request();
    CreateAsset rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(CreateAssetTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    CreateAsset lhs = create_default_request();
    CreateAsset rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(CreateAssetTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    CreateAsset lhs;
    CreateAsset rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
