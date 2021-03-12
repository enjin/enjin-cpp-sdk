#ifndef ENJINCPPSDK_MOCKEVENTLISTENER_HPP
#define ENJINCPPSDK_MOCKEVENTLISTENER_HPP

#include "enjinsdk/IEventListener.hpp"
#include "gmock/gmock.h"

class MockEventListener : public enjin::sdk::events::IEventListener {
public:
    MOCK_METHOD(void, notification_received, (enjin::sdk::models::NotificationEvent event), (override));
};

#endif //ENJINCPPSDK_MOCKEVENTLISTENER_HPP
