#ifndef ENJINCPPSDK_PUSHERISUBSCRIPTIONEVENTLISTENER_HPP
#define ENJINCPPSDK_PUSHERISUBSCRIPTIONEVENTLISTENER_HPP

#include "enjinsdk/internal/pusher/PusherEvent.hpp"

namespace enjin::pusher {

/// \brief TODO
class ISubscriptionEventListener {
public:
    virtual ~ISubscriptionEventListener() = default;

    virtual void on_event(const pusher::PusherEvent& event) = 0;
};

}

#endif //ENJINCPPSDK_PUSHERISUBSCRIPTIONEVENTLISTENER_HPP
