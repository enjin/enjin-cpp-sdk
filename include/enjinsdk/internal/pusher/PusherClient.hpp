#ifndef ENJINCPPSDK_PUSHERPUSHERCLIENT_HPP
#define ENJINCPPSDK_PUSHERPUSHERCLIENT_HPP

#include "enjinsdk/IWebsocketClient.hpp"
#include "enjinsdk/internal/pusher/ConnectionState.hpp"
#include "enjinsdk/internal/pusher/PusherChannel.hpp"
#include "enjinsdk/internal/pusher/PusherOptions.hpp"
#include <functional>
#include <memory>
#include <string>

namespace enjin::pusher {

/// \brief TODO
class PusherClient {
public:
    PusherClient() = delete;

    PusherClient(std::shared_ptr<sdk::websockets::IWebsocketClient> ws_client,
                 const std::string& key,
                 PusherOptions& options);

    ~PusherClient() = default;

    void connect(const std::function<void(/* TODO: Connection state change. */)>& on_connection_state_change,
                 const std::function<void(const std::string& message,
                                          const std::string& code,
                                          std::exception e)>& on_error);

    void disconnect();

    PusherChannel subscribe(const std::string& channel);

    void unsubscribe(const std::string& channel);

    ConnectionState get_state();

private:
    std::shared_ptr<sdk::websockets::IWebsocketClient> ws_client;
    std::function<void()> on_connection_state_change;
    std::function<void(const std::string&, const std::string&, std::exception)> on_error;
    ConnectionState state = ConnectionState::DISCONNECTED;
};

}

#endif //ENJINCPPSDK_PUSHERPUSHERCLIENT_HPP
