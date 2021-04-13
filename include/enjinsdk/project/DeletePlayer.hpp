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
    DeletePlayer& set_id(const std::string& id);

    bool operator==(const DeletePlayer& rhs) const;

    bool operator!=(const DeletePlayer& rhs) const;

private:
    std::optional<std::string> id;
};

}

#endif //ENJINCPPSDK_PROJECTDELETEPLAYER_HPP
