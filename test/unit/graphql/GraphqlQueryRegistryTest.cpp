#include "enjinsdk/GraphqlQueryRegistry.hpp"

#include "gtest/gtest.h"

using namespace enjin::sdk::graphql;

class GraphqlQueryRegistryTest : public ::testing::Test {
protected:
    GraphqlQueryRegistry class_under_test;

    static constexpr char default_key[] = "key";
    static constexpr char default_query[] = "query";
};

TEST_F(GraphqlQueryRegistryTest, RegisterTemplateRegistryDoesNotHaveKeyReturnsTrue) {
    // Arrange
    const std::string key(default_key);
    const std::string query(default_query);

    // Act
    bool actual = class_under_test.register_template(key, query);

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(GraphqlQueryRegistryTest, RegisterTemplateRegistryDoesHaveKeyReturnsFalse) {
    // Arrange
    const std::string key(default_key);
    const std::string query1("query1");
    const std::string query2("query2");
    class_under_test.register_template(key, query1);

    // Act
    bool actual = class_under_test.register_template(key, query2);

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(GraphqlQueryRegistryTest, HasOperationForNameRegistryDoesHaveKeyReturnsTrue) {
    // Arrange
    const std::string key(default_key);
    const std::string query(default_query);
    class_under_test.register_template(key, query);

    // Act
    bool actual = class_under_test.has_operation_for_name(key);

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(GraphqlQueryRegistryTest, HasOperationForNameRegistryDoesNotHaveKeyReturnsFalse) {
    // Arrange
    const std::string key(default_key);

    // Act
    bool actual = class_under_test.has_operation_for_name(key);

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(GraphqlQueryRegistryTest, GetOperationForNameRegistryDoesHaveMappingReturnsQueryString) {
    // Arrange
    const std::string expected(default_query);
    const std::string key(default_key);
    class_under_test.register_template(key, expected);

    // Act
    std::string actual = class_under_test.get_operation_for_name(key);

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(GraphqlQueryRegistryTest, GetOperationForNameRegistryDoesNotHaveMappingReturnsEmptyString) {
    // Arrange
    const std::string key(default_key);

    // Act
    std::string actual = class_under_test.get_operation_for_name(key);

    // Assert
    ASSERT_TRUE(actual.empty());
}
