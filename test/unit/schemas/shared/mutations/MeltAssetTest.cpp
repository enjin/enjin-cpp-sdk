#include "gtest/gtest.h"
#include "JsonTestSuite.hpp"
#include "enjinsdk/shared/MeltAsset.hpp"
#include <string>
#include <vector>

using namespace enjin::sdk::shared;
using namespace enjin::test::suites;

class MeltAssetTest : public JsonTestSuite,
                      public testing::Test {
public:
    MeltAsset class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"melts":[]})";

    static MeltAsset create_default_request() {
        return MeltAsset().set_melts(std::vector<enjin::sdk::models::Melt>());
    }
};

TEST_F(MeltAssetTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EMPTY_JSON_OBJECT);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(MeltAssetTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_melts(std::vector<enjin::sdk::models::Melt>());

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(MeltAssetTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    MeltAsset lhs;
    MeltAsset rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(MeltAssetTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    MeltAsset lhs = create_default_request();
    MeltAsset rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(MeltAssetTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    MeltAsset lhs = create_default_request();
    MeltAsset rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(MeltAssetTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    MeltAsset lhs;
    MeltAsset rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
