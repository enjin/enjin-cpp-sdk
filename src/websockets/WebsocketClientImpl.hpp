#ifndef ENJINCPPSDK_WEBSOCKETCLIENTIMPL_HPP
#define ENJINCPPSDK_WEBSOCKETCLIENTIMPL_HPP

#include "cpprest/ws_client.h"
#include "enjinsdk/IWebsocketClient.hpp"
#include <functional>
#include <future>
#include <string>

namespace enjin::sdk::websockets {

/// \brief Implementation class of a websocket client.
class WebsocketClientImpl : public IWebsocketClient {
public:
    WebsocketClientImpl() = default;

    ~WebsocketClientImpl() override = default;

    std::future<void> connect(const std::string& uri) override;

    std::future<void> close() override;

    std::future<void> close(int status_code, const std::string& reason) override;

    std::future<void> send(const std::string& data) override;

    void set_close_handler(const std::function<void(int close_status,
                                                    const std::string& message,
                                                    const std::error_code& error)>& handler) override;

    void set_message_handler(const std::function<void(const std::string& message)>& handler) override;

private:
    web::web_sockets::client::websocket_callback_client ws_client;
};

}

#endif //ENJINCPPSDK_WEBSOCKETCLIENTIMPL_HPP
