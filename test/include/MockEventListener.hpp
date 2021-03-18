#ifndef ENJINCPPSDK_MOCKEVENTLISTENER_HPP
#define ENJINCPPSDK_MOCKEVENTLISTENER_HPP

#include "enjinsdk/IEventListener.hpp"
#include "gmock/gmock.h"

namespace enjin::test::mocks {

class MockEventListener : public sdk::events::IEventListener {
public:
    MOCK_METHOD(void, notification_received, (enjin::sdk::models::NotificationEvent event), (override));
};

}

#endif //ENJINCPPSDK_MOCKEVENTLISTENER_HPP
