#include "enjinsdk/shared/GetAsset.hpp"
#include "../../../../suites/JsonTestSuite.hpp"
#include <string>

using namespace enjin::sdk::shared;

class GetTokenTest : public JsonTestSuite {
public:
    GetAsset class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"id":"1"})";

    static GetAsset create_default_request() {
        return GetAsset().set_id("1");
    }
};

TEST_F(GetTokenTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EMPTY_JSON_OBJECT);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(GetTokenTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_id("1");

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(GetTokenTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    GetAsset lhs;
    GetAsset rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(GetTokenTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    GetAsset lhs = create_default_request();
    GetAsset rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(GetTokenTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    GetAsset lhs = create_default_request();
    GetAsset rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(GetTokenTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    GetAsset lhs;
    GetAsset rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
