#ifndef ENJINCPPSDK_MOCKSUBSCRIPTIONEVENTLISTENER_HPP
#define ENJINCPPSDK_MOCKSUBSCRIPTIONEVENTLISTENER_HPP

#include "ISubscriptionEventListener.hpp"
#include "gmock/gmock.h"

namespace enjin::test::mocks {

class MockSubscriptionEventListener : public pusher::ISubscriptionEventListener {
public:
    MOCK_METHOD(void, on_event, (const pusher::PusherEvent& event), (override));
};

}

#endif //ENJINCPPSDK_MOCKSUBSCRIPTIONEVENTLISTENER_HPP
