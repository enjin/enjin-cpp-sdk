#ifndef ENJINCPPSDK_PLAYERUNLINKWALLET_HPP
#define ENJINCPPSDK_PLAYERUNLINKWALLET_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/internal/AbstractGraphqlRequest.hpp"

namespace enjin::sdk::player {

/// \brief Request for unlinking a wallet from the player
class ENJINSDK_EXPORT UnlinkWallet : public graphql::AbstractGraphqlRequest {
public:
    /// \brief Default constructor.
    UnlinkWallet();

    ~UnlinkWallet() override = default;

    std::string serialize() override;

    bool operator==(const UnlinkWallet& rhs) const;

    bool operator!=(const UnlinkWallet& rhs) const;
};

}

#endif //ENJINCPPSDK_PLAYERUNLINKWALLET_HPP
