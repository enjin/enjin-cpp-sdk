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

#ifndef ENJINCPPSDK_FAKEWEBSOCKETCLIENTIMPL_HPP
#define ENJINCPPSDK_FAKEWEBSOCKETCLIENTIMPL_HPP

#include "WebsocketClientImpl.hpp"
#include <string>

namespace enjin::test::mocks {

/// \brief A fake websocket client based on the SDK's built-in websocket client used for testing with a websocket server
/// open on a localhost port.
class FakeWebSocketClientImpl : public sdk::websockets::WebsocketClientImpl {
public:
    /// \brief Overridden member function that has this client connect to a open connection on a local test server.
    /// \param uri Ignored parameter.
    /// \return The future for this operation.
    /// \remarks This will always connect to a open connection on "ws://127.0.0.1:8080/ws" irregardless of the passed
    /// parameter.
    std::future<void> connect(const std::string& uri) override;
};

}

#endif //ENJINCPPSDK_FAKEWEBSOCKETCLIENTIMPL_HPP
#endif
