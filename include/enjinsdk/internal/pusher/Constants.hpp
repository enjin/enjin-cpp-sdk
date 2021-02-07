#ifndef ENJINCPPSDK_PUSHERCONSTANTS_HPP
#define ENJINCPPSDK_CONSTANTS_HPP

namespace enjin::pusher {

class Constants {
public:
    static constexpr char CHANNEL_SUBSCRIBE[] = "pusher:subscribe";
    static constexpr char CHANNEL_UNSUBSCRIBE[] = "pusher:unsubscribe";

    static constexpr char INSECURE_SCHEMA[] = "ws://";
    static constexpr char SECURE_SCHEMA[] = "wss://";
};

}

#endif //ENJINCPPSDK_CONSTANTS_HPP
