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
#include <optional>
#include <string>

namespace enjin::sdk::models {

/// \brief Models a project on the platform.
class ENJINSDK_EXPORT Project : public serialization::IDeserializable {
public:
    /// \brief Default constructor.
    Project() = default;

    ~Project() override = default;

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

private:
    std::optional<std::string> uuid;
    std::optional<std::string> name;
    std::optional<std::string> description;
    std::optional<std::string> image;
    std::optional<std::string> created_at;
    std::optional<std::string> updated_at;
};

}

#endif //ENJINCPPSDK_PROJECT_HPP
