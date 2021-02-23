#include "enjinsdk/models/Trade.hpp"
#include "../../suites/JsonTestSuite.hpp"
#include <string>

using namespace enjin::sdk::models;

class TradeTest : public JsonTestSuite {
public:
    Trade class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"assetId":"1","assetIndex":"1","value":"1"})";

    static Trade create_default_trade() {
        return Trade().set_asset_id("1")
                      .set_asset_index("1")
                      .set_value("1");
    }
};

TEST_F(TradeTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EMPTY_JSON_OBJECT);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(TradeTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_asset_id("1")
                    .set_asset_index("1")
                    .set_value("1");

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(TradeTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    Trade lhs;
    Trade rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(TradeTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    Trade lhs = create_default_trade();
    Trade rhs = create_default_trade();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(TradeTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    Trade lhs = create_default_trade();
    Trade rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(TradeTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    Trade lhs;
    Trade rhs = create_default_trade();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
