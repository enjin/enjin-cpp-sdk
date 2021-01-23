#include "../../../models/ModelsTestSuite.hpp"
#include "enjinsdk/internal/PlayerFragmentArguments.hpp"

using namespace enjin::sdk::shared;

class PlayerFragmentArgumentsTest : public ModelsTestSuite {
public:
    PlayerFragmentArguments class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"withLinkingInfo":true,"linkingCodeQrSize":1,"withPlayerWallet":true})";

    static PlayerFragmentArguments create_default_arguments() {
        PlayerFragmentArguments arguments;
        arguments.set_with_linking_info();
        arguments.set_qr_size(1);
        arguments.set_with_wallet();
        return arguments;
    }
};

TEST_F(PlayerFragmentArgumentsTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EMPTY_JSON_OBJECT);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(PlayerFragmentArgumentsTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_with_linking_info();
    class_under_test.set_qr_size(1);
    class_under_test.set_with_wallet();

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(PlayerFragmentArgumentsTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    PlayerFragmentArguments lhs;
    PlayerFragmentArguments rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(PlayerFragmentArgumentsTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    PlayerFragmentArguments lhs = create_default_arguments();
    PlayerFragmentArguments rhs = create_default_arguments();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(PlayerFragmentArgumentsTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    PlayerFragmentArguments lhs = create_default_arguments();
    PlayerFragmentArguments rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(PlayerFragmentArgumentsTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    PlayerFragmentArguments lhs;
    PlayerFragmentArguments rhs = create_default_arguments();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
