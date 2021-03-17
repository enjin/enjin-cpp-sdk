#ifndef ENJINCPPSDK_MOCKSUBSCRIPTIONEVENTLISTENER_HPP
#define ENJINCPPSDK_MOCKSUBSCRIPTIONEVENTLISTENER_HPP

#include "ISubscriptionEventListener.hpp"
#include "gmock/gmock.h"

namespace enjin::test::utils {

class MockSubscriptionEventListener : public enjin::pusher::ISubscriptionEventListener {
public:
    MOCK_METHOD(void, on_event, (const enjin::pusher::PusherEvent& event), (override));
};

}

#endif //ENJINCPPSDK_MOCKSUBSCRIPTIONEVENTLISTENER_HPP
