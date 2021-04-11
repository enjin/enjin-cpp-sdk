#ifndef ENJINCPPSDK_SHAREDCREATETRADE_HPP
#define ENJINCPPSDK_SHAREDCREATETRADE_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/internal/AbstractGraphqlRequest.hpp"
#include "enjinsdk/models/Trade.hpp"
#include "enjinsdk/shared/TransactionRequestArguments.hpp"
#include <optional>
#include <string>
#include <vector>

namespace enjin::sdk::shared {

/// \brief Request for creating a trade between two wallets.
class ENJINSDK_EXPORT CreateTrade : public graphql::AbstractGraphqlRequest,
                                    public TransactionRequestArguments<CreateTrade> {
public:
    /// \brief Default constructor.
    CreateTrade();

    ~CreateTrade() override = default;

    std::string serialize() override;

    /// \brief Sets the assets the sender is asking for.
    /// \param assets The assets.
    /// \return This request for chaining.
    CreateTrade& set_asking_assets(std::vector<models::Trade> assets);

    /// \brief Sets the assets to be offered bu the sender.
    /// \param assets The assets.
    /// \return This request for chaining.
    CreateTrade& set_offering_assets(std::vector<models::Trade> assets);

    /// \brief Sets the wallet address of the recipient.
    /// \param recipient_address The address.
    /// \return This request for chaining.
    CreateTrade& set_recipient_address(const std::string& recipient_address);

    bool operator==(const CreateTrade& rhs) const;

    bool operator!=(const CreateTrade& rhs) const;

private:
    std::optional<std::vector<models::Trade>> asking_assets;
    std::optional<std::vector<models::Trade>> offering_assets;
    std::optional<std::string> recipient_address;
};

template ENJINSDK_EXPORT CreateTrade& TransactionFragmentArguments<CreateTrade>::set_with_blockchain_data();

template ENJINSDK_EXPORT CreateTrade& TransactionFragmentArguments<CreateTrade>::set_with_meta();

template ENJINSDK_EXPORT CreateTrade& TransactionFragmentArguments<CreateTrade>::set_with_encoded_data();

template ENJINSDK_EXPORT CreateTrade& TransactionFragmentArguments<CreateTrade>::set_with_asset_data();

template ENJINSDK_EXPORT CreateTrade& TransactionFragmentArguments<CreateTrade>::set_with_signed_txs();

template ENJINSDK_EXPORT CreateTrade& TransactionFragmentArguments<CreateTrade>::set_with_error();

template ENJINSDK_EXPORT CreateTrade& TransactionFragmentArguments<CreateTrade>::set_with_nonce();

template ENJINSDK_EXPORT CreateTrade& TransactionFragmentArguments<CreateTrade>::set_with_state();

template ENJINSDK_EXPORT CreateTrade& TransactionFragmentArguments<CreateTrade>::set_with_receipt();

template ENJINSDK_EXPORT CreateTrade& TransactionFragmentArguments<CreateTrade>::set_with_receipt_logs();

template ENJINSDK_EXPORT CreateTrade& TransactionFragmentArguments<CreateTrade>::set_with_log_event();

template ENJINSDK_EXPORT CreateTrade&
TransactionRequestArguments<CreateTrade>::set_eth_address(const std::string& address);

template ENJINSDK_EXPORT CreateTrade& TransactionRequestArguments<CreateTrade>::set_send(bool send);

}

#endif //ENJINCPPSDK_SHAREDCREATETRADE_HPP
