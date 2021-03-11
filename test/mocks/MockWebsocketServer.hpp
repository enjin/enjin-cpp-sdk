#ifndef ENJINCPPSDK_MOCKWEBSOCKETSERVER_HPP
#define ENJINCPPSDK_MOCKWEBSOCKETSERVER_HPP

#include <functional>
#include <memory>
#include <mutex>
#include <queue>
#include <set>
#include <string>
#include <vector>

namespace enjin::test::utils {

enum class WebsocketMessageType {
    WEBSOCKET_BINARY_MESSAGE_TYPE,
    WEBSOCKET_BINARY_FRAGMENT_TYPE,
    WEBSOCKET_UTF8_MESSAGE_TYPE,
    WEBSOCKET_UTF8_FRAGMENT_TYPE,
    WEBSOCKET_CLOSE_TYPE,
    WEBSOCKET_OPEN_TYPE,
    WEBSOCKET_PING_TYPE,
    WEBSOCKET_PONG_TYPE,
};

class TestWebsocketMessage {
public:
    [[nodiscard]] const std::vector<unsigned char>& get_data() const;

    [[nodiscard]] WebsocketMessageType get_type() const;

    void set_data(std::vector<unsigned char> data);

    void set_type(WebsocketMessageType type);

private:
    std::vector<unsigned char> data;
    WebsocketMessageType type;
};

class MockWebsocketServerImpl;

class MockWebsocketServer {
public:
    MockWebsocketServer();

    ~MockWebsocketServer() = default;

    void next_message(const std::function<void(TestWebsocketMessage)>& handler);

    MockWebsocketServer& ignore_message_type(WebsocketMessageType type);

    std::function<void(TestWebsocketMessage)> get_next_message_handler();

    void send_message(const TestWebsocketMessage& message);

    void close(int code, const std::string& reason);

    bool is_type_ignored(WebsocketMessageType type);

private:
    std::mutex message_handlers_lock;
    std::queue<std::function<void(TestWebsocketMessage)>> message_handlers;
    std::set<WebsocketMessageType> ignored_types;

    std::shared_ptr<MockWebsocketServerImpl> impl;
};

}

#endif //ENJINCPPSDK_MOCKWEBSOCKETSERVER_HPP
