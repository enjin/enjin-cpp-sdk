#include "../../../models/ModelsTestSuite.hpp"
#include "enjinsdk/shared/CompleteTrade.hpp"
#include <string>

using namespace enjin::sdk::shared;

class CompleteTradeTest : public ModelsTestSuite {
public:
    CompleteTrade class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"tradeId":"1"})";

    static CompleteTrade create_default_request() {
        return CompleteTrade().set_trade_id("1");
    }
};

TEST_F(CompleteTradeTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EMPTY_JSON_OBJECT);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(CompleteTradeTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_trade_id("1");

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(CompleteTradeTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    CompleteTrade lhs;
    CompleteTrade rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(CompleteTradeTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    CompleteTrade lhs = create_default_request();
    CompleteTrade rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(CompleteTradeTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    CompleteTrade lhs = create_default_request();
    CompleteTrade rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(CompleteTradeTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    CompleteTrade lhs;
    CompleteTrade rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
