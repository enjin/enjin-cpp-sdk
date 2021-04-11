#include "gtest/gtest.h"
#include "AssetFragmentArgumentsTestSuite.hpp"
#include "JsonTestSuite.hpp"
#include "PaginationArgumentsTestSuite.hpp"
#include "enjinsdk/shared/GetAssets.hpp"
#include <string>

using namespace enjin::sdk::models;
using namespace enjin::sdk::shared;
using namespace enjin::test::suites;

class GetAssetsTest : public AssetFragmentArgumentsTestSuite<GetAssets>,
                      public PaginationArgumentsTestSuite<GetAssets>,
                      public JsonTestSuite,
                      public testing::Test {
public:
    GetAssets class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"filter":{},"sort":{}})";

    static GetAssets create_default_request() {
        GetAssets request = GetAssets()
                .set_filter(AssetFilter())
                .set_sort(AssetSort());
        set_asset_fragment_arguments(request);
        set_pagination_arguments(request);
        return request;
    }
};

TEST_F(GetAssetsTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EMPTY_JSON_OBJECT);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(GetAssetsTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_filter(AssetFilter())
                    .set_sort(AssetSort());

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(GetAssetsTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    GetAssets lhs;
    GetAssets rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(GetAssetsTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    GetAssets lhs = create_default_request();
    GetAssets rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(GetAssetsTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    GetAssets lhs = create_default_request();
    GetAssets rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(GetAssetsTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    GetAssets lhs;
    GetAssets rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
