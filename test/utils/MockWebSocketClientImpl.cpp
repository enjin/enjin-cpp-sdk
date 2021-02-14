#include "MockWebSocketClientImpl.hpp"

namespace enjin::test::utils {

std::future<void> MockWebSocketClientImpl::connect(const std::string& uri) {
    return WebsocketClientImpl::connect("ws://localhost:9980/ws");
}


}