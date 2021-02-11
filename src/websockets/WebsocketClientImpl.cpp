#include "WebsocketClientImpl.hpp"

using namespace web::websockets::client;

namespace enjin::sdk::websockets {

WebsocketClientImpl::WebsocketClientImpl() {
    ws_client.set_message_handler([this](const websocket_incoming_message& in) {
        websocket_message_type type = in.message_type();
        if (type == websocket_message_type::text_message && message_handler.has_value()) {
            message_handler.value()(in.extract_string().get());
        } else if (type == websocket_message_type::pong && pong_handler.has_value()) {
            pong_handler.value()(in.extract_string().get());
        } else if (type == websocket_message_type::ping) {
            websocket_outgoing_message out;
            out.set_pong_message("ws client pong");
            auto fut = ws_client.send(out);

            if (ping_handler.has_value()) {
                ping_handler.value()(in.extract_string().get());
            }

            fut.wait();
        }
    });
}

std::future<void> WebsocketClientImpl::connect(const std::string& uri) {
    return std::async([this, uri]() {
        ws_client.connect(utility::conversions::to_string_t(uri)).wait();
    });
}

std::future<void> WebsocketClientImpl::close() {
    return std::async([this]() {
        ws_client.close().wait();
    });
}

std::future<void> WebsocketClientImpl::close(int status_code, const std::string& reason) {
    return std::async([this, status_code, reason]() {
        ws_client.close((websocket_close_status) status_code,
                        utility::conversions::to_string_t(reason)).wait();
    });
}

std::future<void> WebsocketClientImpl::send(const std::string& data) {
    return std::async([this, data]() {
        websocket_outgoing_message message;
        message.set_utf8_message(data);
        ws_client.send(message).wait();
    });
}

void WebsocketClientImpl::set_close_handler(const std::function<void(int,
                                                                     const std::string&,
                                                                     const std::error_code&)>& handler) {
    ws_client.set_close_handler([handler](websocket_close_status close_status,
                                          const utility::string_t& reason,
                                          const std::error_code& error) {
        handler((int) close_status, utility::conversions::to_utf8string(reason), error);
    });
}

void WebsocketClientImpl::set_message_handler(const std::function<void(const std::string& message)>& handler) {
    message_handler = handler;
}

void WebsocketClientImpl::set_ping_handler(const std::function<void(const std::string&)>& handler) {
    ping_handler = handler;
}

void WebsocketClientImpl::set_pong_handler(const std::function<void(const std::string&)>& handler) {
    pong_handler = handler;
}

}
