#include "enjinsdk/project/SetWhitelisted.hpp"
#include "../../../../suites/JsonTestSuite.hpp"
#include <string>

using namespace enjin::sdk::project;

class SetWhitelistedTest : public JsonTestSuite {
public:
    SetWhitelisted class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"assetId":"1","accountAddress":"1","whitelisted":"NONE","whitelistedAddress":"1","on":true})";

    static SetWhitelisted create_default_request() {
        return SetWhitelisted().set_asset_id("1")
                               .set_account_address("1")
                               .set_whitelisted(enjin::sdk::models::Whitelisted::NONE)
                               .set_whitelisted_address("1")
                               .set_on(true);
    }
};

TEST_F(SetWhitelistedTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EMPTY_JSON_OBJECT);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(SetWhitelistedTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_asset_id("1")
                    .set_account_address("1")
                    .set_whitelisted(enjin::sdk::models::Whitelisted::NONE)
                    .set_whitelisted_address("1")
                    .set_on(true);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(SetWhitelistedTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    SetWhitelisted lhs;
    SetWhitelisted rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(SetWhitelistedTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    SetWhitelisted lhs = create_default_request();
    SetWhitelisted rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(SetWhitelistedTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    SetWhitelisted lhs = create_default_request();
    SetWhitelisted rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(SetWhitelistedTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    SetWhitelisted lhs;
    SetWhitelisted rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
