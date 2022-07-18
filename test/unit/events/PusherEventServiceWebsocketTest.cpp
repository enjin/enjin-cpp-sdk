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
#include "AssetChannel.hpp"
#include "FakeWebSocketClient.hpp"
#include "MockWebsocketServer.hpp"
#include "ProjectChannel.hpp"
#include "PlayerChannel.hpp"
#include "PusherConstants.hpp"
#include "VerificationTestSuite.hpp"
#include "WalletChannel.hpp"
#include "enjinsdk/PusherEventService.hpp"
#include <memory>
#include <string>
#include <thread>
#include <vector>

using namespace enjin::pusher;
using namespace enjin::sdk::events;
using namespace enjin::sdk::models;
using namespace enjin::test::mocks;
using namespace enjin::test::suites;

class PusherEventServiceWebsocketTest : public VerificationTestSuite,
                                        public testing::Test {
public:
    static constexpr char DefaultProject[] = "1";
    static constexpr char DefaultPlayer[] = "player1";
    static constexpr char DefaultAsset[] = "0x0";
    static constexpr char DefaultWallet[] = "0x1";
    static constexpr char PlatformJson[] =
            R"({"network":"test","notifications":{"pusher":{"key":"1","options":{"cluster":"mt1","encrypted":true}}}})";

    std::unique_ptr<PusherEventService> class_under_test;

    MockWebsocketServer mock_server;

    static Platform create_default_platform() {
        Platform platform;
        platform.deserialize(PlatformJson);
        return platform;
    }

    static std::string create_subscription_success_message(const std::string& channel = "") {
        std::stringstream ss;
        ss << R"({"event":")"
           << PusherConstants::ChannelSubscriptionSucceeded
           << R"(","channel":")"
           << channel
           << R"("})";
        return ss.str();
    }

protected:
    void SetUp() override {
        class_under_test = PusherEventService::builder()
                .ws_client(std::make_unique<FakeWebSocketClient>())
                .platform(create_default_platform())
                .build();
    }

    void TearDown() override {
        class_under_test->shutdown().get();
        mock_server.close(1000, "Teardown");
    }
};

TEST_F(PusherEventServiceWebsocketTest, StartAndShutdownDoNotThrowExceptions) {
    // Assert
    EXPECT_NO_THROW(class_under_test->start().get()) << "Service start threw an error";
    EXPECT_NO_THROW(class_under_test->shutdown().get()) << "Service shutdown threw an error";
}

TEST_F(PusherEventServiceWebsocketTest, IsConnectedServiceNotStartedReturnsFalse) {
    // Act
    const bool actual = class_under_test->is_connected();

    // Assert
    ASSERT_FALSE(actual);
}

TEST_F(PusherEventServiceWebsocketTest, IsConnectedServiceStartedAndConnectedToServerReturnsTrue) {
    // Arrange
    class_under_test->start().get();

    // Act
    const bool actual = class_under_test->is_connected();

    // Assert
    ASSERT_TRUE(actual);
}

TEST_F(PusherEventServiceWebsocketTest, SubscribeToProjectServiceSubscribesToChannel) {
    // Arrange - Data
    const std::string project = DefaultProject;
    const std::string channel = ProjectChannel(create_default_platform(), project).channel();
    mock_server.ignore_message_type(WebsocketMessageType::WebsocketOpenType)
               .ignore_message_type(WebsocketMessageType::WebsocketPingType)
               .ignore_message_type(WebsocketMessageType::WebsocketPongType);
    class_under_test->start().get();

    // Arrange - Expectations
    mock_server.next_message([this, &channel](const TestWebsocketMessage& message) {
        increment_call_counter();
        EXPECT_EQ(WebsocketMessageType::WebsocketUtf8MessageType, message.get_type()) << "Unexpected message type";

        std::string data = create_subscription_success_message(channel);
        TestWebsocketMessage response;
        response.set_data(std::vector<unsigned char>(data.begin(), data.end()));
        response.set_type(WebsocketMessageType::WebsocketUtf8MessageType);
        mock_server.send_message(response);
    });
    set_expected_call_count(1);

    // Assumptions
    ASSERT_FALSE(class_under_test->is_subscribed_to_project(project)) << "Assume not pre-subscribed to channel";

    // Act
    class_under_test->subscribe_to_project(project);

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    // Assert
    EXPECT_TRUE(class_under_test->is_subscribed_to_project(project)) << "Service was not subscribed to channel";

    // Verify
    verify_call_count();
}

