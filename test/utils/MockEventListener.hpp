#ifndef ENJINCPPSDK_MOCKEVENTLISTENER_HPP
#define ENJINCPPSDK_MOCKEVENTLISTENER_HPP

#include "enjinsdk/IEventListener.hpp"

/* Class is not a real mock due to inability to use gMock due to issue with "MOCK_METHOD" and clang-cl in GoogleTest
 * v1.10.
 */
class MockEventListener : public enjin::sdk::events::IEventListener {
public:
    MockEventListener() = default;

    ~MockEventListener() override = default;

    void notification_received(enjin::sdk::models::NotificationEvent event) override {
    }
};

#endif //ENJINCPPSDK_MOCKEVENTLISTENER_HPP
