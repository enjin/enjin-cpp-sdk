#ifndef ENJINSDK_INCLUDE_WEBSOCKET_CLIENT_IMPL
#define ENJINSDK_INCLUDE_WEBSOCKET_CLIENT_IMPL 0
#endif
#if ENJINSDK_INCLUDE_WEBSOCKET_CLIENT_IMPL

#ifndef ENJINCPPSDK_PUSHERCLIENTTESTSUITE_HPP
#define ENJINCPPSDK_PUSHERCLIENTTESTSUITE_HPP

#include "Constants.hpp"
#include "MockWebSocketClientImpl.hpp"
#include "MockWebsocketServer.hpp"
#include "PusherClient.hpp"
#include <memory>
#include <sstream>
#include <string>

namespace enjin::test::suites {

class PusherClientTestSuite {
public:
    static constexpr char DEFAULT_CHANNEL_NAME[] = "test.channel";
    static constexpr char DEFAULT_CLUSTER[] = "mt1";
    static constexpr char DEFAULT_EVENT_NAME[] = "TestEvent";
    static constexpr char DEFAULT_KEY[] = "xyz";

    std::shared_ptr<mocks::MockWebSocketClientImpl> mock_ws_client = std::make_shared<mocks::MockWebSocketClientImpl>();
    mocks::MockWebsocketServer mock_server;

    enjin::pusher::PusherClient create_testable_pusher_client();

    static std::string create_default_event(const std::string& channel = "", const std::string& data = "null");

    static pusher::PusherOptions create_default_pusher_options();

    static std::string create_subscription_error_message();

    static std::string create_subscription_success_message(const std::string& channel = "",
                                                           const std::string& data = "null");
};

}

#endif //ENJINCPPSDK_PUSHERCLIENTTESTSUITE_HPP
#endif
