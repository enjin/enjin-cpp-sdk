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

#ifndef ENJINCPPSDK_TRUSTEDPLATFORMHANDLER_HPP
#define ENJINCPPSDK_TRUSTEDPLATFORMHANDLER_HPP

#include "enjinsdk_export.h"
#include <mutex>
#include <optional>
#include <string>

namespace enjin::sdk::http {

/// \brief Class for handling aspects of communication with the platform.
class ENJINSDK_EXPORT TrustedPlatformHandler {
public:
    /// \brief The schema of the Authorization request header.
    static constexpr char AUTHORIZATION_SCHEMA[] = "Bearer";

    /// \brief The prefix for the default user agent value of this SDK in "<product>/<version>" format.
    static constexpr char USER_AGENT_PREFIX[] = "Enjin-CPP-SDK/v";

    /// \brief Default constructor.
    TrustedPlatformHandler() = default;

    /// \brief Default destructor.
    ~TrustedPlatformHandler() = default;

    /// \brief Determines if the handler is authenticated.
    /// \return Whether the handler is authenticated.
    [[nodiscard]] bool is_authenticated() const;

    /// \brief Sets the auth token for the handler.
    /// \param auth_token The auth token.
    void set_auth_token(std::string auth_token);

    /// \brief Returns the auth token for the handler.
    /// \return The optional with containing the auth token.
    [[nodiscard]] const std::optional<std::string>& get_auth_token() const;

private:
    std::optional<std::string> auth_token;

    // Mutex
    mutable std::mutex auth_token_mutex;
};

}

#endif //ENJINCPPSDK_TRUSTEDPLATFORMHANDLER_HPP
