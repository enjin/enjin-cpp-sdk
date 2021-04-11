#include "JsonTestSuite.hpp"
#include "PaginationArgumentsTestSuite.hpp"
#include "PlayerFragmentArgumentsTestSuite.hpp"
#include "enjinsdk/project/GetPlayers.hpp"
#include "gtest/gtest.h"
#include <string>

using namespace enjin::sdk::models;
using namespace enjin::sdk::project;
using namespace enjin::test::suites;

class GetPlayersTest : public PlayerFragmentArgumentsTestSuite<GetPlayers>,
                       public PaginationArgumentsTestSuite<GetPlayers>,
                       public JsonTestSuite,
                       public testing::Test {
public:
    GetPlayers class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"filter":{}})";

    static GetPlayers create_default_request() {
        GetPlayers request = GetPlayers()
                .set_filter(PlayerFilter());
        set_player_fragment_arguments(request);
        set_pagination_arguments(request);
        return request;
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
    class_under_test.set_filter(PlayerFilter());

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
