#ifndef ENJINCPPSDK_SHAREDRESETENJAPPROVAL_HPP
#define ENJINCPPSDK_SHAREDRESETENJAPPROVAL_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/internal/AbstractGraphqlRequest.hpp"
#include "enjinsdk/shared/TransactionRequestArguments.hpp"
#include <optional>

namespace enjin::sdk::shared {

/// \brief Request for resetting the crypto items contract approval for ENJ.
class ENJINSDK_EXPORT ResetEnjApproval : public graphql::AbstractGraphqlRequest,
                                         public TransactionRequestArguments<ResetEnjApproval> {
public:
    /// \brief Default constructor.
    ResetEnjApproval();

    ~ResetEnjApproval() override = default;

    [[nodiscard]] std::string serialize() const override;

    bool operator==(const ResetEnjApproval& rhs) const;

    bool operator!=(const ResetEnjApproval& rhs) const;
};

template ENJINSDK_EXPORT ResetEnjApproval& TransactionFragmentArguments<ResetEnjApproval>::set_with_blockchain_data();

template ENJINSDK_EXPORT ResetEnjApproval& TransactionFragmentArguments<ResetEnjApproval>::set_with_meta();

template ENJINSDK_EXPORT ResetEnjApproval& TransactionFragmentArguments<ResetEnjApproval>::set_with_encoded_data();

template ENJINSDK_EXPORT ResetEnjApproval& TransactionFragmentArguments<ResetEnjApproval>::set_with_asset_data();

template ENJINSDK_EXPORT ResetEnjApproval& TransactionFragmentArguments<ResetEnjApproval>::set_with_signed_txs();

template ENJINSDK_EXPORT ResetEnjApproval& TransactionFragmentArguments<ResetEnjApproval>::set_with_error();

template ENJINSDK_EXPORT ResetEnjApproval& TransactionFragmentArguments<ResetEnjApproval>::set_with_nonce();

template ENJINSDK_EXPORT ResetEnjApproval& TransactionFragmentArguments<ResetEnjApproval>::set_with_state();

template ENJINSDK_EXPORT ResetEnjApproval& TransactionFragmentArguments<ResetEnjApproval>::set_with_receipt();

template ENJINSDK_EXPORT ResetEnjApproval& TransactionFragmentArguments<ResetEnjApproval>::set_with_receipt_logs();

template ENJINSDK_EXPORT ResetEnjApproval& TransactionFragmentArguments<ResetEnjApproval>::set_with_log_event();

template ENJINSDK_EXPORT ResetEnjApproval&
TransactionRequestArguments<ResetEnjApproval>::set_eth_address(const std::string& address);

template ENJINSDK_EXPORT ResetEnjApproval& TransactionRequestArguments<ResetEnjApproval>::set_send(bool send);

}

#endif //ENJINCPPSDK_SHAREDRESETENJAPPROVAL_HPP
