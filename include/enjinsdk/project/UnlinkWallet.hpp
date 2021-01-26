#ifndef ENJINCPPSDK_PROJECTUNLINKWALLET_HPP
#define ENJINCPPSDK_PROJECTUNLINKWALLET_HPP

#include "enjinsdk/AbstractGraphqlRequest.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::project {

/// \brief Request for unlinking a wallet from the project.
class UnlinkWallet : public graphql::AbstractGraphqlRequest {
public:
    /// \brief Default constructor.
    UnlinkWallet();

    ~UnlinkWallet() override = default;

    std::string serialize() override;

    /// \brief Sets the Ethereum address of the wallet to unlink.
    /// \param eth_address The address.
    /// \return This request for chaining.
    UnlinkWallet& set_eth_address(const std::string& eth_address);

    bool operator==(const UnlinkWallet& rhs) const;

    bool operator!=(const UnlinkWallet& rhs) const;

private:
    std::optional<std::string> eth_address;
};

}

#endif //ENJINCPPSDK_PROJECTUNLINKWALLET_HPP
