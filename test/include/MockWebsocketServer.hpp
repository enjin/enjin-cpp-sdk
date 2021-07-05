/* Copyright 2021 Enjin Pte Ltd.
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

#ifndef ENJINSDK_INCLUDE_WEBSOCKET_CLIENT_IMPL
#define ENJINSDK_INCLUDE_WEBSOCKET_CLIENT_IMPL 0
#endif
#if ENJINSDK_INCLUDE_WEBSOCKET_CLIENT_IMPL

#ifndef ENJINCPPSDK_MOCKWEBSOCKETSERVER_HPP
#define ENJINCPPSDK_MOCKWEBSOCKETSERVER_HPP

#include <functional>
#include <memory>
#include <mutex>
#include <queue>
#include <set>
#include <string>
#include <vector>

namespace enjin::test::mocks {

/// \brief Enums representing the type of websocket message being sent or received.
enum class WebsocketMessageType {
    UNKNOWN,
    WEBSOCKET_BINARY_MESSAGE_TYPE,
    WEBSOCKET_BINARY_FRAGMENT_TYPE,
    WEBSOCKET_UTF8_MESSAGE_TYPE,
    WEBSOCKET_UTF8_FRAGMENT_TYPE,
    WEBSOCKET_CLOSE_TYPE,
    WEBSOCKET_OPEN_TYPE,
    WEBSOCKET_PING_TYPE,
    WEBSOCKET_PONG_TYPE,
};

/// \brief A websocket message used for testing.
class TestWebsocketMessage {
public:
    /// \brief Default constructor.
    TestWebsocketMessage() = default;

    /// \brief Default destructor.
    ~TestWebsocketMessage() = default;

    /// \brief Gets the raw data of this message.
    /// \return The data.
    [[nodiscard]] const std::vector<unsigned char>& get_data() const;

    /// \brief Gets the type of this message.
    /// \return The message type.
    [[nodiscard]] WebsocketMessageType get_type() const;

    /// \brief Sets the raw data for this message.
    /// \param data The data.
    void set_data(std::vector<unsigned char> data);

    /// \brief Sets the type of this message.
    /// \param type The message type.
    void set_type(WebsocketMessageType type);

private:
    std::vector<unsigned char> data;
    WebsocketMessageType type = WebsocketMessageType::UNKNOWN;
};

/// \brief Implementation class of the MockWebsocketServer used internally.
class MockWebsocketServerImpl;

/// \brief A mock websocket server used for testing websocket messages.
class MockWebsocketServer {
public:
    /// \brief Sole constructor.
    MockWebsocketServer();

    /// \brief Default destructor.
    ~MockWebsocketServer() = default;

    /// \brief Setup a handler for the next message received by this server. Intended for use establishing expectations.
    /// \param handler The message handler.
    /// \remarks If this server has already received a message that has not been handled yet, then the given handler
    /// will be applied to that message.
    void next_message(const std::function<void(TestWebsocketMessage)>& handler);

    /// \brief Sets the server up to ignore a given message type.
    /// \param type The message type.
    /// \return This server for chaining.
    MockWebsocketServer& ignore_message_type(WebsocketMessageType type);

    /// \brief Gets the next message handler from a queue.
    /// \return The message handler.
    std::function<void(TestWebsocketMessage)> get_next_message_handler();

    /// \brief Sends a websocket message to connected clients.
    /// \param message The websocket message.
    void send_message(const TestWebsocketMessage& message);

    /// \brief Closes the connection with all connected clients.
    void close();

    /// \brief Closes the connection with all connected clients with the given status code and close message.
    /// \param code The status code for closing.
    /// \param reason The reason for the closure.
    void close(int code, const std::string& reason);

    /// \brief Closes the connection with all connected clients and stops this server.
    void stop();

    /// \brief Closes the connection with all connected clients with the given status code and close message and stops
    /// this server.
    /// \param code The status code for closing.
    /// \param reason The reason for the closure.
    void stop(int code, const std::string& reason);

    /// \brief Determines if the given message type is ignored by this server.
    /// \param type The message type.
    /// \return Whether the message type is ignored by this server.
    bool is_type_ignored(WebsocketMessageType type);

private:
    std::mutex message_handlers_lock;
    std::queue<std::function<void(TestWebsocketMessage)>> message_handlers;
    std::set<WebsocketMessageType> ignored_types;

    std::shared_ptr<MockWebsocketServerImpl> impl;
};

}

#endif //ENJINCPPSDK_MOCKWEBSOCKETSERVER_HPP
#endif
