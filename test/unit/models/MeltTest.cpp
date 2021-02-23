#include "enjinsdk/models/Melt.hpp"
#include "../../suites/JsonTestSuite.hpp"
#include <string>

using namespace enjin::sdk::models;

class MeltTest : public JsonTestSuite {
public:
    Melt class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"assetId":"1","assetIndex":"1","value":"1"})";

    static Melt create_default_melt() {
        return Melt().set_asset_id("1")
                     .set_asset_index("1")
                     .set_value("1");
    }
};

TEST_F(MeltTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EMPTY_JSON_OBJECT);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(MeltTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_asset_id("1")
                    .set_asset_index("1")
                    .set_value("1");

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(MeltTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    Melt lhs;
    Melt rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(MeltTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    Melt lhs = create_default_melt();
    Melt rhs = create_default_melt();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(MeltTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    Melt lhs = create_default_melt();
    Melt rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(MeltTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    Melt lhs;
    Melt rhs = create_default_melt();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
