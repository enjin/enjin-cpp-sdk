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
#include "PusherClientTestSuite.hpp"
#include "VerificationTestSuite.hpp"
#include <chrono>
#include <string>
#include <thread>

using namespace enjin::pusher;
using namespace enjin::test::mocks;
using namespace enjin::test::suites;

/* TODO: These tests tend to not work on GitHub's Ubuntu test runner. The reason why needs to be figured out and fixed.
 */
class PusherClientReconnectTest : public PusherClientTestSuite,
                                  public VerificationTestSuite,
                                  public testing::Test {
protected:
    void SetUp() override {
        mock_server.ignore_message_type(WebsocketMessageType::WebsocketCloseType)
                   .ignore_message_type(WebsocketMessageType::WebsocketPingType)
                   .ignore_message_type(WebsocketMessageType::WebsocketPongType);
    }
};

TEST_F(PusherClientReconnectTest, ReceivesGenericClosingCodeAndReconnectToServer) {
    // Arrange - Data
    const int status_code = 1000;
    const std::string reason("Test closure");
    PusherClient client = create_testable_pusher_client();
    client.connect().get();
    mock_server.next_message([](const TestWebsocketMessage& message) { /* Consumes initial open message */ });

    // Arrange - Expectations
    mock_server.next_message([this](const TestWebsocketMessage& message) {
        increment_call_counter();
        EXPECT_EQ(WebsocketMessageType::WebsocketOpenType, message.get_type());
    });
    set_expected_call_count(1);

    // Act
    mock_server.close(status_code, reason);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    // Verify
    verify_call_count();

    // Assert
    EXPECT_EQ(PusherConnectionState::Connected, client.get_state());
}

TEST_F(PusherClientReconnectTest, ReceivesPusherClosingCodeDoesNotReconnectToServer) {
    // Arrange - Data
    const int status_code = 4000;
    const std::string reason("Test closure");
    PusherClient client = create_testable_pusher_client();
    client.connect().get();
    mock_server.next_message([](const TestWebsocketMessage& message) { /* Consumes initial open message */ });

    // Arrange - Expectations
    mock_server.next_message([this](const TestWebsocketMessage& message) {
        increment_call_counter();
        EXPECT_EQ(WebsocketMessageType::WebsocketOpenType, message.get_type());
    });
    set_expected_call_count(0);

    // Act
    mock_server.close(status_code, reason);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    // Verify
    verify_call_count();

    // Assert
    EXPECT_EQ(PusherConnectionState::Disconnected, client.get_state());
}
