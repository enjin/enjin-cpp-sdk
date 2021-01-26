#include "../../../models/ModelsTestSuite.hpp"
#include "enjinsdk/project/UnlinkWallet.hpp"
#include <string>

using namespace enjin::sdk::project;

class UnlinkWalletTest : public ModelsTestSuite {
public:
    UnlinkWallet class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"ethAddress":"1"})";

    static UnlinkWallet create_default_request() {
        return UnlinkWallet().set_eth_address("1");
    }
};

TEST_F(UnlinkWalletTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EMPTY_JSON_OBJECT);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(UnlinkWalletTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_eth_address("1");

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(UnlinkWalletTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    UnlinkWallet lhs;
    UnlinkWallet rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(UnlinkWalletTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    UnlinkWallet lhs = create_default_request();
    UnlinkWallet rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(UnlinkWalletTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    UnlinkWallet lhs = create_default_request();
    UnlinkWallet rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(UnlinkWalletTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    UnlinkWallet lhs;
    UnlinkWallet rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
