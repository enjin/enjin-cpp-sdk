#include "JsonTestSuite.hpp"
#include "enjinsdk/project/InvalidateAssetMetadata.hpp"
#include <string>

using namespace enjin::sdk::project;

class InvalidateAssetMetadataTest : public JsonTestSuite {
public:
    InvalidateAssetMetadata class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"id":"1"})";

    static InvalidateAssetMetadata create_default_request() {
        return InvalidateAssetMetadata().set_id("1");
    }
};

TEST_F(InvalidateAssetMetadataTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EMPTY_JSON_OBJECT);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(InvalidateAssetMetadataTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_id("1");

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(InvalidateAssetMetadataTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    InvalidateAssetMetadata lhs;
    InvalidateAssetMetadata rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(InvalidateAssetMetadataTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    InvalidateAssetMetadata lhs = create_default_request();
    InvalidateAssetMetadata rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(InvalidateAssetMetadataTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    InvalidateAssetMetadata lhs = create_default_request();
    InvalidateAssetMetadata rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(InvalidateAssetMetadataTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    InvalidateAssetMetadata lhs;
    InvalidateAssetMetadata rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
