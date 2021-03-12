#include "JsonTestSuite.hpp"
#include "enjinsdk/project/GetPlayers.hpp"
#include <string>

using namespace enjin::sdk::project;

class GetPlayersTest : public JsonTestSuite {
public:
    GetPlayers class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"filter":{}})";

    static GetPlayers create_default_request() {
        return GetPlayers().set_filter(enjin::sdk::models::PlayerFilter());
    }
};

TEST_F(GetPlayersTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EMPTY_JSON_OBJECT);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(GetPlayersTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_filter(enjin::sdk::models::PlayerFilter());

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(GetPlayersTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    GetPlayers lhs;
    GetPlayers rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(GetPlayersTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    GetPlayers lhs = create_default_request();
    GetPlayers rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(GetPlayersTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    GetPlayers lhs = create_default_request();
    GetPlayers rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(GetPlayersTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    GetPlayers lhs;
    GetPlayers rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
