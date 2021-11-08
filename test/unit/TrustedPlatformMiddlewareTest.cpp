/* Copyright 2021 Enjin Pte. Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "gtest/gtest.h"
#include "enjinsdk/TrustedPlatformMiddleware.hpp"
#include "MockHttpClient.hpp"
#include <memory>
#include <utility>

using namespace enjin::sdk;
using namespace enjin::sdk::http;
using namespace enjin::test::mocks;
using ::testing::NiceMock;
using ::testing::Return;

class TrustedPlatformMiddlewareTest : public ::testing::Test {
public:
    static TrustedPlatformMiddleware create_default_middleware() {
        return TrustedPlatformMiddleware(std::make_unique<NiceMock<MockHttpClient>>());
    }
};

TEST_F(TrustedPlatformMiddlewareTest, IsClosedHttpClientIsNotOpenReturnsTrue) {
    // Arrange - Data
    auto middleware = create_default_middleware();
    auto& client = dynamic_cast<NiceMock<MockHttpClient>&>(*middleware.get_client());

    // Arrange - Expectations
    EXPECT_CALL(client, is_open()).WillOnce(Return(false));

    // Act
    bool actual = middleware.is_closed();

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(TrustedPlatformMiddlewareTest, IsClosedHttpClientIsOpenReturnsFalse) {
    // Arrange - Data
    auto middleware = create_default_middleware();
    auto& client = dynamic_cast<NiceMock<MockHttpClient>&>(*middleware.get_client());

    // Arrange - Expectations
    EXPECT_CALL(client, is_open()).WillOnce(Return(true));

    // Act
    bool actual = middleware.is_closed();

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(TrustedPlatformMiddlewareTest, IsClosedAfterMoveReturnsTrue) {
    // Arrange
    auto middleware = create_default_middleware();
    auto other = std::move(middleware);

    // Act
    bool actual = middleware.is_closed();

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(TrustedPlatformMiddlewareTest, CloseAfterMoveDoesNotFail) {
    // Arrange
    auto middleware = create_default_middleware();
    auto other = std::move(middleware);

    // Assert
    ASSERT_NO_FATAL_FAILURE(middleware.close());
}
