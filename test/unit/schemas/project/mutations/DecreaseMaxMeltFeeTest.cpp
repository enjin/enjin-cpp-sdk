#include "../../../models/ModelsTestSuite.hpp"
#include "enjinsdk/project/DecreaseMaxMeltFee.hpp"
#include <string>

using namespace enjin::sdk::project;

class DecreaseMaxMeltFeeTest : public ModelsTestSuite {
public:
    DecreaseMaxMeltFee class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"tokenId":"1","tokenIndex":"1","maxMeltFee":1})";

    static DecreaseMaxMeltFee create_default_request() {
        return DecreaseMaxMeltFee().set_token_id("1")
                                   .set_token_index("1")
                                   .set_max_melt_fee(1);
    }
};

TEST_F(DecreaseMaxMeltFeeTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EMPTY_JSON_OBJECT);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(DecreaseMaxMeltFeeTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_token_id("1")
                    .set_token_index("1")
                    .set_max_melt_fee(1);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(DecreaseMaxMeltFeeTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    DecreaseMaxMeltFee lhs;
    DecreaseMaxMeltFee rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(DecreaseMaxMeltFeeTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    DecreaseMaxMeltFee lhs = create_default_request();
    DecreaseMaxMeltFee rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(DecreaseMaxMeltFeeTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    DecreaseMaxMeltFee lhs = create_default_request();
    DecreaseMaxMeltFee rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(DecreaseMaxMeltFeeTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    DecreaseMaxMeltFee lhs;
    DecreaseMaxMeltFee rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
