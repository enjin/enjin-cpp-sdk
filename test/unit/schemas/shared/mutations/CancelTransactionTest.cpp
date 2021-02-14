#include "enjinsdk/shared/CancelTransaction.hpp"
#include "../../../../suites/JsonTestSuite.hpp"
#include <string>

using namespace enjin::sdk::shared;

class CancelTransactionTest : public JsonTestSuite {
public:
    CancelTransaction class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"id":1})";

    static CancelTransaction create_default_request() {
        return CancelTransaction().set_id(1);
    }
};

TEST_F(CancelTransactionTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EMPTY_JSON_OBJECT);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(CancelTransactionTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_id(1);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(CancelTransactionTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    CancelTransaction lhs;
    CancelTransaction rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(CancelTransactionTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    CancelTransaction lhs = create_default_request();
    CancelTransaction rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(CancelTransactionTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    CancelTransaction lhs = create_default_request();
    CancelTransaction rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(CancelTransactionTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    CancelTransaction lhs;
    CancelTransaction rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
