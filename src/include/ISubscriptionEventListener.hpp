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

#ifndef ENJINCPPSDK_PUSHERISUBSCRIPTIONEVENTLISTENER_HPP
#define ENJINCPPSDK_PUSHERISUBSCRIPTIONEVENTLISTENER_HPP

#include "enjinsdk_export.h"
#include "PusherEvent.hpp"

namespace enjin::pusher {

/// \brief Interface for event listener for receiving Pusher events.
class ENJINSDK_EXPORT ISubscriptionEventListener {
public:
    /// \brief Default destructor.
    virtual ~ISubscriptionEventListener() = default;

    /// \brief Handler for Pusher events.
    /// \param event The Pusher event.
    virtual void on_event(const PusherEvent& event) = 0;
};

}

#endif //ENJINCPPSDK_PUSHERISUBSCRIPTIONEVENTLISTENER_HPP
