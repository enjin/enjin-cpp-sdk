#ifndef ENJINCPPSDK_PUSHERCLIENTTESTSUITE_HPP
#define ENJINCPPSDK_PUSHERCLIENTTESTSUITE_HPP

#include "enjinsdk/internal/pusher/Constants.hpp"
#include "enjinsdk/internal/pusher/PusherClient.hpp"
#include "../mocks/MockWebSocketClientImpl.hpp"
#include "../mocks/MockWebsocketServer.hpp"
#include <memory>
#include <sstream>
#include <string>

namespace enjin::test::utils {

class PusherClientTestSuite {
public:
    static constexpr char DEFAULT_CHANNEL_NAME[] = "test.channel";
    static constexpr char DEFAULT_CLUSTER[] = "mt1";
    static constexpr char DEFAULT_EVENT_NAME[] = "TestEvent";
    static constexpr char DEFAULT_KEY[] = "xyz";

    std::shared_ptr<MockWebSocketClientImpl> mock_ws_client = std::make_shared<MockWebSocketClientImpl>();
    MockWebsocketServer mock_server;

    enjin::pusher::PusherClient create_testable_pusher_client();

    static std::string create_default_event(const std::string& channel = "", const std::string& data = "null");

    static pusher::PusherOptions create_default_pusher_options();

    static std::string create_subscription_error_message();

    static std::string create_subscription_success_message(const std::string& channel = "",
                                                           const std::string& data = "null");
};

}

#endif //ENJINCPPSDK_PUSHERCLIENTTESTSUITE_HPP
