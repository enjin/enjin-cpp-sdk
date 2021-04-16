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

#ifndef ENJINCPPSDK_PUSHERCONNECTIONSTATE_HPP
#define ENJINCPPSDK_PUSHERCONNECTIONSTATE_HPP

namespace enjin::pusher {

/// \brief Enums for different connection states for a Pusher client.
enum class ConnectionState {
    CONNECTING,
    CONNECTED,
    DISCONNECTING,
    DISCONNECTED,
    RECONNECTING,
    ALL, ///< \brief Value used to indicate any state when used as a function argument.
};

}

#endif //ENJINCPPSDK_PUSHERCONNECTIONSTATE_HPP
