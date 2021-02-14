#include "enjinsdk/shared/SetApprovalForAll.hpp"
#include "../../../../suites/JsonTestSuite.hpp"
#include <string>

using namespace enjin::sdk::shared;

class SetApprovalForAllTest : public JsonTestSuite {
public:
    SetApprovalForAll class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"operatorAddress":"1","approved":true})";

    static SetApprovalForAll create_default_request() {
        return SetApprovalForAll().set_operator_address("1")
                                  .set_approved(true);
    }
};

TEST_F(SetApprovalForAllTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EMPTY_JSON_OBJECT);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(SetApprovalForAllTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_operator_address("1")
                    .set_approved(true);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(SetApprovalForAllTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    SetApprovalForAll lhs;
    SetApprovalForAll rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(SetApprovalForAllTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    SetApprovalForAll lhs = create_default_request();
    SetApprovalForAll rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(SetApprovalForAllTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    SetApprovalForAll lhs = create_default_request();
    SetApprovalForAll rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(SetApprovalForAllTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    SetApprovalForAll lhs;
    SetApprovalForAll rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
