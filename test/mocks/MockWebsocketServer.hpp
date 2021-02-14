#ifndef ENJINCPPSDK_MOCKWEBSOCKETSERVER_HPP
#define ENJINCPPSDK_MOCKWEBSOCKETSERVER_HPP

#include <functional>
#include <memory>
#include <mutex>
#include <queue>
#include <string>
#include <vector>

namespace enjin::test::utils {

enum class WebsocketMessageType {
    WEBSOCKET_BINARY_MESSAGE_TYPE,
    WEBSOCKET_BINARY_FRAGMENT_TYPE,
    WEBSOCKET_UTF8_MESSAGE_TYPE,
    WEBSOCKET_UTF8_FRAGMENT_TYPE,
    WEBSOCKET_CLOSE_TYPE,
    WEBSOCKET_PING_TYPE,
    WEBSOCKET_PONG_TYPE,
};

class ITestHttpRequest {
public:
    virtual ~ITestHttpRequest() = default;
    virtual const std::string& get_username() = 0;
    virtual const std::string& get_password() = 0;
    virtual const std::string& get_header_value(const std::string& header_name) = 0;
};

typedef std::unique_ptr<ITestHttpRequest> TestHttpRequest;

class TestHttpResponse {
public:
    [[nodiscard]] const std::string& get_realm() const;

    [[nodiscard]] unsigned short get_status_code() const;

    void set_realm(const std::string& realm);

    void set_status_code(unsigned short status_code);

public:

private:
    std::string realm;
    unsigned short status_code;
};

typedef std::function<TestHttpResponse __cdecl(TestHttpRequest)> HttpHandler;

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

    void next_message(std::function<void(TestWebsocketMessage)> handler);

    std::function<void(TestWebsocketMessage)> get_next_message_handler();

    void send_message(const TestWebsocketMessage& message);

    [[nodiscard]] const HttpHandler& get_http_handler() const;

    void set_http_handler(const HttpHandler& http_handler);

private:
    std::mutex message_handlers_lock;
    std::queue<std::function<void(TestWebsocketMessage)>> message_handlers;

    HttpHandler http_handler;
    std::shared_ptr<MockWebsocketServerImpl> impl;
};

}

#endif //ENJINCPPSDK_MOCKWEBSOCKETSERVER_HPP
