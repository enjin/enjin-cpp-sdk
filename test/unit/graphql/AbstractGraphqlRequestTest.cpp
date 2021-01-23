#include "enjinsdk/AbstractGraphqlRequest.hpp"
#include "gtest/gtest.h"
#include <string>

using namespace enjin::sdk::graphql;

class AbstractGraphqlRequestTest : public ::testing::Test {
public:
    class TestableGraphqlRequest : public AbstractGraphqlRequest {
    public:
        TestableGraphqlRequest() : AbstractGraphqlRequest() {
        }

        explicit TestableGraphqlRequest(const std::string& template_key) : AbstractGraphqlRequest(template_key) {
        }

        std::string serialize() override {
            return std::string();
        }
    };

    TestableGraphqlRequest class_under_test;

    TestableGraphqlRequest static create_default_request() {
        return TestableGraphqlRequest("test");
    }
};

TEST_F(AbstractGraphqlRequestTest, EqualityNeitherSideHaveTemplateKeyReturnsTrue) {
    // Arrange
    TestableGraphqlRequest lhs;
    TestableGraphqlRequest rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(AbstractGraphqlRequestTest, EqualityBothSidesHaveTemplateKeyReturnsTrue) {
    // Arrange
    TestableGraphqlRequest lhs = create_default_request();
    TestableGraphqlRequest rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(AbstractGraphqlRequestTest, EqualityLeftSideHasTemplateKeyReturnsFalse) {
    // Arrange
    TestableGraphqlRequest lhs = create_default_request();
    TestableGraphqlRequest rhs;

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(AbstractGraphqlRequestTest, EqualityRightSideHasTemplateKeyReturnsFalse) {
    // Arrange
    TestableGraphqlRequest lhs;
    TestableGraphqlRequest rhs = create_default_request();

    // Act
    bool actual = lhs == rhs;

    // Assert
    ASSERT_FALSE(actual);
}
