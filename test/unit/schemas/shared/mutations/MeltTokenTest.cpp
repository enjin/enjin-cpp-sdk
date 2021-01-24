#include "../../../models/ModelsTestSuite.hpp"
#include "enjinsdk/shared/MeltToken.hpp"
#include <string>
#include <vector>

using namespace enjin::sdk::shared;

class MeltTokenTest : public ModelsTestSuite {
public:
    MeltToken class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"melts":[]})";

    static MeltToken create_default_request() {
        return MeltToken().set_melts(std::vector<enjin::sdk::models::Melt>());
    }
};

TEST_F(MeltTokenTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EMPTY_JSON_OBJECT);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(MeltTokenTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_melts(std::vector<enjin::sdk::models::Melt>());

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(MeltTokenTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    MeltToken lhs;
    MeltToken rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(MeltTokenTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    MeltToken lhs = create_default_request();
    MeltToken rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(MeltTokenTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    MeltToken lhs = create_default_request();
    MeltToken rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(MeltTokenTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    MeltToken lhs;
    MeltToken rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
