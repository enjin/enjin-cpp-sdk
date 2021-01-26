#ifndef ENJINCPPSDK_DELETEPLAYER_HPP
#define ENJINCPPSDK_DELETEPLAYER_HPP

#include "enjinsdk/AbstractGraphqlRequest.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::project {

/// \brief Request for deleting a player from the platform.
class DeletePlayer : public graphql::AbstractGraphqlRequest {
public:
    /// \brief Default constructor.
    DeletePlayer();

    ~DeletePlayer() override = default;

    std::string serialize() override;

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

#endif //ENJINCPPSDK_DELETEPLAYER_HPP
