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

#include "WebsocketClientImpl.hpp"

#ifdef WIN32
#include "ixwebsocket/IXNetSystem.h"
#endif

namespace enjin::sdk::websockets {

std::runtime_error create_connection_exception(const ix::WebSocketErrorInfo& error_info) {
    return std::runtime_error(error_info.reason);
}

WebsocketClientImpl::WebsocketClientImpl() {
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

WebsocketClientImpl::~WebsocketClientImpl() {
    WebsocketClientImpl::close().get();

    // TODO: Uninitialize in a smarter way if possible.
#ifdef WIN32
    ix::uninitNetSystem();
#endif
}

std::future<void> WebsocketClientImpl::connect(const std::string& uri) {
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

std::future<void> WebsocketClientImpl::close() {
    return close(ix::WebSocketCloseConstants::kNormalClosureCode, ix::WebSocketCloseConstants::kNormalClosureMessage);
}

std::future<void> WebsocketClientImpl::close(int status_code, const std::string& reason) {
    std::lock_guard<std::mutex> guard(conn_mutex);

    if (conn_status == ConnectionStatus::DISCONNECTED) {
        return std::async([]() {});
    }

    conn_status = ConnectionStatus::DISCONNECTING;

    return std::async([this, status_code, reason]() {
        ws.stop(status_code, reason);
    });
}

void WebsocketClientImpl::send(const std::string& data) {
    ws.sendText(data);
}

void WebsocketClientImpl::set_open_handler(const std::function<void()>& handler) {
    std::lock_guard<std::mutex> guard(handler_mutex);
    open_handler = handler;
}

void WebsocketClientImpl::set_close_handler(const std::function<void(int, const std::string&)>& handler) {
    std::lock_guard<std::mutex> guard(handler_mutex);
    close_handler = handler;
}

void WebsocketClientImpl::set_message_handler(const std::function<void(const std::string& message)>& handler) {
    std::lock_guard<std::mutex> guard(handler_mutex);
    message_handler = handler;
}

void WebsocketClientImpl::set_error_handler(const std::function<void(int code, const std::string& message)>& handler) {
    std::lock_guard<std::mutex> guard(handler_mutex);
    error_handler = handler;
}

void WebsocketClientImpl::set_allow_reconnecting(bool allow) {
    if (allow) {
        ws.enableAutomaticReconnection();
    } else {
        ws.disableAutomaticReconnection();
    }
}

void WebsocketClientImpl::set_allowed_reconnect_attempts(unsigned int allowed_attempts) {
    std::lock_guard<std::mutex> guard(conn_mutex);
    WebsocketClientImpl::allowed_attempts = allowed_attempts;
}

void WebsocketClientImpl::open_message_received() {
    std::lock_guard<std::mutex> guard(conn_mutex);

    if (conn_status == ConnectionStatus::CONNECTED) {
        return;
    }

    conn_status = ConnectionStatus::CONNECTED;
    conn_cv.notify_all();
}

void WebsocketClientImpl::error_message_received(const ix::WebSocketMessagePtr& msg) {
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

}
