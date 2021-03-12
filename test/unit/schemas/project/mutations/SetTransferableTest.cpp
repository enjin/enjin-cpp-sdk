#include "JsonTestSuite.hpp"
#include "enjinsdk/project/SetTransferable.hpp"
#include <string>

using namespace enjin::sdk::project;

class SetTransferableTest : public JsonTestSuite {
public:
    SetTransferable class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"assetId":"1","assetIndex":"1","transferable":"PERMANENT"})";

    static SetTransferable create_default_request() {
        return SetTransferable().set_asset_id("1")
                                .set_asset_index("1")
                                .set_transferable(enjin::sdk::models::AssetTransferable::PERMANENT);
    }
};

TEST_F(SetTransferableTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EMPTY_JSON_OBJECT);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(SetTransferableTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_asset_id("1")
                    .set_asset_index("1")
                    .set_transferable(enjin::sdk::models::AssetTransferable::PERMANENT);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(SetTransferableTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    SetTransferable lhs;
    SetTransferable rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(SetTransferableTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    SetTransferable lhs = create_default_request();
    SetTransferable rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(SetTransferableTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    SetTransferable lhs = create_default_request();
    SetTransferable rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(SetTransferableTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    SetTransferable lhs;
    SetTransferable rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
