#include "JsonTestSuite.hpp"
#include "enjinsdk/internal/TransactionRequestArgumentsImpl.hpp"
#include <string>

using namespace enjin::sdk::shared;

class TransactionRequestArgumentsImplTest : public JsonTestSuite {
public:
    TransactionRequestArgumentsImpl class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"ethAddress":"1","send":true})";

    static TransactionRequestArgumentsImpl create_default_arguments() {
        TransactionRequestArgumentsImpl arguments;
        arguments.set_eth_address("1");
        arguments.set_send(true);
        return arguments;
    }
};

TEST_F(TransactionRequestArgumentsImplTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EMPTY_JSON_OBJECT);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(TransactionRequestArgumentsImplTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_eth_address("1");
    class_under_test.set_send(true);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(TransactionRequestArgumentsImplTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    TransactionRequestArgumentsImpl lhs;
    TransactionRequestArgumentsImpl rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(TransactionRequestArgumentsImplTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    TransactionRequestArgumentsImpl lhs = create_default_arguments();
    TransactionRequestArgumentsImpl rhs = create_default_arguments();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(TransactionRequestArgumentsImplTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    TransactionRequestArgumentsImpl lhs = create_default_arguments();
    TransactionRequestArgumentsImpl rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(TransactionRequestArgumentsImplTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    TransactionRequestArgumentsImpl lhs;
    TransactionRequestArgumentsImpl rhs = create_default_arguments();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
