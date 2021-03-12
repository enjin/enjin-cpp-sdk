#include "JsonTestSuite.hpp"
#include "enjinsdk/shared/SendAsset.hpp"
#include <string>

using namespace enjin::sdk::shared;

class SendAssetTest : public JsonTestSuite {
public:
    SendAsset class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"recipientAddress":"1","assetId":"1","assetIndex":"1","value":"1","data":"1"})";

    static SendAsset create_default_request() {
        return SendAsset().set_recipient_address("1")
                          .set_asset_id("1")
                          .set_asset_index("1")
                          .set_value("1")
                          .set_data("1");
    }
};

TEST_F(SendAssetTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EMPTY_JSON_OBJECT);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(SendAssetTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_recipient_address("1")
                    .set_asset_id("1")
                    .set_asset_index("1")
                    .set_value("1")
                    .set_data("1");

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(SendAssetTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    SendAsset lhs;
    SendAsset rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(SendAssetTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    SendAsset lhs = create_default_request();
    SendAsset rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(SendAssetTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    SendAsset lhs = create_default_request();
    SendAsset rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(SendAssetTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    SendAsset lhs;
    SendAsset rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
