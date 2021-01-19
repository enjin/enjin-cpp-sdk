#include "ModelsTestSuite.hpp"
#include "enjinsdk/models/MintInput.hpp"
#include <string>

using namespace enjin::sdk::models;

class MintInputTest : public ModelsTestSuite {
public:
    MintInput class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"to":"1","value":"1"})";

    static MintInput create_default_mint_input() {
        return MintInput().set_to("1")
                          .set_value("1");
    }
};

TEST_F(MintInputTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EMPTY_JSON_OBJECT);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(MintInputTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_to("1")
                    .set_value("1");

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(MintInputTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    MintInput lhs;
    MintInput rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(MintInputTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    MintInput lhs = create_default_mint_input();
    MintInput rhs = create_default_mint_input();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(MintInputTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    MintInput lhs = create_default_mint_input();
    MintInput rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(MintInputTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    MintInput lhs;
    MintInput rhs = create_default_mint_input();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
