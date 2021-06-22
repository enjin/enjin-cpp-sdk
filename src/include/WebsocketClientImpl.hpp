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

#ifndef ENJINCPPSDK_WEBSOCKETCLIENTIMPL_HPP
#define ENJINCPPSDK_WEBSOCKETCLIENTIMPL_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/IWebsocketClient.hpp"
#include "ixwebsocket/IXWebSocket.h"
#include <condition_variable>
#include <functional>
#include <memory>
#include <mutex>
#include <optional>
#include <stdexcept>
#include <string>

namespace enjin::sdk::websockets {

/// \brief Implementation class of a websocket client.
class ENJINSDK_EXPORT WebsocketClientImpl : public IWebsocketClient {
public:
    /// \brief Creates the websocket client.
    WebsocketClientImpl();

    ~WebsocketClientImpl() override;

    std::future<void> connect(const std::string& uri) override;

    std::future<void> close() override;

    std::future<void> close(int status_code, const std::string& reason) override;

    void send(const std::string& data) override;

    void set_open_handler(const std::function<void()>& handler) override;

    void set_close_handler(const std::function<void(int close_status, const std::string& message)>& handler) override;

    void set_message_handler(const std::function<void(const std::string& message)>& handler) override;

    void set_error_handler(const std::function<void(int code, const std::string& message)>& handler) override;

    void set_allow_reconnecting(bool allow) override;

    void set_allowed_reconnect_attempts(unsigned int allowed_attempts) override;

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

    void open_message_received();

    void error_message_received(const ix::WebSocketMessagePtr& msg);
};

}

#endif //ENJINCPPSDK_WEBSOCKETCLIENTIMPL_HPP
#endif
