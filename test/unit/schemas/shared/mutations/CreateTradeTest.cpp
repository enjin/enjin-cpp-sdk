#include "gtest/gtest.h"
#include "JsonTestSuite.hpp"
#include "enjinsdk/shared/CreateTrade.hpp"
#include <string>
#include <vector>

using namespace enjin::sdk::shared;
using namespace enjin::test::suites;

class CreateTradeTest : public JsonTestSuite,
                        public testing::Test {
public:
    CreateTrade class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"askingAssets":[],"offeringAssets":[],"recipientAddress":"1"})";

    static CreateTrade create_default_request() {
        return CreateTrade().set_asking_assets(std::vector<enjin::sdk::models::Trade>())
                            .set_offering_assets(std::vector<enjin::sdk::models::Trade>())
                            .set_recipient_address("1");
    }
};

TEST_F(CreateTradeTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EMPTY_JSON_OBJECT);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(CreateTradeTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_asking_assets(std::vector<enjin::sdk::models::Trade>())
                    .set_offering_assets(std::vector<enjin::sdk::models::Trade>())
                    .set_recipient_address("1");

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(CreateTradeTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    CreateTrade lhs;
    CreateTrade rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(CreateTradeTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    CreateTrade lhs = create_default_request();
    CreateTrade rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(CreateTradeTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    CreateTrade lhs = create_default_request();
    CreateTrade rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(CreateTradeTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    CreateTrade lhs;
    CreateTrade rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