TEST_F(PusherEventServiceWebsocketTest, UnsubscribeToProjectServiceIsUnsubscribedFromChannel) {
    // Arrange
    const std::string project = DefaultProject;
    const std::string channel = ProjectChannel(create_default_platform(), project).channel();
    mock_server.ignore_message_type(WebsocketMessageType::WebsocketOpenType)
               .ignore_message_type(WebsocketMessageType::WebsocketPingType)
               .ignore_message_type(WebsocketMessageType::WebsocketPongType);
    class_under_test->start().get();
    mock_server.next_message([this, &channel](const TestWebsocketMessage& message) {
        std::string data = create_subscription_success_message(channel);
        TestWebsocketMessage response;
        response.set_data(std::vector<unsigned char>(data.begin(), data.end()));
        response.set_type(WebsocketMessageType::WebsocketUtf8MessageType);
        mock_server.send_message(response);
    });
    class_under_test->subscribe_to_project(project);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    // Act
    class_under_test->unsubscribe_to_project(project);

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    // Assert
    ASSERT_FALSE(class_under_test->is_subscribed_to_project(project));
}

TEST_F(PusherEventServiceWebsocketTest, SubscribeToPlayerServiceSubscribesToChannel) {
    // Arrange - Data
    const std::string project = DefaultProject;
    const std::string player(DefaultPlayer);
    const std::string channel = PlayerChannel(create_default_platform(), project, player).channel();
    mock_server.ignore_message_type(WebsocketMessageType::WebsocketOpenType)
               .ignore_message_type(WebsocketMessageType::WebsocketPingType)
               .ignore_message_type(WebsocketMessageType::WebsocketPongType);
    class_under_test->start().get();

    // Arrange - Expectations
    mock_server.next_message([this, &channel](const TestWebsocketMessage& message) {
        increment_call_counter();
        EXPECT_EQ(WebsocketMessageType::WebsocketUtf8MessageType, message.get_type()) << "Unexpected message type";

        std::string data = create_subscription_success_message(channel);
        TestWebsocketMessage response;
        response.set_data(std::vector<unsigned char>(data.begin(), data.end()));
        response.set_type(WebsocketMessageType::WebsocketUtf8MessageType);
        mock_server.send_message(response);
    });
    set_expected_call_count(1);

    // Assumptions
    ASSERT_FALSE(class_under_test->is_subscribed_to_player(project, player)) << "Assume not pre-subscribed to channel";

    // Act
    class_under_test->subscribe_to_player(project, player);

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    // Assert
    EXPECT_TRUE(class_under_test->is_subscribed_to_player(project, player)) << "Service was not subscribed to channel";

    // Verify
    verify_call_count();
}

TEST_F(PusherEventServiceWebsocketTest, UnsubscribeToPlayerServiceIsUnsubscribedFromChannel) {
    // Arrange
    const std::string project = DefaultProject;
    const std::string player(DefaultPlayer);
    const std::string channel = PlayerChannel(create_default_platform(), project, player).channel();
    mock_server.ignore_message_type(WebsocketMessageType::WebsocketOpenType)
               .ignore_message_type(WebsocketMessageType::WebsocketPingType)
               .ignore_message_type(WebsocketMessageType::WebsocketPongType);
    class_under_test->start().get();
    mock_server.next_message([this, &channel](const TestWebsocketMessage& message) {
        std::string data = create_subscription_success_message(channel);
        TestWebsocketMessage response;
        response.set_data(std::vector<unsigned char>(data.begin(), data.end()));
        response.set_type(WebsocketMessageType::WebsocketUtf8MessageType);
        mock_server.send_message(response);
    });
    class_under_test->subscribe_to_player(project, player);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    // Act
    class_under_test->unsubscribe_to_player(project, player);

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    // Assert
    ASSERT_FALSE(class_under_test->is_subscribed_to_player(project, player));
}

