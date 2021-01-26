#ifndef ENJINCPPSDK_PROJECTGETWALLETS_HPP
#define ENJINCPPSDK_PROJECTGETWALLETS_HPP

#include "enjinsdk/AbstractGraphqlRequest.hpp"
#include "enjinsdk/shared/PaginationArgumentsTemplate.hpp"
#include "enjinsdk/shared/WalletFragmentArgumentsTemplate.hpp"
#include <optional>
#include <string>
#include <vector>

namespace enjin::sdk::project {

/// \brief Request for getting wallets from the platform.
class GetWallets : public graphql::AbstractGraphqlRequest,
                   public shared::WalletFragmentArgumentsTemplate<GetWallets>,
                   public shared::PaginationArgumentsTemplate<GetWallets> {
public:
    /// \brief Default constructor.
    GetWallets();

    ~GetWallets() override = default;

    std::string serialize() override;

    /// \brief Sets the user IDs owning the wallets to get.
    /// \param user_ids The IDs.
    /// \return This request for chaining.
    GetWallets& set_user_ids(const std::vector<std::string>& user_ids);

    /// \brief Sets the Ethereum addresses of the wallets to get.
    /// \param eth_addresses The addresses.
    /// \return This request for chaining.
    GetWallets& set_eth_addresses(const std::vector<std::string>& eth_addresses);

    bool operator==(const GetWallets& rhs) const;

    bool operator!=(const GetWallets& rhs) const;

private:
    std::optional<std::vector<std::string>> user_ids;
    std::optional<std::vector<std::string>> eth_addresses;
};

}

#endif //ENJINCPPSDK_PROJECTGETWALLETS_HPP
