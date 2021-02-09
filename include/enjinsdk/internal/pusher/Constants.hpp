#ifndef ENJINCPPSDK_PUSHERCONSTANTS_HPP
#define ENJINCPPSDK_CONSTANTS_HPP

namespace enjin::pusher {

class Constants {
public:
    static constexpr char PUSHER_MESSAGE_PREFIX[] = "pusher";

    static constexpr char CHANNEL_SUBSCRIBE[] = "pusher:subscribe";
    static constexpr char CHANNEL_UNSUBSCRIBE[] = "pusher:unsubscribe";
    static constexpr char CHANNEL_SUBSCRIPTION_SUCCEEDED[] = "pusher_internal:subscription_succeed";
    static constexpr char CHANNEL_SUBSCRIPTION_ERROR[] = "pusher_internal:subscription_error";

    static constexpr char INSECURE_SCHEMA[] = "ws://";
    static constexpr char SECURE_SCHEMA[] = "wss://";
};

}

#endif //ENJINCPPSDK_CONSTANTS_HPP
