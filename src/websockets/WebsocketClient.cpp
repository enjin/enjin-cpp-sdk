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

#include "WebsocketClient.hpp"

#include "ixwebsocket/IXWebSocket.h"
#include <condition_variable>
#include <mutex>
#include <optional>
#include <stdexcept>

#ifdef WIN32
#include "ixwebsocket/IXNetSystem.h"
#endif

namespace enjin::sdk::websockets {

class WebsocketClient::Impl : public IWebsocketClient {
public:
    Impl() {
#ifdef WIN32
        ix::initNetSystem();
#endif

        ws.enablePong();
        ws.setPingInterval(120); // Ping every 2 minutes
        ws.disableAutomaticReconnection();

        ws.setOnMessageCallback([this](const ix::WebSocketMessagePtr& msg) {
            std::lock_guard<std::mutex> guard(handler_mutex);

            ix::WebSocketMessageType type = msg->type;
            if (type == ix::WebSocketMessageType::Message && message_handler.has_value()) {
                message_handler.value()(msg->str);
            } else if (type == ix::WebSocketMessageType::Open) {
                open_message_received();

                if (open_handler.has_value()) {
                    open_handler.value()();
                }
            } else if (type == ix::WebSocketMessageType::Close && close_handler.has_value()) {
                close_handler.value()(msg->closeInfo.code, msg->closeInfo.reason);
            } else if (type == ix::WebSocketMessageType::Error) {
                error_message_received(msg);

                if (error_handler.has_value()) {
                    error_handler.value()(msg->errorInfo.http_status, msg->errorInfo.reason);
                }
            }
        });
    }

    ~Impl() override {
        Impl::close().get();

        // TODO: Uninitialize in a smarter way if possible.
#ifdef WIN32
        ix::uninitNetSystem();
#endif
    }

    std::future<void> connect(const std::string& uri) override {
        std::lock_guard<std::mutex> guard(conn_mutex);

        if (conn_status == ConnectionStatus::CONNECTED) {
            return std::async([]() {});
        }

        conn_status = ConnectionStatus::CONNECTING;

        return std::async([this, uri]() {
            ws.setUrl(uri);
            ws.start();

            std::unique_lock<std::mutex> lock(conn_mutex);

            while (conn_status == ConnectionStatus::CONNECTING) {
                conn_cv.wait(lock, [&]() {
                    if (conn_error_info.has_value()) {
                        auto error_info = conn_error_info.value();
                        conn_error_info.reset();
                        throw create_connection_exception(error_info);
                    }

                    return conn_status != ConnectionStatus::CONNECTING;
                });
            }
        });
    }

    std::future<void> close() override {
        return close(ix::WebSocketCloseConstants::kNormalClosureCode,
                     ix::WebSocketCloseConstants::kNormalClosureMessage);
    }

    std::future<void> close(int status_code, const std::string& reason) override {
        std::lock_guard<std::mutex> guard(conn_mutex);

        if (conn_status == ConnectionStatus::DISCONNECTED) {
            return std::async([]() {});
        }

        conn_status = ConnectionStatus::DISCONNECTING;

        return std::async([this, status_code, reason]() {
            ws.stop(status_code, reason);
        });
    }

    void send(const std::string& data) override {
        ws.sendText(data);
    }

    void set_open_handler(const std::function<void()>& handler) override {
        std::lock_guard<std::mutex> guard(handler_mutex);
        open_handler = handler;
    }

    void set_close_handler(const std::function<void(int close_status, const std::string& message)>& handler) override {
        std::lock_guard<std::mutex> guard(handler_mutex);
        close_handler = handler;
    }

    void set_message_handler(const std::function<void(const std::string& message)>& handler) override {
        std::lock_guard<std::mutex> guard(handler_mutex);
        message_handler = handler;
    }

    void set_error_handler(const std::function<void(int code, const std::string& message)>& handler) override {
        std::lock_guard<std::mutex> guard(handler_mutex);
        error_handler = handler;
    }

    void set_allow_reconnecting(bool allow) override {
        if (allow) {
            ws.enableAutomaticReconnection();
        } else {
            ws.disableAutomaticReconnection();
        }
    }

    void set_allowed_reconnect_attempts(unsigned int allowed_attempts) override {
        std::lock_guard<std::mutex> guard(conn_mutex);
        Impl::allowed_attempts = allowed_attempts;
    }

private:
    enum class ConnectionStatus {
        CONNECTED,
        CONNECTING,
        DISCONNECTED,
        DISCONNECTING,
    };

    ix::WebSocket ws;
    ConnectionStatus conn_status = ConnectionStatus::DISCONNECTED;
    unsigned int allowed_attempts = 0;

    std::optional<std::function<void()>> open_handler;
    std::optional<std::function<void(int, const std::string&)>> close_handler;
    std::optional<std::function<void(const std::string&)>> message_handler;
    std::optional<std::function<void(int code, const std::string& message)>> error_handler;

    std::condition_variable conn_cv;
    std::optional<ix::WebSocketErrorInfo> conn_error_info;

    // Mutexes
    mutable std::mutex conn_mutex;
    mutable std::mutex handler_mutex;

    void open_message_received() {
        std::lock_guard<std::mutex> guard(conn_mutex);

        if (conn_status == ConnectionStatus::CONNECTED) {
            return;
        }

        conn_status = ConnectionStatus::CONNECTED;
        conn_cv.notify_all();
    }

    void error_message_received(const ix::WebSocketMessagePtr& msg) {
        std::unique_lock<std::mutex> conn_lock(conn_mutex);

        auto error_info = msg->errorInfo;
        if (conn_status != ConnectionStatus::CONNECTING || msg->errorInfo.retries - 1 < allowed_attempts) {
            return;
        }

        ws.close(ix::WebSocketCloseConstants::kAbnormalCloseCode, ix::WebSocketCloseConstants::kAbnormalCloseMessage);
        conn_status = ConnectionStatus::DISCONNECTED;
        conn_error_info = msg->errorInfo;
        conn_cv.notify_all();
        conn_lock.unlock();

        if (close_handler.has_value()) {
            close_handler.value()(error_info.http_status, error_info.reason);
        }
    }

    static std::runtime_error create_connection_exception(const ix::WebSocketErrorInfo& error_info) {
        return std::runtime_error(error_info.reason);
    }
};

WebsocketClient::WebsocketClient() : impl(new Impl()) {
}

WebsocketClient::~WebsocketClient() {
    delete impl;
}

std::future<void> WebsocketClient::connect(const std::string& uri) {
    return impl->connect(uri);
}

std::future<void> WebsocketClient::close() {
    return impl->close();
}

std::future<void> WebsocketClient::close(int status_code, const std::string& reason) {
    return impl->close(status_code, reason);
}

void WebsocketClient::send(const std::string& data) {
    impl->send(data);
}

void WebsocketClient::set_open_handler(const std::function<void()>& handler) {
    impl->set_open_handler(handler);
}

void WebsocketClient::set_close_handler(const std::function<void(int, const std::string&)>& handler) {
    impl->set_close_handler(handler);
}

void WebsocketClient::set_message_handler(const std::function<void(const std::string& message)>& handler) {
    impl->set_message_handler(handler);
}

void WebsocketClient::set_error_handler(const std::function<void(int code, const std::string& message)>& handler) {
    impl->set_error_handler(handler);
}

void WebsocketClient::set_allow_reconnecting(bool allow) {
    impl->set_allow_reconnecting(allow);
}

void WebsocketClient::set_allowed_reconnect_attempts(unsigned int allowed_attempts) {
    impl->set_allowed_reconnect_attempts(allowed_attempts);
}

}
