#include "JsonTestSuite.hpp"
#include "enjinsdk/project/SetMeltFee.hpp"
#include <string>

using namespace enjin::sdk::project;

class SetMeltFeeTest : public JsonTestSuite {
public:
    SetMeltFee class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"assetId":"1","assetIndex":"1","meltFee":1})";

    static SetMeltFee create_default_request() {
        return SetMeltFee().set_asset_id("1")
                           .set_asset_index("1")
                           .set_melt_fee(1);
    }
};

TEST_F(SetMeltFeeTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EMPTY_JSON_OBJECT);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(SetMeltFeeTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_asset_id("1")
                    .set_asset_index("1")
                    .set_melt_fee(1);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(SetMeltFeeTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    SetMeltFee lhs;
    SetMeltFee rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(SetMeltFeeTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    SetMeltFee lhs = create_default_request();
    SetMeltFee rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(SetMeltFeeTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    SetMeltFee lhs = create_default_request();
    SetMeltFee rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(SetMeltFeeTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    SetMeltFee lhs;
    SetMeltFee rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
