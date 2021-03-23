#include "enjinsdk/internal/AbstractGraphqlRequest.hpp"
#include "gtest/gtest.h"
#include <string>

using namespace enjin::sdk::graphql;

class AbstractGraphqlRequestTest : public ::testing::Test {
public:
    class TestableGraphqlRequest : public AbstractGraphqlRequest {
    public:
        TestableGraphqlRequest() = delete;

        explicit TestableGraphqlRequest(const std::string& template_key) : AbstractGraphqlRequest(template_key) {
        }

        std::string serialize() override {
            return std::string();
        }
    };
};

TEST_F(AbstractGraphqlRequestTest, EqualityBothSidesHaveSameTemplateKeyReturnsTrue) {
    // Arrange
    const std::string key("test");
    TestableGraphqlRequest lhs(key);
    TestableGraphqlRequest rhs(key);

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(AbstractGraphqlRequestTest, EqualityBothSidesHaveDifferentTemplateKeyReturnsFalse) {
    // Arrange
    TestableGraphqlRequest lhs("left");
    TestableGraphqlRequest rhs("right");

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
