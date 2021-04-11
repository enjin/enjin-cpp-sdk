#include "JsonTestSuite.hpp"
#include "WalletFragmentArgumentsTestSuite.hpp"
#include "enjinsdk/project/GetWallet.hpp"
#include "gtest/gtest.h"
#include <string>

using namespace enjin::sdk::project;
using namespace enjin::test::suites;

class GetWalletTest : public WalletFragmentArgumentsTestSuite<GetWallet>,
                      public JsonTestSuite,
                      public testing::Test {
public:
    GetWallet class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"userId":"1","ethAddress":"1"})";

    static GetWallet create_default_request() {
        GetWallet request = GetWallet()
                .set_user_id("1")
                .set_eth_address("1");
        set_wallet_fragment_arguments(request);
        return request;
    }
};

TEST_F(GetWalletTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EMPTY_JSON_OBJECT);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(GetWalletTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_user_id("1")
                    .set_eth_address("1");

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(GetWalletTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    GetWallet lhs;
    GetWallet rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(GetWalletTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    GetWallet lhs = create_default_request();
    GetWallet rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(GetWalletTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    GetWallet lhs = create_default_request();
    GetWallet rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(GetWalletTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    GetWallet lhs;
    GetWallet rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
