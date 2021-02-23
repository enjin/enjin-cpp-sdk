#include "enjinsdk/project/SetUri.hpp"
#include "../../../../suites/JsonTestSuite.hpp"
#include <string>

using namespace enjin::sdk::project;

class SetUriTest : public JsonTestSuite {
public:
    SetUri class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"assetId":"1","assetIndex":"1","uri":"1"})";

    static SetUri create_default_request() {
        return SetUri().set_asset_id("1")
                       .set_asset_index("1")
                       .set_uri("1");
    }
};

TEST_F(SetUriTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EMPTY_JSON_OBJECT);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(SetUriTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_asset_id("1")
                    .set_asset_index("1")
                    .set_uri("1");

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(SetUriTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    SetUri lhs;
    SetUri rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(SetUriTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    SetUri lhs = create_default_request();
    SetUri rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(SetUriTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    SetUri lhs = create_default_request();
    SetUri rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(SetUriTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    SetUri lhs;
    SetUri rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
