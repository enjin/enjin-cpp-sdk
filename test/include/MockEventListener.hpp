/* Copyright 2021 Enjin Pte. Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ENJINCPPSDK_MOCKEVENTLISTENER_HPP
#define ENJINCPPSDK_MOCKEVENTLISTENER_HPP

#include "enjinsdk/IEventListener.hpp"
#include "gmock/gmock.h"

namespace enjin::test::mocks {

class MockEventListener : public sdk::events::IEventListener {
public:
    MOCK_METHOD(void, notification_received, (const sdk::models::NotificationEvent& event), (override));
};

}

#endif //ENJINCPPSDK_MOCKEVENTLISTENER_HPP
