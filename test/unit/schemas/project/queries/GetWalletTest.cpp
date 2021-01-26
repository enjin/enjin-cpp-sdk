#include "../../../models/ModelsTestSuite.hpp"
#include "enjinsdk/project/GetWallet.hpp"
#include <string>

using namespace enjin::sdk::project;

class GetWalletTest : public ModelsTestSuite {
public:
    GetWallet class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"userId":"1","ethAddress":"1"})";

    static GetWallet create_default_request() {
        return GetWallet().set_user_id("1")
                          .set_eth_address("1");
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
