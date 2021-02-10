#include "MockWebsocketServer.hpp"

#include "cpprest/ws_client.h"
#include "websocketpp/server.hpp"
#include "websocketpp/config/asio_no_tls.hpp"
#include <thread>

#define WEBSOCKET_TEST_SERVER_PORT 9980

namespace enjin::test::utils {

typedef websocketpp::server<websocketpp::config::asio> Server;

const std::string& TestHttpResponse::get_realm() const {
    return realm;
}

unsigned short TestHttpResponse::get_status_code() const {
    return status_code;
}

void TestHttpResponse::set_realm(const std::string& realm) {
    TestHttpResponse::realm = realm;
}

void TestHttpResponse::set_status_code(unsigned short status_code) {
    TestHttpResponse::status_code = status_code;
}

const std::vector<unsigned char>& TestWebsocketMessage::get_data() const {
    return data;
}

WebsocketMessageType TestWebsocketMessage::get_type() const {
    return type;
}

void TestWebsocketMessage::set_data(std::vector<unsigned char> data) {
    TestWebsocketMessage::data = data;
}

void TestWebsocketMessage::set_type(WebsocketMessageType type) {
    TestWebsocketMessage::type = type;
}

class TestHttpRequestImpl : public ITestHttpRequest {
public:
    TestHttpRequestImpl() = delete;

    TestHttpRequestImpl(Server::connection_ptr connection) : connection(connection) {
    }

    ~TestHttpRequestImpl() override = default;

    const std::string& get_username() override {
        throw std::runtime_error("Not yet implemented");
    }

    const std::string& get_password() override {
        throw std::runtime_error("Not yet implemented");
    }

    const std::string& get_header_value(const std::string& header_name) override {
        return connection->get_request_header(header_name);
    }

private:
    Server::connection_ptr connection;
};

class MockWebsocketServerImpl {
public:
    MockWebsocketServerImpl() = delete;

    explicit MockWebsocketServerImpl(MockWebsocketServer* mock_server) : mock_server(mock_server) {
        server.clear_access_channels(websocketpp::log::alevel::all);
        server.clear_error_channels(websocketpp::log::elevel::all);
        connect();
    }

    ~MockWebsocketServerImpl() {
        close("Destructor");
        server.stop_listening();
        server.stop_perpetual();
        _ASSERT(thread.joinable());
        thread.join();
    }

    void connect() {
        server.set_validate_handler([this](websocketpp::connection_hdl hdl) {
            auto handler = mock_server->get_http_handler();
            if (handler) {
                Server::connection_ptr connection = server.get_con_from_hdl(hdl);
                TestHttpRequest request(new TestHttpRequestImpl(connection));
                TestHttpResponse response = handler(std::move(request));

                connection->set_status(static_cast<websocketpp::http::status_code::value>(response.get_status_code()));
                if (response.get_status_code() != 200) {
                    return false;
                }
            }

            return true;
        });

        server.set_open_handler([this](websocketpp::connection_hdl hdl) {
            connection = hdl;
            server_connected.set();
        });

        server.set_fail_handler([this](websocketpp::connection_hdl hdl) {
            connection = hdl;
            server_connected.set_exception(std::runtime_error("Connection attempt failed"));
        });

        server.set_ping_handler([this](websocketpp::connection_hdl hdl, std::string input) {
            auto handler = mock_server->get_next_message_handler();
            assert(handler);

            TestWebsocketMessage ws_message;
            ws_message.set_data(std::vector<uint8_t>(input.begin(), input.end()));
            ws_message.set_type(WebsocketMessageType::WEBSOCKET_PING_TYPE);

            handler(ws_message);

            return true;
        });

        server.set_pong_handler([this](websocketpp::connection_hdl hdl, std::string input) {
            auto handler = mock_server->get_next_message_handler();
            assert(handler);

            TestWebsocketMessage ws_message;
            ws_message.set_data(std::vector<uint8_t>(input.begin(), input.end()));
            ws_message.set_type(WebsocketMessageType::WEBSOCKET_PONG_TYPE);

            handler(ws_message);
        });

        server.set_message_handler([this](websocketpp::connection_hdl hdl, Server::message_ptr message) {
            auto payload = message->get_payload();
            auto handler = mock_server->get_next_message_handler();
            assert(handler);

            TestWebsocketMessage ws_message;
            ws_message.set_data(std::vector<uint8_t>(payload.begin(), payload.end()));

            switch (message->get_opcode()) {
                case websocketpp::frame::opcode::BINARY:
                    ws_message.set_type(WebsocketMessageType::WEBSOCKET_BINARY_MESSAGE_TYPE);
                    break;
                case websocketpp::frame::opcode::TEXT:
                    ws_message.set_type(WebsocketMessageType::WEBSOCKET_UTF8_MESSAGE_TYPE);
                    break;
                case websocketpp::frame::opcode::CLOSE:
                    ws_message.set_type(WebsocketMessageType::WEBSOCKET_CLOSE_TYPE);
                    break;
                default:
                    std::abort();
            }

            handler(ws_message);
        });

        server.init_asio();
        server.start_perpetual();
        server.set_reuse_addr(true);

        websocketpp::lib::error_code error_code;
        server.listen(WEBSOCKET_TEST_SERVER_PORT, error_code);
        if (error_code) {
            throw std::runtime_error(error_code.message());
        }

        server.start_accept();
        thread = std::thread(&Server::run, &server);
    }

