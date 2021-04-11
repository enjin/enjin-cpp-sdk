#include "gtest/gtest.h"
#include "AssetFragmentArgumentsTestSuite.hpp"
#include "JsonTestSuite.hpp"
#include "enjinsdk/shared/GetAsset.hpp"
#include <string>

using namespace enjin::sdk::shared;
using namespace enjin::test::suites;

class GetAssetTest : public AssetFragmentArgumentsTestSuite<GetAsset>,
                     public JsonTestSuite,
                     public testing::Test {
public:
    GetAsset class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"id":"1"})";

    static GetAsset create_default_request() {
        GetAsset request = GetAsset().set_id("1");
        set_asset_fragment_arguments(request);
        return request;
    }
};

TEST_F(GetAssetTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EMPTY_JSON_OBJECT);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(GetAssetTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_id("1");

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(GetAssetTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    GetAsset lhs;
    GetAsset rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(GetAssetTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    GetAsset lhs = create_default_request();
    GetAsset rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(GetAssetTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    GetAsset lhs = create_default_request();
    GetAsset rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(GetAssetTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    GetAsset lhs;
    GetAsset rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
