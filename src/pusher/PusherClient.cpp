#include "enjinsdk/internal/pusher/PusherClient.hpp"

#include <utility>

namespace enjin::pusher {

PusherClient::PusherClient(std::shared_ptr<sdk::websockets::IWebsocketClient> ws_client,
                           const std::string& key,
                           PusherOptions& options)
        : ws_client(std::move(ws_client)) {
}

void PusherClient::connect(const std::function<void()>& on_connection_state_change,
                           const std::function<void(const std::string&,
                                                    const std::string&,
                                                    std::exception)>& on_error) {
    PusherClient::on_connection_state_change = on_connection_state_change;
    PusherClient::on_error = on_error;
}

void PusherClient::disconnect() {
}

PusherChannel PusherClient::subscribe(const std::string& channel) {
    return PusherChannel();
}

void PusherClient::unsubscribe(const std::string& channel) {
}

ConnectionState PusherClient::get_state() {
    return state;
}

}