    void close(const std::string& reason) {
        websocketpp::lib::error_code error_code;
        server.close(connection, websocketpp::close::status::going_away, reason, error_code);
    }

    void send_message(const TestWebsocketMessage& message) {
        pplx::task<void>(server_connected).wait();
        const auto& data = message.get_data();
        std::string string_message(data.begin(), data.end());

        switch (message.get_type()) {
            case WebsocketMessageType::WEBSOCKET_BINARY_MESSAGE_TYPE:
                server.send(connection, string_message, websocketpp::frame::opcode::BINARY);
                break;
            case WebsocketMessageType::WEBSOCKET_UTF8_MESSAGE_TYPE:
                server.send(connection, string_message, websocketpp::frame::opcode::TEXT);
                break;
            case WebsocketMessageType::WEBSOCKET_CLOSE_TYPE:
                close(string_message);
                break;
            case WebsocketMessageType::WEBSOCKET_PING_TYPE:
                server.ping(connection, string_message);
                break;
            case WebsocketMessageType::WEBSOCKET_PONG_TYPE:
                server.ping(connection, string_message);
                break;
            case WebsocketMessageType::WEBSOCKET_BINARY_FRAGMENT_TYPE:
            case WebsocketMessageType::WEBSOCKET_UTF8_FRAGMENT_TYPE:
                throw std::runtime_error("Invalid websocket message type");
            default:
                throw std::runtime_error("Unknown websocket message type");
        }
    }

private:
    MockWebsocketServer* mock_server;

    std::thread thread;

    Server server;
    websocketpp::connection_hdl connection;
    pplx::task_completion_event<void> server_connected;
};

MockWebsocketServer::MockWebsocketServer() : impl(std::make_shared<MockWebsocketServerImpl>(this)) {
}

void MockWebsocketServer::next_message(std::function<void(TestWebsocketMessage)> handler) {
    std::lock_guard<std::mutex> guard(message_handlers_lock);

    assert(handler);
    message_handlers.push(handler);
}

std::function<void(TestWebsocketMessage)> MockWebsocketServer::get_next_message_handler() {
    std::lock_guard<std::mutex> guard(message_handlers_lock);

    assert(!message_handlers.empty());
    auto handler = message_handlers.front();
    assert(handler);
    message_handlers.pop();
    assert(handler);

    return handler;
}

void MockWebsocketServer::send_message(const TestWebsocketMessage& message) {
    impl->send_message(message);
}

const HttpHandler& MockWebsocketServer::get_http_handler() const {
    return http_handler;
}

void MockWebsocketServer::set_http_handler(const HttpHandler& http_handler) {
    MockWebsocketServer::http_handler = http_handler;
}

}
