#ifndef ENJINCPPSDK_PROJECTDECREASEMAXTRANSFERFEE_HPP
#define ENJINCPPSDK_PROJECTDECREASEMAXTRANSFERFEE_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/internal/AbstractGraphqlRequest.hpp"
#include "enjinsdk/shared/TransactionRequestArguments.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::project {

/// \brief Request for setting an asset's max transfer fee to a lower value.
class ENJINSDK_EXPORT DecreaseMaxTransferFee : public graphql::AbstractGraphqlRequest,
                                               public shared::TransactionRequestArguments<DecreaseMaxTransferFee> {
public:
    /// \brief Default constructor.
    DecreaseMaxTransferFee();

    ~DecreaseMaxTransferFee() override = default;

    std::string serialize() override;

    /// \brief Sets the asset ID.
    /// \param asset_id The ID.
    /// \return This request for chaining.
    DecreaseMaxTransferFee& set_asset_id(const std::string& asset_id);

    /// \brief Sets the index for non-fungible assets.
    /// \param asset_index The index.
    /// \return This request for chaining.
    DecreaseMaxTransferFee& set_asset_index(const std::string& asset_index);

    /// \brief Sets the new max transfer fee in Wei.
    /// \param max_transfer_fee The new fee.
    /// \return This request for chaining.
    DecreaseMaxTransferFee& set_max_transfer_fee(int max_transfer_fee);

    bool operator==(const DecreaseMaxTransferFee& rhs) const;

    bool operator!=(const DecreaseMaxTransferFee& rhs) const;

private:
    std::optional<std::string> asset_id;
    std::optional<std::string> asset_index;
    std::optional<int> max_transfer_fee;
};

}

namespace enjin::sdk::shared {

template ENJINSDK_EXPORT project::DecreaseMaxTransferFee&
TransactionFragmentArguments<project::DecreaseMaxTransferFee>::set_with_blockchain_data();

template ENJINSDK_EXPORT project::DecreaseMaxTransferFee&
TransactionFragmentArguments<project::DecreaseMaxTransferFee>::set_with_meta();

template ENJINSDK_EXPORT project::DecreaseMaxTransferFee&
TransactionFragmentArguments<project::DecreaseMaxTransferFee>::set_with_encoded_data();

template ENJINSDK_EXPORT project::DecreaseMaxTransferFee&
TransactionFragmentArguments<project::DecreaseMaxTransferFee>::set_with_asset_data();

template ENJINSDK_EXPORT project::DecreaseMaxTransferFee&
TransactionFragmentArguments<project::DecreaseMaxTransferFee>::set_with_signed_txs();

template ENJINSDK_EXPORT project::DecreaseMaxTransferFee&
TransactionFragmentArguments<project::DecreaseMaxTransferFee>::set_with_error();

template ENJINSDK_EXPORT project::DecreaseMaxTransferFee&
TransactionFragmentArguments<project::DecreaseMaxTransferFee>::set_with_nonce();

template ENJINSDK_EXPORT project::DecreaseMaxTransferFee&
TransactionFragmentArguments<project::DecreaseMaxTransferFee>::set_with_state();

template ENJINSDK_EXPORT project::DecreaseMaxTransferFee&
TransactionFragmentArguments<project::DecreaseMaxTransferFee>::set_with_receipt();

template ENJINSDK_EXPORT project::DecreaseMaxTransferFee&
TransactionFragmentArguments<project::DecreaseMaxTransferFee>::set_with_receipt_logs();

template ENJINSDK_EXPORT project::DecreaseMaxTransferFee&
TransactionFragmentArguments<project::DecreaseMaxTransferFee>::set_with_log_event();

template ENJINSDK_EXPORT project::DecreaseMaxTransferFee&
TransactionRequestArguments<project::DecreaseMaxTransferFee>::set_eth_address(const std::string& address);

template ENJINSDK_EXPORT project::DecreaseMaxTransferFee&
TransactionRequestArguments<project::DecreaseMaxTransferFee>::set_send(bool send);

}

#endif //ENJINCPPSDK_PROJECTDECREASEMAXTRANSFERFEE_HPP
