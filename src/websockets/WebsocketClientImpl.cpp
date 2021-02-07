#include "WebsocketClientImpl.hpp"

namespace enjin::sdk::websockets {

std::future<void> WebsocketClientImpl::connect(const std::string& uri) {
    return std::async([this, uri]() {
        ws_client.connect(utility::conversions::to_string_t(uri));
    });
}

std::future<void> WebsocketClientImpl::close() {
    return std::async([this]() {
        ws_client.close();
    });
}

std::future<void> WebsocketClientImpl::send(const std::string& data) {
    return std::async([this, data]() {
        web::websockets::client::websocket_outgoing_message message;
        message.set_utf8_message(data);
        ws_client.send(message);
    });
}

void WebsocketClientImpl::set_close_handler(const std::function<void(int,
                                                                     const std::string&,
                                                                     const std::error_code&)>& handler) {
    ws_client.set_close_handler([handler](web::websockets::client::websocket_close_status close_status,
                                          const utility::string_t& reason,
                                          const std::error_code& error) {
        handler((int) close_status, utility::conversions::to_utf8string(reason), error);
    });
}

void WebsocketClientImpl::set_message_handler(const std::function<void(const std::string& message)>& handler) {
    ws_client.set_message_handler([this, handler](const web::websockets::client::websocket_incoming_message& in) {
        // Only use handler for incoming messages that are strings
        if (in.message_type() == web::websockets::client::websocket_message_type::text_message) {
            handler(in.extract_string().get());
            return;
        }

        // Handle non-string messages
        web::websockets::client::websocket_outgoing_message out;
        switch (in.message_type()) {
            case web::websockets::client::websocket_message_type::ping: // Respond to maintain connection
                out.set_pong_message("ws client pong");
                ws_client.send(out);
                break;
            case web::websockets::client::websocket_message_type::pong: // TODO: Handle pong and binary messages.
            case web::websockets::client::websocket_message_type::binary_message:
                break;
            default: // Ignore close messages
                break;
        }
    });
}

}
