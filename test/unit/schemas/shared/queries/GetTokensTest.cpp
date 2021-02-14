#include "enjinsdk/shared/GetTokens.hpp"
#include "../../../../suites/JsonTestSuite.hpp"
#include <string>

using namespace enjin::sdk::shared;

class GetTokensTest : public JsonTestSuite {
public:
    GetTokens class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"filter":{},"sort":{}})";

    static GetTokens create_default_request() {
        return GetTokens().set_filter(enjin::sdk::models::TokenFilter())
                          .set_sort(enjin::sdk::models::TokenSort());
    }
};

TEST_F(GetTokensTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EMPTY_JSON_OBJECT);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(GetTokensTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_filter(enjin::sdk::models::TokenFilter())
                    .set_sort(enjin::sdk::models::TokenSort());

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(GetTokensTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    GetTokens lhs;
    GetTokens rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(GetTokensTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    GetTokens lhs = create_default_request();
    GetTokens rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(GetTokensTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    GetTokens lhs = create_default_request();
    GetTokens rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(GetTokensTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    GetTokens lhs;
    GetTokens rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
