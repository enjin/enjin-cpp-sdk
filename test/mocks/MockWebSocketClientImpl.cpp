#include "MockWebSocketClientImpl.hpp"

namespace enjin::test::utils {

void MockWebSocketClientImpl::connect(const std::string& uri) {
    WebsocketClientImpl::connect("ws://127.0.0.1:9980/ws");
}


}