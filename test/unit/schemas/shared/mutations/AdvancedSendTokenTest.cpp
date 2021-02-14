#include "enjinsdk/shared/AdvancedSendToken.hpp"
#include "../../../../suites/JsonTestSuite.hpp"
#include <string>

using namespace enjin::sdk::shared;

class AdvancedSendTokenTest : public JsonTestSuite {
public:
    AdvancedSendToken class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"transfers":[],"data":"1"})";

    static AdvancedSendToken create_default_request() {
        return AdvancedSendToken().set_transfers(std::vector<enjin::sdk::models::Transfer>())
                                  .set_data("1");
    }
};

TEST_F(AdvancedSendTokenTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EMPTY_JSON_OBJECT);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(AdvancedSendTokenTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_transfers(std::vector<enjin::sdk::models::Transfer>())
                    .set_data("1");

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(AdvancedSendTokenTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    AdvancedSendToken lhs;
    AdvancedSendToken rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(AdvancedSendTokenTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    AdvancedSendToken lhs = create_default_request();
    AdvancedSendToken rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(AdvancedSendTokenTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    AdvancedSendToken lhs = create_default_request();
    AdvancedSendToken rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(AdvancedSendTokenTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    AdvancedSendToken lhs;
    AdvancedSendToken rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
