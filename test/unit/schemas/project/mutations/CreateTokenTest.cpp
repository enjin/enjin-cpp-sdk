#include "enjinsdk/project/CreateToken.hpp"
#include "../../../../suites/JsonTestSuite.hpp"
#include <string>

using namespace enjin::sdk::project;

class CreateTokenTest : public JsonTestSuite {
public:
    CreateToken class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"name":"1","totalSupply":"1","initialReserve":"1","supplyModel":"FIXED","meltValue":"1","meltFeeRatio":1,"transferable":"PERMANENT","transferFeeSettings":{},"nonfungible":true})";

    static CreateToken create_default_request() {
        return CreateToken().set_name("1")
                            .set_total_supply("1")
                            .set_initial_reserve("1")
                            .set_supply_model(enjin::sdk::models::TokenSupplyModel::FIXED)
                            .set_melt_value("1")
                            .set_melt_fee_ratio(1)
                            .set_transferable(enjin::sdk::models::TokenTransferable::PERMANENT)
                            .set_transfer_fee_settings(enjin::sdk::models::TokenTransferFeeSettingsInput())
                            .set_nonfungible(true);
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
                    .set_supply_model(enjin::sdk::models::TokenSupplyModel::FIXED)
                    .set_melt_value("1")
                    .set_melt_fee_ratio(1)
                    .set_transferable(enjin::sdk::models::TokenTransferable::PERMANENT)
                    .set_transfer_fee_settings(enjin::sdk::models::TokenTransferFeeSettingsInput())
                    .set_nonfungible(true);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(CreateTokenTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    CreateToken lhs;
    CreateToken rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(CreateTokenTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    CreateToken lhs = create_default_request();
    CreateToken rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(CreateTokenTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    CreateToken lhs = create_default_request();
    CreateToken rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(CreateTokenTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    CreateToken lhs;
    CreateToken rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
