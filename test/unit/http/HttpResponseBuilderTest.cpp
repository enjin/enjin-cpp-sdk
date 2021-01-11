#include "enjinsdk/HttpResponse.hpp"
#include "gtest/gtest.h"
#include <string>

using namespace enjin::sdk::http;

class HttpResponseBuilderTest : public testing::Test {
public:
    HttpResponseBuilder class_under_test;
};

TEST_F(HttpResponseBuilderTest, BuildDoesNotThrowException) {
    // Arrange
    ASSERT_NO_THROW(class_under_test.build());
}

TEST_F(HttpResponseBuilderTest, BuildNoSetValuesBuiltRequestIsEmpty) {
    // Act
    HttpResponse actual = class_under_test.build();

    // Arrange
    EXPECT_FALSE(actual.get_body().has_value());
    EXPECT_FALSE(actual.get_content_type().has_value());
}

TEST_F(HttpResponseBuilderTest, CodeValueIsSetBuiltRequestHasExpectedValue) {
    // Arrange
    const uint16_t expected = 100;

    // Act
    uint16_t actual = class_under_test.code(expected)
                                      .build()
                                      .get_code()
                                      .value();

    // Arrange
    ASSERT_EQ(expected, actual);
}

TEST_F(HttpResponseBuilderTest, BodyValueIsSetBuiltRequestHasExpectedValue) {
    // Arrange
    const std::string expected("expected");

    // Act
    std::string actual = class_under_test.body(expected)
                                         .build()
                                         .get_body()
                                         .value();

    // Arrange
    ASSERT_EQ(expected, actual);
}

TEST_F(HttpResponseBuilderTest, ContentTypeValueIsSetBuiltRequestHasExpectedValue) {
    // Arrange
    const std::string expected("expected");

    // Act
    std::string actual = class_under_test.content_type(expected)
                                         .build()
                                         .get_content_type()
                                         .value();

    // Arrange
    ASSERT_EQ(expected, actual);
}
