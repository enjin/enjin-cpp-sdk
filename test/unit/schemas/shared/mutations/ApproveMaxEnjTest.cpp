#include "JsonTestSuite.hpp"
#include "TransactionRequestArgumentsTestSuite.hpp"
#include "enjinsdk/shared/ApproveMaxEnj.hpp"
#include "gtest/gtest.h"
#include <string>

using namespace enjin::sdk::shared;
using namespace enjin::test::suites;

class ApproveMaxEnjTest : public TransactionRequestArgumentsTestSuite<ApproveMaxEnj>,
                          public JsonTestSuite,
                          public testing::Test {
public:
    static ApproveMaxEnj create_default_request() {
        ApproveMaxEnj request;
        set_transaction_request_arguments(request);
        return request;
    }
};

TEST_F(ApproveMaxEnjTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    ApproveMaxEnj lhs;
    ApproveMaxEnj rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(ApproveMaxEnjTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    ApproveMaxEnj lhs = create_default_request();
    ApproveMaxEnj rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(ApproveMaxEnjTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    ApproveMaxEnj lhs = create_default_request();
    ApproveMaxEnj rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(ApproveMaxEnjTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    ApproveMaxEnj lhs;
    ApproveMaxEnj rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
