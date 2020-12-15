#include "enjinsdk/GraphqlRequest.hpp"
#include "gtest/gtest.h"
#include <any>

using namespace enjin::sdk::graphql;

class GraphqlRequestTest : public ::testing::Test {
    class TestableGraphqlRequest : public GraphqlRequest<TestableGraphqlRequest> {
    };

protected:
    TestableGraphqlRequest class_under_test;
};

TEST_F(GraphqlRequestTest, SetVariableVariableIsSetVariablesContainsVariable) {
    // Arrange
    const std::any expected;
    const std::string key("key");

    // Act
    class_under_test.set_variable(key, expected);

    // Assert
    ASSERT_NO_THROW(std::any actual = class_under_test.get_variables().at(key));
}

TEST_F(GraphqlRequestTest, SetVariableChaining) {
    // Arrange
    const std::string key1("key1");
    const std::any value1 = std::make_any<int>(1);
    const std::string key2("key2");
    const std::any value2 = std::make_any<int>(2);
    const std::string key3("key3");
    const std::any value3 = std::make_any<int>(3);

    // Act
    class_under_test.set_variable(key1, value1)
                    .set_variable(key2, value2)
                    .set_variable(key3, value3);

    // Assert
    EXPECT_TRUE(class_under_test.is_set(key1));
    EXPECT_TRUE(class_under_test.is_set(key2));
    EXPECT_TRUE(class_under_test.is_set(key3));
}

TEST_F(GraphqlRequestTest, IsSetVariableIsSetReturnsTrue) {
    // Arrange
    const std::string key("key");
    const std::any value = std::make_any<std::string>("value");
    class_under_test.set_variable(key, value);

    // Act
    bool actual = class_under_test.is_set(key);

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(GraphqlRequestTest, IsSetVariableIsNotSetReturnsFalse) {
    // Arrange
    const std::string key("key");

    // Act
    bool actual = class_under_test.is_set(key);

    // Assert
    ASSERT_FALSE(actual);
}
