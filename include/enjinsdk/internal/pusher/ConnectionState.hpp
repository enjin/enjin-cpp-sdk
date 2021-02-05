#ifndef ENJINCPPSDK_PUSHERCONNECTIONSTATE_HPP
#define ENJINCPPSDK_PUSHERCONNECTIONSTATE_HPP

namespace enjin::pusher {

/// \brief Enums for different connection states for a Pusher client.
enum class ConnectionState {
    CONNECTING,
    CONNECTED,
    DISCONNECTING,
    DISCONNECTED,
    RECONNECTING,
    ALL, ///< \brief Value used to indicate any state when used as a function argument.
};

}

#endif //ENJINCPPSDK_PUSHERCONNECTIONSTATE_HPP
