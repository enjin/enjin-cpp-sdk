#include "DummyObject.hpp"
#include "JsonTestSuite.hpp"
#include "gtest/gtest.h"
#include "enjinsdk/HttpResponse.hpp"

using namespace enjin::sdk::http;
using namespace enjin::test::suites;
using namespace enjin::test::utils;

class HttpResponseTest : public JsonTestSuite,
                         public testing::Test {
};

class HttpResponseStatusCodeFailed100To199Test : public testing::TestWithParam<int> {
};

class HttpResponseStatusCodeSuccess200To299Test : public testing::TestWithParam<int> {
};

class HttpResponseStatusCodeFailed300To599Test : public testing::TestWithParam<int> {
};

TEST_P(HttpResponseStatusCodeSuccess200To299Test, IsSuccessGiven200To299ReturnsTrue) {
    // Arrange
    HttpResponse response = HttpResponseBuilder()
            .code(GetParam())
            .build();

    // Act
    bool actual = response.is_success();

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(HttpResponseTest, IsSuccessDoesNotHaveCodeReturnsFalse) {
    // Arrange
    HttpResponse response = HttpResponseBuilder().build();

    // Act
    bool actual = response.is_success();

    // Assert
    EXPECT_FALSE(response.get_code().has_value());
    ASSERT_FALSE(actual);
}

TEST_P(HttpResponseStatusCodeFailed100To199Test, IsSuccessGiven100To199ReturnsFalse) {
    // Arrange
    HttpResponse response = HttpResponseBuilder()
            .code(GetParam())
            .build();

    // Act
    bool actual = response.is_success();

    // Assert
    ASSERT_FALSE(actual);
}

TEST_P(HttpResponseStatusCodeFailed300To599Test, IsSuccessGiven300To599ReturnsFalse) {
    // Arrange
    HttpResponse response = HttpResponseBuilder()
            .code(GetParam())
            .build();

    // Act
    bool actual = response.is_success();

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(HttpResponseTest, IsEmptyDoesNotHaveBodyReturnsTrue) {
    // Arrange
    HttpResponse response = HttpResponseBuilder().build();

    // Act
    bool actual = response.is_empty();

    // Assert
    EXPECT_TRUE(!response.get_body().has_value());
    ASSERT_TRUE(actual);
}

TEST_F(HttpResponseTest, IsEmptyBodyIsEmptyStringReturnsTrue) {
    // Arrange
    HttpResponse response = HttpResponseBuilder().build();

    // Act
    bool actual = response.is_empty();

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(HttpResponseTest, IsEmptyBodyIsEmptyJsonObjectReturnsTrue) {
    // Arrange
    HttpResponse response = HttpResponseBuilder()
            .body(EMPTY_JSON_OBJECT)
            .build();

    // Act
    bool actual = response.is_empty();

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(HttpResponseTest, IsEmptyBodyIsPopulatedJsonObjectReturnsFalse) {
    // Arrange
    DummyObject dummy_object = DummyObject::create_default_dummy_object();
    HttpResponse response = HttpResponseBuilder()
            .body(dummy_object.serialize())
            .build();

    // Act
    bool actual = response.is_empty();

    // Assert
    ASSERT_FALSE(actual);
}

INSTANTIATE_TEST_SUITE_P(IsSuccess,
                         HttpResponseStatusCodeFailed100To199Test,
                         testing::Range(100, 200));

INSTANTIATE_TEST_SUITE_P(IsSuccess,
                         HttpResponseStatusCodeSuccess200To299Test,
                         testing::Range(200, 300));

INSTANTIATE_TEST_SUITE_P(IsSuccess,
                         HttpResponseStatusCodeFailed300To599Test,
                         testing::Range(300, 600));
