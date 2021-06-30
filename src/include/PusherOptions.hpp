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
#include <chrono>
#include <optional>
#include <string>

namespace enjin::pusher {

/// \brief Class for modeling options for a Pusher client.
class ENJINSDK_EXPORT PusherOptions {
public:
    /// \brief The default cluster used by a client.
    static constexpr char DEFAULT_CLUSTER[] = "mt1";

    /// \brief The default encryption state used by a client.
    static constexpr bool DEFAULT_ENCRYPTION = true;

    /// \brief The default timeout duration for asynchronous operations used by a client.
    static constexpr std::chrono::milliseconds DEFAULT_CLIENT_TIMEOUT = std::chrono::milliseconds(30000);

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

    /// \brief Sets the timeout duration to wait for a asynchronous operation to complete.
    /// \tparam Rep An arithmetic type representing the number of ticks.
    /// \tparam Period A std::ratio representing the tick period (i.e. the number of seconds per tick).
    /// \param timeout The timeout duration.
    /// \return This for chaining.
    template<typename Rep, typename Period>
    inline PusherOptions& set_client_timeout(const std::chrono::duration<Rep, Period>& timeout) {
        client_timeout = std::chrono::duration_cast<std::chrono::milliseconds>(timeout);
        return *this;
    }

    /// \brief Returns the cluster if set, otherwise returns DEFAULT_CLUSTER.
    /// \return The cluster.
    [[nodiscard]] std::string get_cluster() const;

    /// \brief Returns the client timeout duration if set, otherwise returns DEFAULT_CLIENT_TIMEOUT.
    /// \return The timeout duration.
    [[nodiscard]] std::chrono::milliseconds get_client_timeout() const;

private:
    std::optional<std::string> cluster;
    std::optional<bool> encrypted;
    std::optional<std::chrono::milliseconds> client_timeout;
};

}

#endif //ENJINCPPSDK_PUSHERPUSHEROPTIONS_HPP
