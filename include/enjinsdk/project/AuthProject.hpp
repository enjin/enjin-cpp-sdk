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

#ifndef ENJINCPPSDK_PROJECTAUTHPROJECT_HPP
#define ENJINCPPSDK_PROJECTAUTHPROJECT_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/internal/AbstractGraphqlRequest.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::project {

/// \brief Request to obtain the access token for a project.
class ENJINSDK_EXPORT AuthProject : public graphql::AbstractGraphqlRequest {
public:
    /// \brief Default constructor.
    AuthProject();

    ~AuthProject() override = default;

    [[nodiscard]] std::string serialize() const override;

    /// \brief Sets the project UUID.
    /// \param uuid The UUID.
    /// \return This request for chaining.
    AuthProject& set_uuid(std::string uuid);

    /// \brief Sets the secret.
    /// \param secret The secret.
    /// \return This request for chaining.
    AuthProject& set_secret(std::string secret);

    [[nodiscard]] json::JsonValue to_json() const override;

    bool operator==(const AuthProject& rhs) const;

    bool operator!=(const AuthProject& rhs) const;

private:
    std::optional<std::string> uuid_opt;
    std::optional<std::string> secret_opt;
};

}

#endif //ENJINCPPSDK_PROJECTAUTHPROJECT_HPP
