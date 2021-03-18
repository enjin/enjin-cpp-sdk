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

    /// \brief Returns the ID of this project.
    /// \return The ID.
    [[nodiscard]] const std::optional<int>& get_id() const;

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
    std::optional<int> id;
    std::optional<std::string> name;
    std::optional<std::string> description;
    std::optional<std::string> image;
    std::optional<std::string> created_at;
    std::optional<std::string> updated_at;

    constexpr static char ID_KEY[] = "id";
    constexpr static char NAME_KEY[] = "name";
    constexpr static char DESCRIPTION_KEY[] = "description";
    constexpr static char IMAGE_KEY[] = "image";
    constexpr static char CREATED_AT_KEY[] = "createdAt";
    constexpr static char UPDATED_AT_KEY[] = "updatedAt";
};

}

#endif //ENJINCPPSDK_PROJECT_HPP
