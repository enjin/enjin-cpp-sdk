#ifndef ENJINCPPSDK_IEVENTLISTENER_HPP
#define ENJINCPPSDK_IEVENTLISTENER_HPP

#include "enjinsdk/models/NotificationEvent.hpp"

namespace enjin::sdk::events {

class IEventListener {
public:
    virtual ~IEventListener() = default;

    virtual void notification_received(models::NotificationEvent event) = 0;
};

}

#endif //ENJINCPPSDK_IEVENTLISTENER_HPP
