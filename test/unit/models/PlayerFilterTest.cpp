#include "ModelsTestSuite.hpp"
#include "enjinsdk/models/PlayerFilter.hpp"
#include <string>
#include <vector>

using namespace enjin::sdk::models;

class PlayerFilterTest : public ModelsTestSuite {
public:
    PlayerFilter class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"and":[],"or":[],"id":"1","id_in":[]})";

    static PlayerFilter create_default_filter() {
        return PlayerFilter().set_and(std::vector<PlayerFilter>())
                             .set_or(std::vector<PlayerFilter>())
                             .set_id("1")
                             .set_id_in(std::vector<std::string>());
    }
};

TEST_F(PlayerFilterTest, SerializeNoSetFieldsReturnsFilterWithNoSetFields) {
    // Arrange
    const std::string expected(EMPTY_JSON_OBJECT);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(PlayerFilterTest, SerializeSetFieldsReturnsFilterWithSetFields) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_and(std::vector<PlayerFilter>())
                    .set_or(std::vector<PlayerFilter>())
                    .set_id("1")
                    .set_id_in(std::vector<std::string>());

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(PlayerFilterTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    PlayerFilter lhs;
    PlayerFilter rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(PlayerFilterTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    PlayerFilter lhs = create_default_filter();
    PlayerFilter rhs = create_default_filter();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(PlayerFilterTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    PlayerFilter lhs = create_default_filter();
    PlayerFilter rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(PlayerFilterTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    PlayerFilter lhs;
    PlayerFilter rhs = create_default_filter();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
