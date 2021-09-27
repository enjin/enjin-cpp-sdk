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

#include "MockWebsocketServer.hpp"

#include "ixwebsocket/IXNetSystem.h"
#include "ixwebsocket/IXWebSocketServer.h"
#include <algorithm>
#include <mutex>
#include <queue>
#include <set>
#include <stdexcept>

#define WEBSOCKET_TEST_SERVER_PORT 8080

namespace enjin::test::mocks {

const std::vector<unsigned char>& TestWebsocketMessage::get_data() const {
    return data;
}

WebsocketMessageType TestWebsocketMessage::get_type() const {
    return type;
}

void TestWebsocketMessage::set_data(std::vector<unsigned char> data) {
    TestWebsocketMessage::data = data;
}

void TestWebsocketMessage::set_type(WebsocketMessageType type) {
    TestWebsocketMessage::type = type;
}

class MockWebsocketServer::Impl {
public:
    Impl() = delete;

    explicit Impl(MockWebsocketServer* mock_server) : mock_server(mock_server) {
        connect();
    }

    ~Impl() {
        stop("Destructor");
    }

    void connect() {
#ifdef WIN32
        ix::initNetSystem();
#endif

        server.setOnClientMessageCallback([this](const std::shared_ptr<ix::ConnectionState>& connection_state,
                                                 ix::WebSocket& ws,
                                                 const ix::WebSocketMessagePtr& msg) {
            switch (msg->type) {
                case ix::WebSocketMessageType::Open:
                    handle_open();
                    break;
                case ix::WebSocketMessageType::Close:
                    handle_close();
                    break;
                case ix::WebSocketMessageType::Message:
                    handle_message(msg);
                    break;
                default:
                    break;
            }
        });

        auto res = server.listen();
        if (!res.first) {
            throw std::runtime_error(res.second);
        }

        server.start();
    }

    void close() {
        close(ix::WebSocketCloseConstants::kNormalClosureCode, ix::WebSocketCloseConstants::kNormalClosureMessage);
    }

    void close(const std::string& reason) {
        close(ix::WebSocketCloseConstants::kNormalClosureCode, reason);
    }

    void close(uint16_t code, const std::string& reason) {
        auto clients = server.getClients();
        std::for_each(clients.begin(),
                      clients.end(),
                      [code, reason](const std::shared_ptr<ix::WebSocket>& c) {
                          c->close(code, reason);
                      });
    }

    void stop() {
        stop(ix::WebSocketCloseConstants::kNormalClosureCode, ix::WebSocketCloseConstants::kNormalClosureMessage);
    }

    void stop(const std::string& reason) {
        stop(ix::WebSocketCloseConstants::kNormalClosureCode, reason);
    }

    void stop(uint16_t code, const std::string& reason) {
        close(code, reason);
        server.stop();
    }

    void ignore_message_type(WebsocketMessageType type) {
        ignored_types.emplace(type);
    }

    void next_message(const std::function<void(TestWebsocketMessage)>& handler) {
        std::lock_guard<std::mutex> guard(message_handlers_lock);

        if (has_unhandled_messages()) {
            handler(get_unhandled_message());
        } else {
            message_handlers.push(handler);
        }
    }

    void send_message(const TestWebsocketMessage& message) {
        std::string data(message.get_data().begin(), message.get_data().end());

        auto clients = server.getClients();
        switch (message.get_type()) {
            case WebsocketMessageType::WEBSOCKET_BINARY_MESSAGE_TYPE:
                std::for_each(clients.begin(),
                              clients.end(),
                              [data](const std::shared_ptr<ix::WebSocket>& c) {
                                  c->sendBinary(data);
                              });
                break;
            case WebsocketMessageType::WEBSOCKET_UTF8_MESSAGE_TYPE:
                std::for_each(clients.begin(),
                              clients.end(),
                              [data](const std::shared_ptr<ix::WebSocket>& c) {
                                  c->sendText(data);
                              });
                break;
            case WebsocketMessageType::WEBSOCKET_CLOSE_TYPE:
                close(data);
                break;
            case WebsocketMessageType::WEBSOCKET_PING_TYPE:
            case WebsocketMessageType::WEBSOCKET_PONG_TYPE:
            case WebsocketMessageType::WEBSOCKET_BINARY_FRAGMENT_TYPE:
            case WebsocketMessageType::WEBSOCKET_UTF8_FRAGMENT_TYPE:
                throw std::runtime_error("Invalid websocket message type");
            default:
                throw std::runtime_error("Unknown websocket message type");
        }
    }

