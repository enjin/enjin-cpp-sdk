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

#ifndef ENJINCPPSDK_NOTIFICATIONS_HPP
#define ENJINCPPSDK_NOTIFICATIONS_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/IDeserializable.hpp"
#include "enjinsdk/models/Pusher.hpp"
#include <memory>
#include <optional>
#include <string>

namespace enjin::sdk::models {

/// \brief Models the notification drivers and settings for the platform.
class ENJINSDK_EXPORT Notifications : public serialization::IDeserializable {
public:
    /// \brief Constructs an instance of this class.
    Notifications();

    /// \brief Constructs an instance as a copy of another.
    /// \param other The other instance.
    Notifications(const Notifications& other);

    /// \brief Constructs an instance via move.
    /// \param other The other instance being moved.
    Notifications(Notifications&& other) noexcept;

    /// \brief Deconstructs this instance.
    ~Notifications() override;

    void deserialize(const std::string& json) override;

    /// \brief Returns the Pusher settings of the platform.
    /// \return The Pusher settings.
    [[nodiscard]] const std::optional<Pusher>& get_pusher() const;

    bool operator==(const Notifications& rhs) const;

    bool operator!=(const Notifications& rhs) const;

    Notifications& operator=(const Notifications& rhs);

private:
    class Impl;

    std::unique_ptr<Impl> pimpl;
};

}

#endif //ENJINCPPSDK_NOTIFICATIONS_HPP
