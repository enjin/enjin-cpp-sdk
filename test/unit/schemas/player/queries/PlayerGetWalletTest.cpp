#include "JsonTestSuite.hpp"
#include "WalletFragmentArgumentsTestSuite.hpp"
#include "enjinsdk/player/GetWallet.hpp"
#include "gtest/gtest.h"
#include <string>

using namespace enjin::sdk::player;
using namespace enjin::test::suites;

class PlayerGetWalletTest : public WalletFragmentArgumentsTestSuite<GetWallet>,
                            public JsonTestSuite,
                            public testing::Test {
public:
    GetWallet class_under_test;

    static GetWallet create_default_request() {
        GetWallet request;
        set_wallet_fragment_arguments(request);
        return request;
    }
};

TEST_F(PlayerGetWalletTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EMPTY_JSON_OBJECT);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(PlayerGetWalletTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    GetWallet lhs;
    GetWallet rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(PlayerGetWalletTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    GetWallet lhs = create_default_request();
    GetWallet rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(PlayerGetWalletTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    GetWallet lhs = create_default_request();
    GetWallet rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(PlayerGetWalletTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    GetWallet lhs;
    GetWallet rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
