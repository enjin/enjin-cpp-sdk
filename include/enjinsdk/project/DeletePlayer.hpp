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

#ifndef ENJINCPPSDK_PROJECTDELETEPLAYER_HPP
#define ENJINCPPSDK_PROJECTDELETEPLAYER_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/internal/AbstractGraphqlRequest.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::project {

/// \brief Request for deleting a player from the platform.
class ENJINSDK_EXPORT DeletePlayer : public graphql::AbstractGraphqlRequest {
public:
    /// \brief Default constructor.
    DeletePlayer();

    ~DeletePlayer() override = default;

    [[nodiscard]] std::string serialize() const override;

    /// \brief Sets the ID for the player to be deleted.
    /// \param id The ID.
    /// \return This request for chaining.
    DeletePlayer& set_id(std::string id);

    [[nodiscard]] json::JsonValue to_json() const override;

    bool operator==(const DeletePlayer& rhs) const;

    bool operator!=(const DeletePlayer& rhs) const;

private:
    std::optional<std::string> id_opt;
};

}

#endif //ENJINCPPSDK_PROJECTDELETEPLAYER_HPP
