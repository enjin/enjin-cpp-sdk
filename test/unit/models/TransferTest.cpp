#include "enjinsdk/models/Transfer.hpp"
#include "../../suites/JsonTestSuite.hpp"
#include <string>

using namespace enjin::sdk::models;

class TransferTest : public JsonTestSuite {
public:
    Transfer class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"from":"1","to":"1","tokenId":"1","tokenIndex":"1","value":"1"})";

    static Transfer create_default_transfer() {
        return Transfer().set_from("1")
                         .set_to("1")
                         .set_token_id("1")
                         .set_token_index("1")
                         .set_value("1");
    }
};

TEST_F(TransferTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EMPTY_JSON_OBJECT);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(TransferTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_from("1")
                    .set_to("1")
                    .set_token_id("1")
                    .set_token_index("1")
                    .set_value("1");

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(TransferTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    Transfer lhs;
    Transfer rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(TransferTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    Transfer lhs = create_default_transfer();
    Transfer rhs = create_default_transfer();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(TransferTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    Transfer lhs = create_default_transfer();
    Transfer rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(TransferTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    Transfer lhs;
    Transfer rhs = create_default_transfer();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
