#ifndef ENJINSDK_INCLUDE_WEBSOCKET_CLIENT_IMPL
#define ENJINSDK_INCLUDE_WEBSOCKET_CLIENT_IMPL 0
#endif
#if ENJINSDK_INCLUDE_WEBSOCKET_CLIENT_IMPL

#ifndef ENJINCPPSDK_MOCKWEBSOCKETCLIENTIMPL_HPP
#define ENJINCPPSDK_MOCKWEBSOCKETCLIENTIMPL_HPP

#include "WebsocketClientImpl.hpp"
#include <string>

namespace enjin::test::utils {

class MockWebSocketClientImpl : public sdk::websockets::WebsocketClientImpl {
public:
    void connect(const std::string& uri) override;
};

}

#endif //ENJINCPPSDK_MOCKWEBSOCKETCLIENTIMPL_HPP
#endif
