#include "enjinsdk/TrustedPlatformHandler.hpp"
#include "gtest/gtest.h"
#include <string>

using namespace enjin::sdk::http;

class TrustedPlatformHandlerTest : public testing::Test {
public:
    TrustedPlatformHandler class_under_test;
};

TEST_F(TrustedPlatformHandlerTest, IsAuthenticatedAuthTokenIsNotEmptyOrWhitespaceReturnsTrue) {
    // Arrange
    const std::string auth_token("xyz");
    class_under_test.set_auth_token(auth_token);

    // Act
    bool actual = class_under_test.is_authenticated();

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(TrustedPlatformHandlerTest, IsAuthenticatedAuthTokenIsNotSetReturnsFalse) {
    // Act
    bool actual = class_under_test.is_authenticated();

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(TrustedPlatformHandlerTest, IsAuthenticatedAuthTokenIsEmptyReturnsFalse) {
    // Arrange
    const std::string auth_token;
    class_under_test.set_auth_token(auth_token);

    // Act
    bool actual = class_under_test.is_authenticated();

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(TrustedPlatformHandlerTest, IsAuthenticatedAuthTokenIsWhitespaceReturnsFalse) {
    // Arrange
    const std::string auth_token(" ");
    class_under_test.set_auth_token(auth_token);

    // Act
    bool actual = class_under_test.is_authenticated();

    // Assert
    ASSERT_FALSE(actual);
}
