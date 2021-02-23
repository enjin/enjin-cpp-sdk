#include "enjinsdk/internal/TransactionRequestArguments.hpp"
#include "../../../../suites/JsonTestSuite.hpp"

using namespace enjin::sdk::shared;

class TransactionRequestArgumentsTest : public JsonTestSuite {
public:
    TransactionRequestArguments class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"ethAddress":"1","send":true})";

    static TransactionRequestArguments create_default_arguments() {
        TransactionRequestArguments arguments;
        arguments.set_eth_address("1");
        arguments.set_send(true);
        return arguments;
    }
};

TEST_F(TransactionRequestArgumentsTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EMPTY_JSON_OBJECT);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(TransactionRequestArgumentsTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_eth_address("1");
    class_under_test.set_send(true);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(TransactionRequestArgumentsTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    TransactionRequestArguments lhs;
    TransactionRequestArguments rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(TransactionRequestArgumentsTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    TransactionRequestArguments lhs = create_default_arguments();
    TransactionRequestArguments rhs = create_default_arguments();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(TransactionRequestArgumentsTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    TransactionRequestArguments lhs = create_default_arguments();
    TransactionRequestArguments rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(TransactionRequestArgumentsTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    TransactionRequestArguments lhs;
    TransactionRequestArguments rhs = create_default_arguments();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
