#include "enjinsdk/project/MintToken.hpp"
#include "../../../../suites/JsonTestSuite.hpp"
#include <string>
#include <vector>

using namespace enjin::sdk::project;

class MintTokenTest : public JsonTestSuite {
public:
    MintToken class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"tokenId":"1","mints":[]})";

    static MintToken create_default_request() {
        return MintToken().set_token_id("1")
                          .set_mints(std::vector<enjin::sdk::models::MintInput>());
    }
};

TEST_F(MintTokenTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EMPTY_JSON_OBJECT);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(MintTokenTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_token_id("1")
                    .set_mints(std::vector<enjin::sdk::models::MintInput>());

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(MintTokenTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    MintToken lhs;
    MintToken rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(MintTokenTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    MintToken lhs = create_default_request();
    MintToken rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(MintTokenTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    MintToken lhs = create_default_request();
    MintToken rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(MintTokenTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    MintToken lhs;
    MintToken rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
