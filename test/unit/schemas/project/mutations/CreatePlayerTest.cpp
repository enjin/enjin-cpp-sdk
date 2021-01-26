#include "../../../models/ModelsTestSuite.hpp"
#include "enjinsdk/project/CreatePlayer.hpp"
#include <string>

using namespace enjin::sdk::project;

class CreatePlayerTest : public ModelsTestSuite {
public:
    CreatePlayer class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"id":"1"})";

    static CreatePlayer create_default_request() {
        return CreatePlayer().set_id("1");
    }
};

TEST_F(CreatePlayerTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EMPTY_JSON_OBJECT);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(CreatePlayerTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_id("1");

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(CreatePlayerTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    CreatePlayer lhs;
    CreatePlayer rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(CreatePlayerTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    CreatePlayer lhs = create_default_request();
    CreatePlayer rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(CreatePlayerTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    CreatePlayer lhs = create_default_request();
    CreatePlayer rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(CreatePlayerTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    CreatePlayer lhs;
    CreatePlayer rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
