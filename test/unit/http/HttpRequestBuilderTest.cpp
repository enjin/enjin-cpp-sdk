#include "enjinsdk/HttpRequest.hpp"
#include "gtest/gtest.h"
#include <string>

using namespace enjin::sdk::http;

class HttpRequestBuilderTest : public testing::Test {
public:
    static constexpr HttpMethod DEFAULT_METHOD = HttpMethod::Get;
    static constexpr char DEFAULT_PATH_QUERY_FRAGMENT[] = "/";
    static constexpr char DEFAULT_HEADER_NAME[] = "Connection";
    static constexpr char DEFAULT_HEADER_VALUE[] = "keep-alive";
    static constexpr char DEFAULT_CONTENT_TYPE[] = "application/json";
    static constexpr char DEFAULT_BODY[] = "{}";

    HttpRequestBuilder class_under_test;
};

TEST_F(HttpRequestBuilderTest, BuildMethodValueIsNotSetThrowsException) {
    // Arrange
    class_under_test.path_query_fragment(DEFAULT_PATH_QUERY_FRAGMENT)
                    .add_header(DEFAULT_HEADER_NAME, DEFAULT_HEADER_VALUE)
                    .content_type(DEFAULT_CONTENT_TYPE)
                    .body(DEFAULT_BODY);

    // Assert
    ASSERT_ANY_THROW(class_under_test.build());
}

TEST_F(HttpRequestBuilderTest, BuildMethodValueIsSetDoThrowsException) {
    // Arrange
    class_under_test.method(DEFAULT_METHOD)
                    .path_query_fragment(DEFAULT_PATH_QUERY_FRAGMENT)
                    .add_header(DEFAULT_HEADER_NAME, DEFAULT_HEADER_VALUE)
                    .content_type(DEFAULT_CONTENT_TYPE)
                    .body(DEFAULT_BODY);

    // Assert
    ASSERT_NO_THROW(class_under_test.build());
}

TEST_F(HttpRequestBuilderTest, MethodValueIsSetBuiltRequestHasExpectedValue) {
    // Arrange
    const HttpMethod expected = DEFAULT_METHOD;

    // Act
    HttpMethod actual = class_under_test.method(expected)
                                        .build()
                                        .get_method();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(HttpRequestBuilderTest, PathQueryFragmentValueIsSetBuiltRequestHasExpectedValue) {
    // Arrange
    const std::string expected(DEFAULT_PATH_QUERY_FRAGMENT);
    class_under_test.method(DEFAULT_METHOD);

    // Act
    std::string actual = class_under_test.path_query_fragment(expected)
                                         .build()
                                         .get_path_query_fragment();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(HttpRequestBuilderTest, BodyValueIsSetBuiltRequestHasExpectedValue) {
    // Arrange
    const std::string expected(DEFAULT_BODY);
    class_under_test.method(DEFAULT_METHOD);

    // Act
    std::string actual = class_under_test.body(expected)
                                         .build()
                                         .get_body();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(HttpRequestBuilderTest, ContentTypeValueIsSetBuiltRequestHasExpectedValue) {
    // Arrange
    const std::string expected(DEFAULT_CONTENT_TYPE);
    class_under_test.method(DEFAULT_METHOD);

    // Act
    std::string actual = class_under_test.content_type(expected)
                                         .build()
                                         .get_content_type();

    // Assert
    ASSERT_EQ(expected, actual);
}

TEST_F(HttpRequestBuilderTest, AddHeaderBuiltRequestHasHeader) {
    // Arrange
    const std::string expected_name(DEFAULT_HEADER_NAME);
    const std::string expected_value(DEFAULT_HEADER_VALUE);
    class_under_test.method(DEFAULT_METHOD);

    // Act
    HttpRequest request = class_under_test.add_header(expected_name, expected_value)
                                          .build();

    // Assert
    ASSERT_TRUE(request.has_header(expected_name));
    ASSERT_EQ(expected_value, request.get_header_value(expected_name));
}
