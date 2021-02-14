#ifndef ENJINCPPSDK_PUSHERISUBSCRIPTIONEVENTLISTENER_HPP
#define ENJINCPPSDK_PUSHERISUBSCRIPTIONEVENTLISTENER_HPP

#include "enjinsdk/internal/pusher/PusherEvent.hpp"

namespace enjin::pusher {

/// \brief Interface for event listener for receiving Pusher events.
class ISubscriptionEventListener {
public:
    /// \brief Default destructor.
    virtual ~ISubscriptionEventListener() = default;

    /// \brief Handler for Pusher events.
    /// \param event The Pusher event.
    virtual void on_event(const PusherEvent& event) = 0;
};

}

#endif //ENJINCPPSDK_PUSHERISUBSCRIPTIONEVENTLISTENER_HPP
