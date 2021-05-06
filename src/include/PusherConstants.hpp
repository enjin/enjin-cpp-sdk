/* Copyright 2021 Enjin Pte Ltd.
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

#ifndef ENJINCPPSDK_PUSHERCONSTANTS_HPP
#define ENJINCPPSDK_PUSHERCONSTANTS_HPP

#include "enjinsdk_export.h"

namespace enjin::pusher {

/// \brief Constants used in the Pusher protocol.
class ENJINSDK_EXPORT PusherConstants {
public:
    /// \brief Prefix for Pusher messages.
    static constexpr char PUSHER_MESSAGE_PREFIX[] = "pusher";

    // Message keys

    /// \brief Key for subscribe messages.
    static constexpr char CHANNEL_SUBSCRIBE[] = "pusher:subscribe";
    /// \brief Key for unsubscribe messages.
    static constexpr char CHANNEL_UNSUBSCRIBE[] = "pusher:unsubscribe";
    /// \brief Key for subscription succeeded message.
    static constexpr char CHANNEL_SUBSCRIPTION_SUCCEEDED[] = "pusher_internal:subscription_succeed";
    /// \brief Key for subscription error message.
    static constexpr char CHANNEL_SUBSCRIPTION_ERROR[] = "pusher_internal:subscription_error";

    // Protocol schemas

    /// \brief Schema for not using encryption.
    static constexpr char INSECURE_SCHEMA[] = "ws://";
    /// \brief Schema for using encryption.
    static constexpr char SECURE_SCHEMA[] = "wss://";
};

}

#endif //ENJINCPPSDK_PUSHERCONSTANTS_HPP
