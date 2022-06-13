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

#ifndef ENJINCPPSDK_PLAYERFILTER_HPP
#define ENJINCPPSDK_PLAYERFILTER_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/ISerializable.hpp"
#include <optional>
#include <string>
#include <vector>

namespace enjin::sdk::models {

/// \brief Models a filter input for player queries.
class ENJINSDK_EXPORT PlayerFilter : public serialization::ISerializable {
public:
    /// \brief Default constructor.
    PlayerFilter() = default;

    ~PlayerFilter() override = default;

    [[nodiscard]] std::string serialize() const override;

    /// \brief Sets the filter to include other filters to intersect with.
    /// \param others The other filters.
    /// \return This filter for chaining.
    PlayerFilter& set_and(std::vector<PlayerFilter> others);

    /// \brief Sets the filter to include other filters to union with.
    /// \param others The other filters.
    /// \return This filter for chaining.
    PlayerFilter& set_or(std::vector<PlayerFilter> others);

    /// \brief Sets the player ID to filter for.
    /// \param id The player ID.
    /// \return This filter for chaining.
    PlayerFilter& set_id(std::string id);

    /// \brief Sets the player IDs to filter for.
    /// \param ids The player IDs.
    /// \return This filter for chaining.
    PlayerFilter& set_id_in(std::vector<std::string> ids);

    [[nodiscard]] json::JsonValue to_json() const override;

    bool operator==(const PlayerFilter& rhs) const;

    bool operator!=(const PlayerFilter& rhs) const;

private:
    std::optional<std::vector<PlayerFilter>> and_filters_opt;
    std::optional<std::vector<PlayerFilter>> or_filters_opt;
    std::optional<std::string> id_opt;
    std::optional<std::vector<std::string>> id_in_opt;
};

}

#endif //ENJINCPPSDK_PLAYERFILTER_HPP
