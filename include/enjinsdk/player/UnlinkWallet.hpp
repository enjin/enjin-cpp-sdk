#ifndef ENJINCPPSDK_UNLINKWALLET_HPP
#define ENJINCPPSDK_UNLINKWALLET_HPP

#include "enjinsdk/AbstractGraphqlRequest.hpp"

namespace enjin::sdk::player {

/// \brief Request for unlinking a wallet from the player
class UnlinkWallet : public graphql::AbstractGraphqlRequest {
public:
    /// \brief Default constructor.
    UnlinkWallet();

    ~UnlinkWallet() override = default;

    std::string serialize() override;

    bool operator==(const UnlinkWallet& rhs) const;

    bool operator!=(const UnlinkWallet& rhs) const;
};

}

#endif //ENJINCPPSDK_UNLINKWALLET_HPP
