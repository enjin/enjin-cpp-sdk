#include "enjinsdk/models/BalanceFilter.hpp"
#include "../../suites/JsonTestSuite.hpp"
#include <string>
#include <vector>

using namespace enjin::sdk::models;

class BalanceFilterTest : public JsonTestSuite {
public:
    BalanceFilter class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"and":[],"or":[],"tokenId":"1","tokenId_in":[],"wallet":"1","wallet_in":[],"value":1,"value_gt":1,"value_gte":1,"value_lt":1,"value_lte":1})";

    static BalanceFilter create_default_filter() {
        return BalanceFilter().set_and(std::vector<BalanceFilter>())
                              .set_or(std::vector<BalanceFilter>())
                              .set_token_id("1")
                              .set_token_id_in(std::vector<std::string>())
                              .set_wallet("1")
                              .set_wallet_in(std::vector<std::string>())
                              .set_value(1)
                              .set_value_greater_than(1)
                              .set_value_greater_than_or_equal(1)
                              .set_value_less_than(1)
                              .set_value_less_than_or_equal(1);
    }
};

TEST_F(BalanceFilterTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EMPTY_JSON_OBJECT);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(BalanceFilterTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_and(std::vector<BalanceFilter>())
                    .set_or(std::vector<BalanceFilter>())
                    .set_token_id("1")
                    .set_token_id_in(std::vector<std::string>())
                    .set_wallet("1")
                    .set_wallet_in(std::vector<std::string>())
                    .set_value(1)
                    .set_value_greater_than(1)
                    .set_value_greater_than_or_equal(1)
                    .set_value_less_than(1)
                    .set_value_less_than_or_equal(1);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(BalanceFilterTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    BalanceFilter lhs;
    BalanceFilter rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(BalanceFilterTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    BalanceFilter lhs = create_default_filter();
    BalanceFilter rhs = create_default_filter();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(BalanceFilterTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    BalanceFilter lhs = create_default_filter();
    BalanceFilter rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(BalanceFilterTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    BalanceFilter lhs;
    BalanceFilter rhs = create_default_filter();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
