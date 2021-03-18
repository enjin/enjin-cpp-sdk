#ifndef ENJINSDK_MOCKWEBSOCKETCLIENT_HPP
#define ENJINSDK_MOCKWEBSOCKETCLIENT_HPP

#include "enjinsdk/IWebsocketClient.hpp"
#include "gmock/gmock.h"
#include <functional>
#include <string>

namespace enjin::test::mocks {

class MockWebsocketClient : public sdk::websockets::IWebsocketClient {
public:
    MOCK_METHOD(void, connect, (const std::string& uri), (override));

    MOCK_METHOD(void, close, (), (override));

    MOCK_METHOD(void, close, (int status_code, const std::string& reason), (override));

    MOCK_METHOD(void, send, (const std::string& data), (override));

    MOCK_METHOD(void, set_open_handler, (const std::function<void()>& handler), (override));

    MOCK_METHOD(void,
                set_close_handler,
                (const std::function<void(int close_status, const std::string& message)>& handler),
                (override));

    MOCK_METHOD(void,
                set_message_handler,
                (const std::function<void(const std::string& message)>& handler),
                (override));

    MOCK_METHOD(void, set_allow_reconnecting, (bool allowed), (override));
};

typedef testing::NiceMock<MockWebsocketClient> DummyWebsocketClient;

}

#endif //ENJINSDK_MOCKWEBSOCKETCLIENT_HPP
