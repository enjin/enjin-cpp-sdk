#include "MockWebSocketClientImpl.hpp"

namespace enjin::test::utils {

void MockWebSocketClientImpl::connect(const std::string& uri) {
    WebsocketClientImpl::connect("ws://localhost:9980/ws");
}


}