TEST_F(PusherEventServiceWebsocketTest, SubscribeToAssetServiceSubscribesToChannel) {
    // Arrange - Data
    const std::string asset(DefaultAsset);
    const std::string channel = AssetChannel(create_default_platform(), asset).channel();
    mock_server.ignore_message_type(WebsocketMessageType::WebsocketOpenType)
               .ignore_message_type(WebsocketMessageType::WebsocketPingType)
               .ignore_message_type(WebsocketMessageType::WebsocketPongType);
    class_under_test->start().get();

    // Arrange - Expectations
    mock_server.next_message([this, &channel](const TestWebsocketMessage& message) {
        increment_call_counter();
        EXPECT_EQ(WebsocketMessageType::WebsocketUtf8MessageType, message.get_type()) << "Unexpected message type";

        std::string data = create_subscription_success_message(channel);
        TestWebsocketMessage response;
        response.set_data(std::vector<unsigned char>(data.begin(), data.end()));
        response.set_type(WebsocketMessageType::WebsocketUtf8MessageType);
        mock_server.send_message(response);
    });
    set_expected_call_count(1);

    // Assumptions
    ASSERT_FALSE(class_under_test->is_subscribed_to_asset(asset)) << "Assume not pre-subscribed to channel";

    // Act
    class_under_test->subscribe_to_asset(asset);

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    // Assert
    EXPECT_TRUE(class_under_test->is_subscribed_to_asset(asset)) << "Service was not subscribed to channel";

    // Verify
    verify_call_count();
}

TEST_F(PusherEventServiceWebsocketTest, UnsubscribeToAssetServiceIsUnsubscribedFromChannel) {
    // Arrange
    const std::string asset(DefaultAsset);
    const std::string channel = AssetChannel(create_default_platform(), asset).channel();
    mock_server.ignore_message_type(WebsocketMessageType::WebsocketOpenType)
               .ignore_message_type(WebsocketMessageType::WebsocketPingType)
               .ignore_message_type(WebsocketMessageType::WebsocketPongType);
    class_under_test->start().get();
    mock_server.next_message([this, &channel](const TestWebsocketMessage& message) {
        std::string data = create_subscription_success_message(channel);
        TestWebsocketMessage response;
        response.set_data(std::vector<unsigned char>(data.begin(), data.end()));
        response.set_type(WebsocketMessageType::WebsocketUtf8MessageType);
        mock_server.send_message(response);
    });
    class_under_test->subscribe_to_asset(asset);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    // Act
    class_under_test->unsubscribe_to_asset(asset);

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    // Assert
    ASSERT_FALSE(class_under_test->is_subscribed_to_asset(asset));
}

