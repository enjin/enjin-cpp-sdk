#ifndef ENJINCPPSDK_PUSHERPUSHERCLIENT_HPP
#define ENJINCPPSDK_PUSHERPUSHERCLIENT_HPP

#include "enjinsdk/IWebsocketClient.hpp"
#include "enjinsdk/internal/pusher/ConnectionState.hpp"
#include "enjinsdk/internal/pusher/ISubscriptionEventListener.hpp"
#include "enjinsdk/internal/pusher/PusherOptions.hpp"
#include <functional>
#include <future>
#include <map>
#include <memory>
#include <mutex>
#include <optional>
#include <string>

namespace enjin::pusher {

/// \brief TODO
class PusherClient : protected std::enable_shared_from_this<PusherClient> {
public:
    class PusherChannel {
    public:
        PusherChannel() = default;

        PusherChannel(const std::string& name, std::shared_ptr<PusherClient> client);

        ~PusherChannel() = default;

        [[nodiscard]] bool is_subscribed() const;

        void bind(const std::string& event_name, ISubscriptionEventListener& listener);

        [[nodiscard]] const std::string& get_name() const;

    private:
        std::shared_ptr<PusherClient> client;
        std::string name;
    };

    PusherClient() = delete;

    PusherClient(std::shared_ptr<sdk::websockets::IWebsocketClient> ws_client,
                 const std::string& key,
                 PusherOptions& options);

    ~PusherClient() = default;

    std::future<void> connect(const std::function<void(ConnectionState state)>& on_connection_state_change,
                              const std::function<void(const std::string& message,
                                                       const std::string& code,
                                                       const std::exception& e)>& on_error);

    std::future<void> disconnect();

    std::future<PusherChannel> subscribe(const std::string& channel_name);

    std::future<void> unsubscribe(const std::string& channel_name);

    ConnectionState get_state();

private:
    std::shared_ptr<sdk::websockets::IWebsocketClient> ws_client;
    std::map<std::string, PusherChannel> channels;
    std::vector<std::string> pending_channels;
    ConnectionState state = ConnectionState::DISCONNECTED;

    std::string key;
    PusherOptions options;

    std::function<void(ConnectionState state)> on_connection_state_change;
    std::function<void(const std::string&, const std::string&, std::exception)> on_error;

    // Mutex
    std::mutex channels_lock;
    std::mutex state_lock;

    std::future<PusherChannel> subscribe_to_channel(const std::string& channel_name);

    bool already_subscribed(const std::string& channel_name);

    void set_state(ConnectionState state);
};

}

#endif //ENJINCPPSDK_PUSHERPUSHERCLIENT_HPP