    bool is_type_ignored(WebsocketMessageType type) {
        return ignored_types.find(type) != ignored_types.end();
    }

    std::function<void(TestWebsocketMessage)> get_next_message_handler() {
        std::lock_guard<std::mutex> guard(message_handlers_lock);

        if (message_handlers.empty()) {
            return std::function<void(TestWebsocketMessage)>();
        }

        auto handler = message_handlers.front();
        message_handlers.pop();

        return handler;
    }

private:
    MockWebsocketServer* mock_server;

    /* Note: The destructor for ixwebsocket's ix::WebSocketServer causes a double free to take place in its latest
     * version (v11.0.4) at the time of this note was written.
     */
    ix::WebSocketServer server = ix::WebSocketServer(WEBSOCKET_TEST_SERVER_PORT);
    std::queue<TestWebsocketMessage> unhandled_message_queue;
    std::queue<std::function<void(TestWebsocketMessage)>> message_handlers;
    std::set<WebsocketMessageType> ignored_types;

    std::mutex message_handlers_lock;
    std::mutex unhandled_message_queue_mutex;

    bool should_handle_type(WebsocketMessageType type) {
        return !mock_server->is_type_ignored(type);
    }

    void push_unhandled_message(const TestWebsocketMessage& ws_message) {
        std::lock_guard<std::mutex> guard(unhandled_message_queue_mutex);

        unhandled_message_queue.push(ws_message);
    }

    void handle_open() {
        TestWebsocketMessage ws_message;
        ws_message.set_type(WebsocketMessageType::WEBSOCKET_OPEN_TYPE);

        if (!should_handle_type(ws_message.get_type())) {
            return;
        }

        auto handler = mock_server->get_next_message_handler();
        if (handler) {
            handler(ws_message);
        } else {
            push_unhandled_message(ws_message);
        }
    }

    void handle_close() {
        TestWebsocketMessage ws_message;
        ws_message.set_type(WebsocketMessageType::WEBSOCKET_CLOSE_TYPE);

        if (!should_handle_type(ws_message.get_type())) {
            return;
        }

        auto handler = mock_server->get_next_message_handler();
        if (handler) {
            handler(ws_message);
        } else {
            push_unhandled_message(ws_message);
        }
    }

    void handle_message(const ix::WebSocketMessagePtr& msg) {
        TestWebsocketMessage ws_message;
        ws_message.set_data(std::vector<uint8_t>(msg->str.begin(), msg->str.end()));

        if (msg->binary) {
            ws_message.set_type(WebsocketMessageType::WEBSOCKET_BINARY_MESSAGE_TYPE);
        } else {
            ws_message.set_type(WebsocketMessageType::WEBSOCKET_UTF8_MESSAGE_TYPE);
        }

        if (!should_handle_type(ws_message.get_type())) {
            return;
        }

        auto handler = mock_server->get_next_message_handler();
        if (handler) {
            handler(ws_message);
        } else {
            push_unhandled_message(ws_message);
        }
    }

    bool has_unhandled_messages() {
        return !unhandled_message_queue.empty();
    }

    TestWebsocketMessage get_unhandled_message() {
        std::lock_guard<std::mutex> guard(unhandled_message_queue_mutex);

        TestWebsocketMessage ws_message = unhandled_message_queue.front();
        unhandled_message_queue.pop();

        return ws_message;
    }
};

MockWebsocketServer::MockWebsocketServer() : impl(new Impl(this)) {
}

MockWebsocketServer::~MockWebsocketServer() {
    delete impl;
}

void MockWebsocketServer::next_message(const std::function<void(TestWebsocketMessage)>& handler) {
    impl->next_message(handler);
}

MockWebsocketServer& MockWebsocketServer::ignore_message_type(WebsocketMessageType type) {
    impl->ignore_message_type(type);
    return *this;
}

std::function<void(TestWebsocketMessage)> MockWebsocketServer::get_next_message_handler() {
    return impl->get_next_message_handler();
}

void MockWebsocketServer::send_message(const TestWebsocketMessage& message) {
    impl->send_message(message);
}

void MockWebsocketServer::close() {
    impl->close();
}

void MockWebsocketServer::close(int code, const std::string& reason) {
    impl->close(code, reason);
}

void MockWebsocketServer::stop() {
    impl->stop();
}

void MockWebsocketServer::stop(int code, const std::string& reason) {
    impl->stop(code, reason);
}

bool MockWebsocketServer::is_type_ignored(WebsocketMessageType type) {
    return impl->is_type_ignored(type);
}

}
