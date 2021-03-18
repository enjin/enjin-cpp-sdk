#include "MockWebSocketClientImpl.hpp"

namespace enjin::test::mocks {

void MockWebSocketClientImpl::connect(const std::string& uri) {
    WebsocketClientImpl::connect("ws://127.0.0.1:8080/ws");
}

}