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

#ifndef ENJINCPPSDK_ACCESSTOKEN_HPP
#define ENJINCPPSDK_ACCESSTOKEN_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/IDeserializable.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::models {

/// \brief Models a successful auth object.
class ENJINSDK_EXPORT AccessToken : public serialization::IDeserializable {
public:
    /// \brief Default constructor.
    AccessToken() = default;

    ~AccessToken() override = default;

    void deserialize(const std::string& json) override;

    /// \brief Returns the auth token.
    /// \return The auth token.
    std::optional<std::string> get_token();

    /// \brief Returns the number of seconds until the auth expires.
    /// \return The number of seconds until the auth expires.
    std::optional<long> get_expires_in();

    bool operator==(const AccessToken& rhs) const;

    bool operator!=(const AccessToken& rhs) const;

private:
    std::optional<std::string> token;
    std::optional<long> expires_in;

    constexpr static char TOKEN_KEY[] = "accessToken";
    constexpr static char EXPIRES_IN_KEY[] = "expiresIn";
};

}

#endif //ENJINCPPSDK_ACCESSTOKEN_HPP
