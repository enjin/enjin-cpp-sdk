#include "../../utils/DummyObject.hpp"
#include "gtest/gtest.h"
#include "enjinsdk/HttpResponse.hpp"

using namespace enjin::sdk::http;

class HttpResponseTest : public testing::Test {
public:
    constexpr static char EMPTY_JSON_OBJECT[] = "{}";
};

class HttpResponseStatusCodeFailed100To199Test : public testing::TestWithParam<int> {
};

class HttpResponseStatusCodeSuccess200To299Test : public testing::TestWithParam<int> {
};

class HttpResponseStatusCodeFailed300To599Test : public testing::TestWithParam<int> {
};

TEST_P(HttpResponseStatusCodeSuccess200To299Test, IsSuccessGiven200To299ReturnsTrue) {
    // Arrange
    HttpResponse response(GetParam(), "");

    // Act
    bool actual = response.is_success();

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(HttpResponseTest, IsSuccessDoesNotHaveCodeReturnsFalse) {
    // Arrange
    HttpResponse response;

    // Act
    bool actual = response.is_success();

    // Assert
    EXPECT_TRUE(!response.get_code().has_value());
    ASSERT_FALSE(actual);
}

TEST_P(HttpResponseStatusCodeFailed100To199Test, IsSuccessGiven100To199ReturnsFalse) {
    // Arrange
    HttpResponse response(GetParam(), "");

    // Act
    bool actual = response.is_success();

    // Assert
    ASSERT_FALSE(actual);
}

TEST_P(HttpResponseStatusCodeFailed300To599Test, IsSuccessGiven300To599ReturnsFalse) {
    // Arrange
    HttpResponse response(GetParam(), "");

    // Act
    bool actual = response.is_success();

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(HttpResponseTest, IsEmptyDoesNotHaveBodyReturnsTrue) {
    // Arrange
    HttpResponse response;

    // Act
    bool actual = response.is_empty();

    // Assert
    EXPECT_TRUE(!response.get_body().has_value());
    ASSERT_TRUE(actual);
}

TEST_F(HttpResponseTest, IsEmptyBodyIsEmptyStringReturnsTrue) {
    // Arrange
    HttpResponse response(0, "");

    // Act
    bool actual = response.is_empty();

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(HttpResponseTest, IsEmptyBodyIsEmptyJsonObjectReturnsTrue) {
    // Arrange
    HttpResponse response(0, EMPTY_JSON_OBJECT);

    // Act
    bool actual = response.is_empty();

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(HttpResponseTest, IsEmptyBodyIsPopulatedJsonObjectReturnsFalse) {
    // Arrange
    enjin::test::utils::DummyObject dummy_object = enjin::test::utils::DummyObject::create_default_dummy_object();
    HttpResponse response(0, dummy_object.serialize());

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
