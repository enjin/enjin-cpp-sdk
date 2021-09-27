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

#ifndef ENJINCPPSDK_ICLIENT_HPP
#define ENJINCPPSDK_ICLIENT_HPP

#include "enjinsdk_export.h"
#include <string>

namespace enjin::sdk {

/// \brief Interface for client implementation.
class ENJINSDK_EXPORT IClient {
public:
    /// \brief Default destructor.
    virtual ~IClient() = default;

    /// \brief Closes this client.
    virtual void close() = 0;

    /// \brief Authenticates this client with the given token.
    /// \param token The auth token.
    virtual void auth(const std::string& token) = 0;

    /// \brief Determines if this client is authenticated.
    /// \return Whether this client is authenticated.
    [[nodiscard]] virtual bool is_authenticated() const = 0;

    /// \brief Determines if this client is closed.
    /// \return Whether this client is closed.
    [[nodiscard]] virtual bool is_closed() const = 0;
};

}

#endif //ENJINCPPSDK_ICLIENT_HPP
