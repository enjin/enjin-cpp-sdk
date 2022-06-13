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

#ifndef ENJINCPPSDK_PROJECT_HPP
#define ENJINCPPSDK_PROJECT_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/IDeserializable.hpp"
#include <memory>
#include <optional>
#include <string>

namespace enjin::sdk::models {

/// \brief Models a project on the platform.
class ENJINSDK_EXPORT Project : public serialization::IDeserializable {
public:
    /// \brief Constructs an instance of this class.
    Project();

    /// \brief Constructs an instance as a copy of another.
    /// \param other The other instance.
    Project(const Project& other);

    /// \brief Constructs an instance via move.
    /// \param other The other instance being moved.
    Project(Project&& other) noexcept;

    /// \brief Deconstructs this instance.
    ~Project() override;

    void deserialize(const std::string& json) override;

    /// \brief Returns the UUID of this project.
    /// \return The UUID.
    [[nodiscard]] const std::optional<std::string>& get_uuid() const;

    /// \brief Returns the name of this project.
    /// \return The name.
    [[nodiscard]] const std::optional<std::string>& get_name() const;

    /// \brief Returns the description of this project.
    /// \return The description.
    [[nodiscard]] const std::optional<std::string>& get_description() const;

    /// \brief Returns the URL for the image of this project.
    /// \return The URL.
    [[nodiscard]] const std::optional<std::string>& get_image() const;

    /// \brief Returns the datetime when this project was created.
    /// \return The datetime.
    /// \remarks The datetime is formatted using the ISO 8601 date format.
    [[nodiscard]] const std::optional<std::string>& get_created_at() const;

    /// \brief Returns the datetime when this project was last updated.
    /// \return The datetime.
    /// \remarks The datetime is formatted using the ISO 8601 date format.
    [[nodiscard]] const std::optional<std::string>& get_updated_at() const;

    bool operator==(const Project& rhs) const;

    bool operator!=(const Project& rhs) const;

    Project& operator=(const Project& rhs);

private:
    class Impl;

    std::unique_ptr<Impl> pimpl;
};

}

#endif //ENJINCPPSDK_PROJECT_HPP
