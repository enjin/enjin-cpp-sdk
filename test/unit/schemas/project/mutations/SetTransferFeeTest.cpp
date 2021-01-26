#include "../../../models/ModelsTestSuite.hpp"
#include "enjinsdk/project/SetTransferFee.hpp"
#include <string>

using namespace enjin::sdk::project;

class SetTransferFeeTest : public ModelsTestSuite {
public:
    SetTransferFee class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"tokenId":"1","tokenIndex":"1","transferFee":"1"})";

    static SetTransferFee create_default_request() {
        return SetTransferFee().set_token_id("1")
                               .set_token_index("1")
                               .set_transfer_fee("1");
    }
};

TEST_F(SetTransferFeeTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EMPTY_JSON_OBJECT);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(SetTransferFeeTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_token_id("1")
                    .set_token_index("1")
                    .set_transfer_fee("1");

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(SetTransferFeeTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    SetTransferFee lhs;
    SetTransferFee rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(SetTransferFeeTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    SetTransferFee lhs = create_default_request();
    SetTransferFee rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(SetTransferFeeTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    SetTransferFee lhs = create_default_request();
    SetTransferFee rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(SetTransferFeeTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    SetTransferFee lhs;
    SetTransferFee rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
