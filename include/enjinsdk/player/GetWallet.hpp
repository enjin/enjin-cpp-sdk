#ifndef ENJINCPPSDK_PLAYERGETWALLET_HPP
#define ENJINCPPSDK_PLAYERGETWALLET_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/internal/AbstractGraphqlRequest.hpp"
#include "enjinsdk/shared/WalletFragmentArguments.hpp"

namespace enjin::sdk::player {

/// \brief Request for getting the player's wallet.
class ENJINSDK_EXPORT GetWallet : public graphql::AbstractGraphqlRequest,
                                  public shared::WalletFragmentArguments<GetWallet> {
public:
    /// \brief Default constructor.
    GetWallet();

    ~GetWallet() override = default;

    std::string serialize() override;

    bool operator==(const GetWallet& rhs) const;

    bool operator!=(const GetWallet& rhs) const;
};

}

namespace enjin::sdk::shared {

template ENJINSDK_EXPORT player::GetWallet& WalletFragmentArguments<player::GetWallet>::set_with_assets_created();

}

#endif //ENJINCPPSDK_PLAYERGETWALLET_HPP
