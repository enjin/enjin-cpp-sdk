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

#ifndef ENJINCPPSDK_PUSHERPUSHEROPTIONS_HPP
#define ENJINCPPSDK_PUSHERPUSHEROPTIONS_HPP

#include "enjinsdk_export.h"
#include <optional>
#include <string>

namespace enjin::pusher {

/// \brief Class for modeling options for a Pusher client.
class ENJINSDK_EXPORT PusherOptions {
public:
    /// \brief Default constructor.
    PusherOptions() = default;

    /// \brief Default destructor.
    ~PusherOptions() = default;

    /// \brief Returns the websocket host to be used by the client.
    /// \return The host.
    [[nodiscard]] std::string host() const;

    /// \brief Determines if encryption is to be used.
    /// \return Whether encryption is to be used.
    [[nodiscard]] bool is_encrypted() const;

    /// \brief Sets the cluster.
    /// \param cluster The cluster.
    /// \return This for chaining.
    PusherOptions& set_cluster(const std::string& cluster);

    /// \brief Sets whether encryption is to be used. True by default.
    /// \param encrypted The state.
    /// \return This for chaining.
    PusherOptions& set_encrypted(bool encrypted);

    /// \brief Returns the cluster.
    /// \return The optional for the cluster.
    [[nodiscard]] const std::optional<std::string>& get_cluster() const;

private:
    std::optional<std::string> cluster;
    bool encrypted = true;
};

}

#endif //ENJINCPPSDK_PUSHERPUSHEROPTIONS_HPP
