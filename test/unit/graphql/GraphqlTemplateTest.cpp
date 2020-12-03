#include "GraphqlTemplate.hpp"

#include "gtest/gtest.h"
#include <list>
#include <string>

using namespace enjin::sdk::graphql;

class GraphqlTemplateTest : public ::testing::Test {
protected:
    static constexpr char default_empty_line[] = "";
    static constexpr char default_namespace[] = "enjin.graphql.Template";
};

TEST_F(GraphqlTemplateTest, ReadNamespaceContentsDoesHaveNamespaceReturnsNamespaceString) {
    // Arrange
    const std::string expected(default_namespace);
    std::stringstream namespace_stream;
    namespace_stream << GraphqlTemplate::namespace_key << " " << expected;
    std::list<std::string> contents;
    contents.emplace_back(default_empty_line);
    contents.emplace_back(namespace_stream.str());
    contents.emplace_back(default_empty_line);

    // Act
    std::string actual = GraphqlTemplate::read_namespace(contents);

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(GraphqlTemplateTest, ReadNamespaceContentsDoesNotHaveNamespaceReturnsEmptyString) {
    // Arrange
    std::list<std::string> contents;
    contents.emplace_back(default_empty_line);
    contents.emplace_back(default_empty_line);
    contents.emplace_back(default_empty_line);

    // Act
    std::string actual = GraphqlTemplate::read_namespace(contents);

    // Assert
    ASSERT_TRUE(actual.empty());
}
