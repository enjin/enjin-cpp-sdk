#include "enjinsdk/internal/BalanceFragmentArguments.hpp"
#include "../../../../suites/JsonTestSuite.hpp"

using namespace enjin::sdk::shared;

class BalanceFragmentArgumentsTest : public JsonTestSuite {
public:
    BalanceFragmentArguments class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"balIdFormat":"hex64","balIndexFormat":"hex64","withBalProjectId":true,"withBalWalletAddress":true})";

    static BalanceFragmentArguments create_default_arguments() {
        BalanceFragmentArguments arguments;
        arguments.set_bal_id_format(enjin::sdk::models::AssetIdFormat::HEX64);
        arguments.set_bal_index_format(enjin::sdk::models::AssetIndexFormat::HEX64);
        arguments.set_with_bal_project_id();
        arguments.set_with_bal_wallet_address();
        return arguments;
    }
};

TEST_F(BalanceFragmentArgumentsTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EMPTY_JSON_OBJECT);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(BalanceFragmentArgumentsTest, SerializeSetFieldsReturnsExpectedJsonObject) {
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

TEST_F(BalanceFragmentArgumentsTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    BalanceFragmentArguments lhs;
    BalanceFragmentArguments rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(BalanceFragmentArgumentsTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    BalanceFragmentArguments lhs = create_default_arguments();
    BalanceFragmentArguments rhs = create_default_arguments();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(BalanceFragmentArgumentsTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    BalanceFragmentArguments lhs = create_default_arguments();
    BalanceFragmentArguments rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(BalanceFragmentArgumentsTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    BalanceFragmentArguments lhs;
    BalanceFragmentArguments rhs = create_default_arguments();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
