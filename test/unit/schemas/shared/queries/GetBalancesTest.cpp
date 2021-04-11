#include "gtest/gtest.h"
#include "BalanceFragmentArgumentsTestSuite.hpp"
#include "JsonTestSuite.hpp"
#include "PaginationArgumentsTestSuite.hpp"
#include "enjinsdk/shared/GetBalances.hpp"
#include <string>

using namespace enjin::sdk::models;
using namespace enjin::sdk::shared;
using namespace enjin::test::suites;

class GetBalancesTest : public BalanceFragmentArgumentsTestSuite<GetBalances>,
                        public PaginationArgumentsTestSuite<GetBalances>,
                        public JsonTestSuite,
                        public testing::Test {
public:
    GetBalances class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"filter":{}})";

    static GetBalances create_default_request() {
        GetBalances request = GetBalances()
                .set_filter(BalanceFilter());
        set_balance_fragment_arguments(request);
        set_pagination_arguments(request);
        return request;
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
    class_under_test.set_filter(BalanceFilter());

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
