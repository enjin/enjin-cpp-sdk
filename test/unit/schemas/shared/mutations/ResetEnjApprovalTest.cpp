#include "JsonTestSuite.hpp"
#include "TransactionRequestArgumentsTestSuite.hpp"
#include "enjinsdk/shared/ResetEnjApproval.hpp"
#include "gtest/gtest.h"
#include <string>

using namespace enjin::sdk::shared;
using namespace enjin::test::suites;

class ResetEnjApprovalTest : public TransactionRequestArgumentsTestSuite<ResetEnjApproval>,
                             public JsonTestSuite,
                             public testing::Test {
public:
    static ResetEnjApproval create_default_request() {
        ResetEnjApproval request;
        set_transaction_request_arguments(request);
        return request;
    }
};

TEST_F(ResetEnjApprovalTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    ResetEnjApproval lhs;
    ResetEnjApproval rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(ResetEnjApprovalTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    ResetEnjApproval lhs = create_default_request();
    ResetEnjApproval rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(ResetEnjApprovalTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    ResetEnjApproval lhs = create_default_request();
    ResetEnjApproval rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(ResetEnjApprovalTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    ResetEnjApproval lhs;
    ResetEnjApproval rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
