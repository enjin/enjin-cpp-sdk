#include "enjinsdk/HttpRequest.hpp"
#include "gtest/gtest.h"
#include <string>

using namespace enjin::sdk::http;

class HttpRequestBuilderTest : public testing::Test {
public:
    HttpRequestBuilder class_under_test;
};

TEST_F(HttpRequestBuilderTest, BuildDoesNotThrowException) {
    // Assert
    ASSERT_NO_THROW(class_under_test.build());
}

TEST_F(HttpRequestBuilderTest, BuildNoSetValuesBuiltRequestIsEmpty) {
    // Act
    HttpRequest actual = class_under_test.build();

    // Assert
    EXPECT_TRUE(actual.get_method().empty());
    EXPECT_TRUE(actual.get_path_query_fragment().empty());
    EXPECT_TRUE(actual.get_body().empty());
    EXPECT_TRUE(actual.get_content_type().empty());
}

TEST_F(HttpRequestBuilderTest, MethodValueIsSetBuiltRequestHasExpectedValue) {
    // Arrange
    const std::string expected("expected");

    // Act
    std::string actual = class_under_test.method(expected)
                                         .build()
                                         .get_method();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(HttpRequestBuilderTest, PathQueryFragmentValueIsSetBuiltRequestHasExpectedValue) {
    // Arrange
    const std::string expected("expected");

    // Act
    std::string actual = class_under_test.path_query_fragment(expected)
                                         .build()
                                         .get_path_query_fragment();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(HttpRequestBuilderTest, BodyValueIsSetBuiltRequestHasExpectedValue) {
    // Arrange
    const std::string expected("expected");

    // Act
    std::string actual = class_under_test.body(expected)
                                         .build()
                                         .get_body();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(HttpRequestBuilderTest, ContentTypeValueIsSetBuiltRequestHasExpectedValue) {
    // Arrange
    const std::string expected("expected");

    // Act
    std::string actual = class_under_test.content_type(expected)
                                         .build()
                                         .get_content_type();

    // Assert
    ASSERT_EQ(expected, actual);
}
