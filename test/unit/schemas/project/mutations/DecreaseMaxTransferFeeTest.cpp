#include "JsonTestSuite.hpp"
#include "TransactionRequestArgumentsTestSuite.hpp"
#include "enjinsdk/project/DecreaseMaxTransferFee.hpp"
#include "gtest/gtest.h"
#include <string>

using namespace enjin::sdk::project;
using namespace enjin::test::suites;

class DecreaseMaxTransferFeeTest : public TransactionRequestArgumentsTestSuite<DecreaseMaxTransferFee>,
                                   public JsonTestSuite,
                                   public testing::Test {
public:
    DecreaseMaxTransferFee class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"assetId":"1","assetIndex":"1","maxTransferFee":1})";

    static DecreaseMaxTransferFee create_default_request() {
        DecreaseMaxTransferFee request = DecreaseMaxTransferFee()
                .set_asset_id("1")
                .set_asset_index("1")
                .set_max_transfer_fee(1);
        set_transaction_request_arguments(request);
        return request;
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
    class_under_test.set_asset_id("1")
                    .set_asset_index("1")
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
