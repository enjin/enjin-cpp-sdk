#ifndef ENJINCPPSDK_PROJECTGETPLAYERS_HPP
#define ENJINCPPSDK_PROJECTGETPLAYERS_HPP

#include "enjinsdk/AbstractGraphqlRequest.hpp"
#include "enjinsdk/models/PlayerFilter.hpp"
#include "enjinsdk/shared/PaginationArgumentsTemplate.hpp"
#include "enjinsdk/shared/PlayerFragmentArgumentsTemplate.hpp"
#include "optional"

namespace enjin::sdk::project {

/// \brief Request for getting players on the platform.
class GetPlayers : public graphql::AbstractGraphqlRequest,
                   public shared::PlayerFragmentArgumentsTemplate<GetPlayers>,
                   public shared::PaginationArgumentsTemplate<GetPlayers> {
public:
    /// \brief Default constructor.
    GetPlayers();

    ~GetPlayers() override = default;

    std::string serialize() override;

    /// \brief Sets the filter the request will use.
    /// \param filter The filter.
    /// \return This request for chaining.
    GetPlayers& set_filter(const models::PlayerFilter& filter);

    bool operator==(const GetPlayers& rhs) const;

    bool operator!=(const GetPlayers& rhs) const;

private:
    std::optional<models::PlayerFilter> filter;
};

}

#endif //ENJINCPPSDK_PROJECTGETPLAYERS_HPP
