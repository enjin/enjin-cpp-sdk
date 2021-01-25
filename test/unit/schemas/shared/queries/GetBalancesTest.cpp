#include "../../../models/ModelsTestSuite.hpp"
#include "enjinsdk/shared/GetBalances.hpp"

using namespace enjin::sdk::shared;

class GetBalancesTest : public ModelsTestSuite {
public:
    GetBalances class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"filter":{}})";

    static GetBalances create_default_request() {
        return GetBalances().set_filter(enjin::sdk::models::BalanceFilter());
    }
};

TEST_F(GetBalancesTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EMPTY_JSON_OBJECT);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(GetBalancesTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_filter(enjin::sdk::models::BalanceFilter());

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(GetBalancesTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    GetBalances lhs;
    GetBalances rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(GetBalancesTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    GetBalances lhs = create_default_request();
    GetBalances rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(GetBalancesTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    GetBalances lhs = create_default_request();
    GetBalances rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(GetBalancesTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    GetBalances lhs;
    GetBalances rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
