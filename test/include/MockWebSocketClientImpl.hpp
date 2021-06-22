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

#ifndef ENJINCPPSDK_MOCKWEBSOCKETCLIENTIMPL_HPP
#define ENJINCPPSDK_MOCKWEBSOCKETCLIENTIMPL_HPP

#include "WebsocketClientImpl.hpp"
#include <string>

namespace enjin::test::mocks {

class MockWebSocketClientImpl : public sdk::websockets::WebsocketClientImpl {
public:
    std::future<void> connect(const std::string& uri) override;
};

}

#endif //ENJINCPPSDK_MOCKWEBSOCKETCLIENTIMPL_HPP
#endif
