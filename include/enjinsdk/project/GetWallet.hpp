#ifndef ENJINCPPSDK_PROJECTGETWALLET_HPP
#define ENJINCPPSDK_PROJECTGETWALLET_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/internal/AbstractGraphqlRequest.hpp"
#include "enjinsdk/shared/WalletFragmentArguments.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::project {

/// \brief Request for getting a wallet from the platform.
class ENJINSDK_EXPORT GetWallet : public graphql::AbstractGraphqlRequest,
                                  public shared::WalletFragmentArguments<GetWallet> {
public:
    /// \brief Default constructor.
    GetWallet();

    ~GetWallet() override = default;

    std::string serialize() override;

    /// \brief Sets the user ID owning the wallet to get.
    /// \param user_id The user ID.
    /// \return This request for chaining.
    GetWallet& set_user_id(const std::string& user_id);

    /// \brief Sets the Ethereum address of the wallet to get.
    /// \param eth_address The address.
    /// \return This request for chaining.
    GetWallet& set_eth_address(const std::string& eth_address);

    bool operator==(const GetWallet& rhs) const;

    bool operator!=(const GetWallet& rhs) const;

private:
    std::optional<std::string> user_id;
    std::optional<std::string> eth_address;
};

}

#endif //ENJINCPPSDK_PROJECTGETWALLET_HPP
