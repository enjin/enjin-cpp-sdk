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

#ifndef ENJINSDK_PUSHEREVENTLISTENER_HPP
#define ENJINSDK_PUSHEREVENTLISTENER_HPP

#include "enjinsdk_export.h"
#include "ISubscriptionEventListener.hpp"
#include "PusherEvent.hpp"
#include "enjinsdk/PusherEventService.hpp"

namespace enjin::sdk::events {

/// \brief Event listener for subscribed Pusher events.
class ENJINSDK_EXPORT PusherEventListener : public pusher::ISubscriptionEventListener {
public:
    PusherEventListener() = delete;

    /// \brief Constructs the listener and interfaces with the given service to emit events to registered listeners.
    /// \param service The service.
    explicit PusherEventListener(PusherEventService* service);

    ~PusherEventListener() override = default;

    void on_event(const pusher::PusherEvent& event) override;

private:
    PusherEventService* service; // Is not to be deleted by this class
};

}

#endif //ENJINSDK_PUSHEREVENTLISTENER_HPP
