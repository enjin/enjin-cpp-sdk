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
#include "enjinsdk/LoggerProvider.hpp"
#include "ixwebsocket/IXWebSocket.h"
#include <functional>
#include <future>
#include <memory>
#include <mutex>
#include <optional>
#include <string>

namespace enjin::sdk::websockets {

/// \brief Implementation class of a websocket client.
class ENJINSDK_EXPORT WebsocketClientImpl : public IWebsocketClient {
public:
    /// \brief Creates the websocket client.
    /// \param logger_provider The logger provider. Null pointer by default.
    explicit WebsocketClientImpl(std::shared_ptr<utils::LoggerProvider> logger_provider = nullptr);

    ~WebsocketClientImpl() override;

    void connect(const std::string& uri) override;

    void close() override;

    void close(int status_code, const std::string& reason) override;

    void send(const std::string& data) override;

    void set_open_handler(const std::function<void()>& handler) override;

    void set_close_handler(const std::function<void(int close_status, const std::string& message)>& handler) override;

    void set_message_handler(const std::function<void(const std::string& message)>& handler) override;

    void set_allow_reconnecting(bool allowed) override;

private:
    ix::WebSocket ws;
    std::shared_ptr<utils::LoggerProvider> logger_provider;

    std::optional<std::function<void()>> open_handler;
    std::optional<std::function<void(int, const std::string&)>> close_handler;
    std::optional<std::function<void(const std::string&)>> message_handler;

    // Mutex
    mutable std::mutex handler_mutex;
};

}

#endif //ENJINCPPSDK_WEBSOCKETCLIENTIMPL_HPP
#endif
