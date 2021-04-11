#include "JsonTestSuite.hpp"
#include "PaginationArgumentsTestSuite.hpp"
#include "WalletFragmentArgumentsTestSuite.hpp"
#include "enjinsdk/project/GetWallets.hpp"
#include "gtest/gtest.h"
#include <string>
#include <vector>

using namespace enjin::sdk::project;
using namespace enjin::test::suites;

class GetWalletsTest : public WalletFragmentArgumentsTestSuite<GetWallets>,
                       public PaginationArgumentsTestSuite<GetWallets>,
                       public JsonTestSuite,
                       public testing::Test {
public:
    GetWallets class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"userIds":[],"ethAddresses":[]})";

    static GetWallets create_default_request() {
        GetWallets request = GetWallets()
                .set_user_ids(std::vector<std::string>())
                .set_eth_addresses(std::vector<std::string>());
        set_wallet_fragment_arguments(request);
        set_pagination_arguments(request);
        return request;
    }
};

TEST_F(GetWalletsTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EMPTY_JSON_OBJECT);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(GetWalletsTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_user_ids(std::vector<std::string>())
                    .set_eth_addresses(std::vector<std::string>());

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(GetWalletsTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    GetWallets lhs;
    GetWallets rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(GetWalletsTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    GetWallets lhs = create_default_request();
    GetWallets rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(GetWalletsTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    GetWallets lhs = create_default_request();
    GetWallets rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(GetWalletsTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    GetWallets lhs;
    GetWallets rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
