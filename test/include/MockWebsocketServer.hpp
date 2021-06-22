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

class TestWebsocketMessage {
public:
    TestWebsocketMessage() = default;

    ~TestWebsocketMessage() = default;

    [[nodiscard]] const std::vector<unsigned char>& get_data() const;

    [[nodiscard]] WebsocketMessageType get_type() const;

    void set_data(std::vector<unsigned char> data);

    void set_type(WebsocketMessageType type);

private:
    std::vector<unsigned char> data;
    WebsocketMessageType type = WebsocketMessageType::UNKNOWN;
};

class MockWebsocketServerImpl;

class MockWebsocketServer {
public:
    MockWebsocketServer();

    ~MockWebsocketServer() = default;

    void next_message(const std::function<void(TestWebsocketMessage)>& handler);

    MockWebsocketServer& ignore_message_type(WebsocketMessageType type);

    std::function<void(TestWebsocketMessage)> get_next_message_handler();

    void send_message(const TestWebsocketMessage& message);

    void close();

    void close(int code, const std::string& reason);

    void stop();

    void stop(int code, const std::string& reason);

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
