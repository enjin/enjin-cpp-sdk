#ifndef ENJINCPPSDK_MOCKWEBSOCKETCLIENTIMPL_HPP
#define ENJINCPPSDK_MOCKWEBSOCKETCLIENTIMPL_HPP

#include "WebsocketClientImpl.hpp"
#include <string>

namespace enjin::test::utils {

class MockWebSocketClientImpl : public sdk::websockets::WebsocketClientImpl {
public:
    std::future<void> connect(const std::string& uri) override;
};

}

#endif //ENJINCPPSDK_MOCKWEBSOCKETCLIENTIMPL_HPP
