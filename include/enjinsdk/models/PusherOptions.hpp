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

#ifndef ENJINCPPSDK_PUSHEROPTIONS_HPP
#define ENJINCPPSDK_PUSHEROPTIONS_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/IDeserializable.hpp"
#include <memory>
#include <optional>
#include <string>

namespace enjin::sdk::models {

/// \brief Models Pusher options used by the platform.
class ENJINSDK_EXPORT PusherOptions : public serialization::IDeserializable {
public:
    /// \brief Constructs an instance of this class.
    PusherOptions();

    /// \brief Constructs an instance as a copy of another.
    /// \param other The other instance.
    PusherOptions(const PusherOptions& other);

    /// \brief Constructs an instance via move.
    /// \param other The other instance being moved.
    PusherOptions(PusherOptions&& other) noexcept;

    /// \brief Deconstructs this instance.
    ~PusherOptions() override;

    void deserialize(const std::string& json) override;

    /// \brief Returns the cluster the platform is in.
    /// \return The cluster.
    [[nodiscard]] const std::optional<std::string>& get_cluster() const;

    /// \brief Returns the encryption setting the platform uses.
    /// \return Whether encryption is used or not.
    [[nodiscard]] const std::optional<bool>& get_encrypted() const;

    bool operator==(const PusherOptions& rhs) const;

    bool operator!=(const PusherOptions& rhs) const;

    PusherOptions& operator=(const PusherOptions& rhs);

private:
    class Impl;

    std::unique_ptr<Impl> pimpl;
};

}

#endif //ENJINCPPSDK_PUSHEROPTIONS_HPP
