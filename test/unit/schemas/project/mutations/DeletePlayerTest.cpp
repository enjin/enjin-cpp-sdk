#include "enjinsdk/project/DeletePlayer.hpp"
#include "../../../../suites/JsonTestSuite.hpp"
#include <string>

using namespace enjin::sdk::project;

class DeletePlayerTest : public JsonTestSuite {
public:
    DeletePlayer class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"id":"1"})";

    static DeletePlayer create_default_request() {
        return DeletePlayer().set_id("1");
    }
};

TEST_F(DeletePlayerTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EMPTY_JSON_OBJECT);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(DeletePlayerTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_id("1");

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(DeletePlayerTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    DeletePlayer lhs;
    DeletePlayer rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(DeletePlayerTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    DeletePlayer lhs = create_default_request();
    DeletePlayer rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(DeletePlayerTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    DeletePlayer lhs = create_default_request();
    DeletePlayer rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(DeletePlayerTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    DeletePlayer lhs;
    DeletePlayer rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
