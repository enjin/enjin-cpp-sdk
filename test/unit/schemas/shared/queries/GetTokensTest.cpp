#include "enjinsdk/shared/GetAssets.hpp"
#include "../../../../suites/JsonTestSuite.hpp"
#include <string>

using namespace enjin::sdk::shared;

class GetTokensTest : public JsonTestSuite {
public:
    GetAssets class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"filter":{},"sort":{}})";

    static GetAssets create_default_request() {
        return GetAssets().set_filter(enjin::sdk::models::AssetFilter())
                          .set_sort(enjin::sdk::models::AssetSort());
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
    class_under_test.set_filter(enjin::sdk::models::AssetFilter())
                    .set_sort(enjin::sdk::models::AssetSort());

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(GetTokensTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    GetAssets lhs;
    GetAssets rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(GetTokensTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    GetAssets lhs = create_default_request();
    GetAssets rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(GetTokensTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    GetAssets lhs = create_default_request();
    GetAssets rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(GetTokensTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    GetAssets lhs;
    GetAssets rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