TEST_F(PusherEventServiceWebsocketTest, SubscribeToWalletServiceSubscribesToChannel) {
    // Arrange - Data
    const std::string wallet(DefaultWallet);
    const std::string channel = WalletChannel(create_default_platform(), wallet).channel();
    mock_server.ignore_message_type(WebsocketMessageType::WebsocketOpenType)
               .ignore_message_type(WebsocketMessageType::WebsocketPingType)
               .ignore_message_type(WebsocketMessageType::WebsocketPongType);
    class_under_test->start().get();

    // Arrange - Expectations
    mock_server.next_message([this, &channel](const TestWebsocketMessage& message) {
        increment_call_counter();
        EXPECT_EQ(WebsocketMessageType::WebsocketUtf8MessageType, message.get_type()) << "Unexpected message type";

        std::string data = create_subscription_success_message(channel);
        TestWebsocketMessage response;
        response.set_data(std::vector<unsigned char>(data.begin(), data.end()));
        response.set_type(WebsocketMessageType::WebsocketUtf8MessageType);
        mock_server.send_message(response);
    });
    set_expected_call_count(1);

    // Assumptions
    ASSERT_FALSE(class_under_test->is_subscribed_to_wallet(wallet)) << "Assume not pre-subscribed to channel";

    // Act
    class_under_test->subscribe_to_wallet(wallet);

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    // Assert
    EXPECT_TRUE(class_under_test->is_subscribed_to_wallet(wallet)) << "Service was not subscribed to channel";

    // Verify
    verify_call_count();
}

TEST_F(PusherEventServiceWebsocketTest, UnsubscribeToWalletServiceIsUnsubscribedFromChannel) {
    // Arrange
    const std::string wallet(DefaultWallet);
    const std::string channel = WalletChannel(create_default_platform(), wallet).channel();
    mock_server.ignore_message_type(WebsocketMessageType::WebsocketOpenType)
               .ignore_message_type(WebsocketMessageType::WebsocketPingType)
               .ignore_message_type(WebsocketMessageType::WebsocketPongType);
    class_under_test->start().get();
    mock_server.next_message([this, &channel](const TestWebsocketMessage& message) {
        std::string data = create_subscription_success_message(channel);
        TestWebsocketMessage response;
        response.set_data(std::vector<unsigned char>(data.begin(), data.end()));
        response.set_type(WebsocketMessageType::WebsocketUtf8MessageType);
        mock_server.send_message(response);
    });
    class_under_test->subscribe_to_wallet(wallet);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    // Act
    class_under_test->unsubscribe_to_wallet(wallet);

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    // Assert
    ASSERT_FALSE(class_under_test->is_subscribed_to_wallet(wallet));
}

TEST_F(PusherEventServiceWebsocketTest, StartPreviouslyActiveServiceResubscribesToChannels) {
    // Arrange - Data & Expectations
    const std::string project = DefaultProject;
    const std::string channel = ProjectChannel(create_default_platform(), project).channel();
    auto subscribe_func = [this, &channel](const TestWebsocketMessage& message) {
        increment_call_counter();
        EXPECT_EQ(WebsocketMessageType::WebsocketUtf8MessageType, message.get_type()) << "Unexpected message type";

        std::string data = create_subscription_success_message(channel);
        TestWebsocketMessage response;
        response.set_data(std::vector<unsigned char>(data.begin(), data.end()));
        response.set_type(WebsocketMessageType::WebsocketUtf8MessageType);
        mock_server.send_message(response);
    };
    mock_server.ignore_message_type(WebsocketMessageType::WebsocketOpenType)
               .ignore_message_type(WebsocketMessageType::WebsocketPingType)
               .ignore_message_type(WebsocketMessageType::WebsocketPongType)
               .ignore_message_type(WebsocketMessageType::WebsocketCloseType);
    mock_server.next_message(subscribe_func); // Expect subscribe messages
    mock_server.next_message(subscribe_func); //
    set_expected_call_count(2);               //
    class_under_test->start().get();                 // Service is started for first time and subscribes to the channel
    class_under_test->subscribe_to_project(project); //
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    class_under_test->shutdown().get(); // Shutdown the service to be restarted on 'Act'

    // Assumptions
    ASSERT_TRUE(class_under_test->is_subscribed_to_project(project)) << "Assume service is pre-subscribed to channel";

    // Act
    class_under_test->start().get();

    // Assert
    EXPECT_TRUE(class_under_test->is_subscribed_to_project(project)) << "Service was not resubscribed to channel";

    // Verify
    verify_call_count();
}
