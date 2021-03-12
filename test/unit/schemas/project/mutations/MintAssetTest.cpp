#include "JsonTestSuite.hpp"
#include "enjinsdk/project/MintAsset.hpp"
#include <string>
#include <vector>

using namespace enjin::sdk::project;

class MintAssetTest : public JsonTestSuite {
public:
    MintAsset class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"assetId":"1","mints":[]})";

    static MintAsset create_default_request() {
        return MintAsset().set_asset_id("1")
                          .set_mints(std::vector<enjin::sdk::models::MintInput>());
    }
};

TEST_F(MintAssetTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EMPTY_JSON_OBJECT);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(MintAssetTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_asset_id("1")
                    .set_mints(std::vector<enjin::sdk::models::MintInput>());

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(MintAssetTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    MintAsset lhs;
    MintAsset rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(MintAssetTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    MintAsset lhs = create_default_request();
    MintAsset rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(MintAssetTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    MintAsset lhs = create_default_request();
    MintAsset rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(MintAssetTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    MintAsset lhs;
    MintAsset rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
