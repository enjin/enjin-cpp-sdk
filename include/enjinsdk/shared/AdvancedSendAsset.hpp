#ifndef ENJINCPPSDK_SHAREDADVANCEDSENDASSET_HPP
#define ENJINCPPSDK_SHAREDADVANCEDSENDASSET_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/internal/AbstractGraphqlRequest.hpp"
#include "enjinsdk/models/Transfer.hpp"
#include "enjinsdk/shared/TransactionRequestArguments.hpp"
#include <optional>
#include <string>
#include <vector>

namespace enjin::sdk::shared {

/// \brief Request for sending one or more assets in a single transaction.
class ENJINSDK_EXPORT AdvancedSendAsset : public graphql::AbstractGraphqlRequest,
                                          public TransactionRequestArguments<AdvancedSendAsset> {
public:
    /// \brief Default constructor.
    AdvancedSendAsset();

    ~AdvancedSendAsset() override = default;

    std::string serialize() override;

    /// \brief Sets the different transfers to perform.
    /// \param transfers The transfers.
    /// \return This request for chaining.
    AdvancedSendAsset& set_transfers(const std::vector<models::Transfer>& transfers);

    /// \brief Sets the data to forward with the transaction.
    /// \param data The data.
    /// \return This request for chaining.
    AdvancedSendAsset& set_data(const std::string& data);

    bool operator==(const AdvancedSendAsset& rhs) const;

    bool operator!=(const AdvancedSendAsset& rhs) const;

private:
    std::optional<std::vector<models::Transfer>> transfers;
    std::optional<std::string> data;
};

template ENJINSDK_EXPORT AdvancedSendAsset& TransactionFragmentArguments<AdvancedSendAsset>::set_with_blockchain_data();

template ENJINSDK_EXPORT AdvancedSendAsset& TransactionFragmentArguments<AdvancedSendAsset>::set_with_meta();

template ENJINSDK_EXPORT AdvancedSendAsset& TransactionFragmentArguments<AdvancedSendAsset>::set_with_encoded_data();

template ENJINSDK_EXPORT AdvancedSendAsset& TransactionFragmentArguments<AdvancedSendAsset>::set_with_asset_data();

template ENJINSDK_EXPORT AdvancedSendAsset& TransactionFragmentArguments<AdvancedSendAsset>::set_with_signed_txs();

template ENJINSDK_EXPORT AdvancedSendAsset& TransactionFragmentArguments<AdvancedSendAsset>::set_with_error();

template ENJINSDK_EXPORT AdvancedSendAsset& TransactionFragmentArguments<AdvancedSendAsset>::set_with_nonce();

template ENJINSDK_EXPORT AdvancedSendAsset& TransactionFragmentArguments<AdvancedSendAsset>::set_with_state();

template ENJINSDK_EXPORT AdvancedSendAsset& TransactionFragmentArguments<AdvancedSendAsset>::set_with_receipt();

template ENJINSDK_EXPORT AdvancedSendAsset& TransactionFragmentArguments<AdvancedSendAsset>::set_with_receipt_logs();

template ENJINSDK_EXPORT AdvancedSendAsset& TransactionFragmentArguments<AdvancedSendAsset>::set_with_log_event();

template ENJINSDK_EXPORT AdvancedSendAsset&
TransactionRequestArguments<AdvancedSendAsset>::set_eth_address(const std::string& address);

template ENJINSDK_EXPORT AdvancedSendAsset& TransactionRequestArguments<AdvancedSendAsset>::set_send(bool send);

}

#endif //ENJINCPPSDK_SHAREDADVANCEDSENDASSET_HPP
