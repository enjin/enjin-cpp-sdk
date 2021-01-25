#ifndef ENJINCPPSDK_GETWALLET_HPP
#define ENJINCPPSDK_GETWALLET_HPP

#include "enjinsdk/AbstractGraphqlRequest.hpp"
#include "enjinsdk/shared/WalletFragmentArgumentsTemplate.hpp"

namespace enjin::sdk::player {

/// \brief Request for getting the player's wallet.
class GetWallet : public graphql::AbstractGraphqlRequest,
                  public shared::WalletFragmentArgumentsTemplate<GetWallet> {
public:
    /// \brief Default constructor.
    GetWallet();

    ~GetWallet() override = default;

    std::string serialize() override;

    bool operator==(const GetWallet& rhs) const;

    bool operator!=(const GetWallet& rhs) const;
};

}

#endif //ENJINCPPSDK_GETWALLET_HPP
