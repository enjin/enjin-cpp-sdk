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

#ifndef ENJINCPPSDK_WEBSOCKETCLIENT_HPP
#define ENJINCPPSDK_WEBSOCKETCLIENT_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/IWebsocketClient.hpp"
#include <functional>
#include <string>

namespace enjin::sdk::websockets {

/// \brief Built-in websocket client for this SDK.
class ENJINSDK_EXPORT WebsocketClient : public IWebsocketClient {
public:
    /// \brief Creates the websocket client.
    WebsocketClient();

    /// \brief Destructor.
    ~WebsocketClient() override;

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
    class Impl;

    Impl* impl;
};

}

#endif //ENJINCPPSDK_WEBSOCKETCLIENT_HPP
#endif
