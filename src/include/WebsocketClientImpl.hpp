#ifndef ENJINSDK_INCLUDE_WEBSOCKET_CLIENT_IMPL
#define ENJINSDK_INCLUDE_WEBSOCKET_CLIENT_IMPL 0
#endif
#if ENJINSDK_INCLUDE_WEBSOCKET_CLIENT_IMPL

#ifndef ENJINCPPSDK_WEBSOCKETCLIENTIMPL_HPP
#define ENJINCPPSDK_WEBSOCKETCLIENTIMPL_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/IWebsocketClient.hpp"
#include "ixwebsocket/IXWebSocket.h"
#include <functional>
#include <future>
#include <mutex>
#include <optional>
#include <string>

namespace enjin::sdk::websockets {

/// \brief Implementation class of a websocket client.
class ENJINSDK_EXPORT WebsocketClientImpl : public IWebsocketClient {
public:
    WebsocketClientImpl();

    ~WebsocketClientImpl() override;

    void connect(const std::string& uri) override;

    void close() override;

    void close(int status_code, const std::string& reason) override;

    void send(const std::string& data) override;

    void set_open_handler(const std::function<void()>& handler) override;

    void set_close_handler(const std::function<void(int close_status, const std::string& message)>& handler) override;

    void set_message_handler(const std::function<void(const std::string& message)>& handler) override;

    void set_allow_reconnecting(bool allowed) override;

private:
    ix::WebSocket ws;

    std::optional<std::function<void()>> open_handler;
    std::optional<std::function<void(int, const std::string&)>> close_handler;
    std::optional<std::function<void(const std::string&)>> message_handler;

    std::mutex handler_mutex;
};

}

#endif //ENJINCPPSDK_WEBSOCKETCLIENTIMPL_HPP
#endif
