#include "../../../models/ModelsTestSuite.hpp"
#include "enjinsdk/project/ReleaseReserve.hpp"
#include <string>

using namespace enjin::sdk::project;

class ReleaseReserveTest : public ModelsTestSuite {
public:
    ReleaseReserve class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"tokenId":"1","value":"1"})";

    static ReleaseReserve create_default_request() {
        return ReleaseReserve().set_token_id("1")
                               .set_value("1");
    }
};

TEST_F(ReleaseReserveTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EMPTY_JSON_OBJECT);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(ReleaseReserveTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_token_id("1")
                    .set_value("1");

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(ReleaseReserveTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    ReleaseReserve lhs;
    ReleaseReserve rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(ReleaseReserveTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    ReleaseReserve lhs = create_default_request();
    ReleaseReserve rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(ReleaseReserveTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    ReleaseReserve lhs = create_default_request();
    ReleaseReserve rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(ReleaseReserveTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    ReleaseReserve lhs;
    ReleaseReserve rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
