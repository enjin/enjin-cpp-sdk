#include "JsonTestSuite.hpp"
#include "enjinsdk/internal/BalanceFragmentArgumentsImpl.hpp"
#include <string>

using namespace enjin::sdk::shared;

class BalanceFragmentArgumentsImplTest : public JsonTestSuite {
public:
    BalanceFragmentArgumentsImpl class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"balIdFormat":"hex64","balIndexFormat":"hex64","withBalProjectId":true,"withBalWalletAddress":true})";

    static BalanceFragmentArgumentsImpl create_default_arguments() {
        BalanceFragmentArgumentsImpl arguments;
        arguments.set_bal_id_format(enjin::sdk::models::AssetIdFormat::HEX64);
        arguments.set_bal_index_format(enjin::sdk::models::AssetIndexFormat::HEX64);
        arguments.set_with_bal_project_id();
        arguments.set_with_bal_wallet_address();
        return arguments;
    }
};

TEST_F(BalanceFragmentArgumentsImplTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EMPTY_JSON_OBJECT);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(BalanceFragmentArgumentsImplTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_bal_id_format(enjin::sdk::models::AssetIdFormat::HEX64);
    class_under_test.set_bal_index_format(enjin::sdk::models::AssetIndexFormat::HEX64);
    class_under_test.set_with_bal_project_id();
    class_under_test.set_with_bal_wallet_address();

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(BalanceFragmentArgumentsImplTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    BalanceFragmentArgumentsImpl lhs;
    BalanceFragmentArgumentsImpl rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(BalanceFragmentArgumentsImplTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    BalanceFragmentArgumentsImpl lhs = create_default_arguments();
    BalanceFragmentArgumentsImpl rhs = create_default_arguments();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(BalanceFragmentArgumentsImplTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    BalanceFragmentArgumentsImpl lhs = create_default_arguments();
    BalanceFragmentArgumentsImpl rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(BalanceFragmentArgumentsImplTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    BalanceFragmentArgumentsImpl lhs;
    BalanceFragmentArgumentsImpl rhs = create_default_arguments();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
