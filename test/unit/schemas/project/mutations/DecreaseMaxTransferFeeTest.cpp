#include "enjinsdk/project/DecreaseMaxTransferFee.hpp"
#include "../../../../suites/JsonTestSuite.hpp"
#include <string>

using namespace enjin::sdk::project;

class DecreaseMaxTransferFeeTest : public JsonTestSuite {
public:
    DecreaseMaxTransferFee class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"tokenId":"1","tokenIndex":"1","maxTransferFee":1})";

    static DecreaseMaxTransferFee create_default_request() {
        return DecreaseMaxTransferFee().set_token_id("1")
                                       .set_token_index("1")
                                       .set_max_transfer_fee(1);
    }
};

TEST_F(DecreaseMaxTransferFeeTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EMPTY_JSON_OBJECT);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(DecreaseMaxTransferFeeTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_token_id("1")
                    .set_token_index("1")
                    .set_max_transfer_fee(1);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(DecreaseMaxTransferFeeTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    DecreaseMaxTransferFee lhs;
    DecreaseMaxTransferFee rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(DecreaseMaxTransferFeeTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    DecreaseMaxTransferFee lhs = create_default_request();
    DecreaseMaxTransferFee rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(DecreaseMaxTransferFeeTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    DecreaseMaxTransferFee lhs = create_default_request();
    DecreaseMaxTransferFee rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(DecreaseMaxTransferFeeTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    DecreaseMaxTransferFee lhs;
    DecreaseMaxTransferFee rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
