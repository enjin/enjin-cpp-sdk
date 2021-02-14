#include "enjinsdk/project/InvalidateTokenMetadata.hpp"
#include "../../../../suites/JsonTestSuite.hpp"
#include <string>

using namespace enjin::sdk::project;

class InvalidateTokenMetadataTest : public JsonTestSuite {
public:
    InvalidateTokenMetadata class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"id":"1"})";

    static InvalidateTokenMetadata create_default_request() {
        return InvalidateTokenMetadata().set_id("1");
    }
};

TEST_F(InvalidateTokenMetadataTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EMPTY_JSON_OBJECT);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(InvalidateTokenMetadataTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_id("1");

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(InvalidateTokenMetadataTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    InvalidateTokenMetadata lhs;
    InvalidateTokenMetadata rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(InvalidateTokenMetadataTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    InvalidateTokenMetadata lhs = create_default_request();
    InvalidateTokenMetadata rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(InvalidateTokenMetadataTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    InvalidateTokenMetadata lhs = create_default_request();
    InvalidateTokenMetadata rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(InvalidateTokenMetadataTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    InvalidateTokenMetadata lhs;
    InvalidateTokenMetadata rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
