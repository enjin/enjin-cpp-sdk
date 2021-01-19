#include "ModelsTestSuite.hpp"
#include "enjinsdk/models/TokenFilter.hpp"
#include <string>
#include <vector>

using namespace enjin::sdk::models;

class TokenFilterTest : public ModelsTestSuite {
public:
    TokenFilter class_under_test;

    constexpr static char POPULATED_JSON_OBJECT[] =
            R"({"and":[],"or":[],"id":"1","id_in":[],"name":"1","name_contains":"1","name_in":[],"name_starts_with":"1","name_ends_with":"1","wallet":"1","wallet_in":[]})";

    static TokenFilter create_default_filter() {
        return TokenFilter().set_and(std::vector<TokenFilter>())
                            .set_or(std::vector<TokenFilter>())
                            .set_id("1")
                            .set_id_in(std::vector<std::string>())
                            .set_name("1")
                            .set_name_contains("1")
                            .set_name_in(std::vector<std::string>())
                            .set_name_starts_with("1")
                            .set_name_ends_with("1")
                            .set_wallet("1")
                            .set_wallet_in(std::vector<std::string>());
    }
};

TEST_F(TokenFilterTest, SerializeNoSetFieldsReturnsEmptyJsonObject) {
    // Arrange
    const std::string expected(EMPTY_JSON_OBJECT);

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(TokenFilterTest, SerializeSetFieldsReturnsExpectedJsonObject) {
    // Arrange
    const std::string expected(POPULATED_JSON_OBJECT);
    class_under_test.set_and(std::vector<TokenFilter>())
                    .set_or(std::vector<TokenFilter>())
                    .set_id("1")
                    .set_id_in(std::vector<std::string>())
                    .set_name("1")
                    .set_name_contains("1")
                    .set_name_in(std::vector<std::string>())
                    .set_name_starts_with("1")
                    .set_name_ends_with("1")
                    .set_wallet("1")
                    .set_wallet_in(std::vector<std::string>());

    // Act
    std::string actual = class_under_test.serialize();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(TokenFilterTest, EqualityNeitherSideIsPopulatedReturnsTrue) {
    // Arrange
    TokenFilter lhs;
    TokenFilter rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(TokenFilterTest, EqualityBothSidesArePopulatedReturnsTrue) {
    // Arrange
    TokenFilter lhs = create_default_filter();
    TokenFilter rhs = create_default_filter();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(TokenFilterTest, EqualityLeftSideIsPopulatedReturnsFalse) {
    // Arrange
    TokenFilter lhs = create_default_filter();
    TokenFilter rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(TokenFilterTest, EqualityRightSideIsPopulatedReturnsFalse) {
    // Arrange
    TokenFilter lhs;
    TokenFilter rhs = create_default_filter();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
