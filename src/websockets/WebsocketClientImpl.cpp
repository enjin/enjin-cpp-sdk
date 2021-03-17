#include "WebsocketClientImpl.hpp"

#include <sstream>

namespace enjin::sdk::websockets {

WebsocketClientImpl::WebsocketClientImpl(std::shared_ptr<utils::Logger> logger) : logger(std::move(logger)) {
    ws.enableAutomaticReconnection();
    ws.enablePong();
    ws.setPingInterval(120); // Ping every 2 minutes

    ws.setOnMessageCallback([this](const ix::WebSocketMessagePtr& msg) {
        std::lock_guard<std::mutex> guard(handler_mutex);

        ix::WebSocketMessageType type = msg->type;
        if (type == ix::WebSocketMessageType::Message && message_handler.has_value()) {
            message_handler.value()(msg->str);
        } else if (type == ix::WebSocketMessageType::Open && open_handler.has_value()) {
            open_handler.value()();
        } else if (type == ix::WebSocketMessageType::Close && close_handler.has_value()) {
            close_handler.value()(msg->closeInfo.code, msg->closeInfo.reason);
        } else if (type == ix::WebSocketMessageType::Error && WebsocketClientImpl::logger != nullptr) {
            std::stringstream ss;
            ss << "Error received from websocket server: "
               << msg->errorInfo.http_status
               << " "
               << msg->errorInfo.reason;
            WebsocketClientImpl::logger->log(utils::LogLevel::WARN, ss.str());
        }
    });
}

WebsocketClientImpl::~WebsocketClientImpl() {
    close();
}

void WebsocketClientImpl::connect(const std::string& uri) {
    ws.setUrl(uri);
    ws.start();
}

void WebsocketClientImpl::close() {
    ws.stop();
}

void WebsocketClientImpl::close(int status_code, const std::string& reason) {
    ws.stop(status_code, reason);
}

void WebsocketClientImpl::send(const std::string& data) {
    ws.sendText(data);
}

void WebsocketClientImpl::set_open_handler(const std::function<void()>& handler) {
    std::lock_guard<std::mutex> guard(handler_mutex);
    open_handler = handler;
}

void WebsocketClientImpl::set_close_handler(const std::function<void(int, const std::string&)>& handler) {
    std::lock_guard<std::mutex> guard(handler_mutex);
    close_handler = handler;
}

void WebsocketClientImpl::set_message_handler(const std::function<void(const std::string& message)>& handler) {
    std::lock_guard<std::mutex> guard(handler_mutex);
    message_handler = handler;
}

void WebsocketClientImpl::set_allow_reconnecting(bool allowed) {
    if (allowed) {
        ws.enableAutomaticReconnection();
    } else {
        ws.disableAutomaticReconnection();
    }
}

}
