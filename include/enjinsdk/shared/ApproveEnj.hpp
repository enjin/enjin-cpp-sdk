#ifndef ENJINCPPSDK_SHAREDAPPROVEENJ_HPP
#define ENJINCPPSDK_SHAREDAPPROVEENJ_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/internal/AbstractGraphqlRequest.hpp"
#include "enjinsdk/shared/TransactionRequestArguments.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::shared {

/// \brief Request for approving the crypto items contract to spend ENJ.
class ENJINSDK_EXPORT ApproveEnj : public graphql::AbstractGraphqlRequest,
                                   public TransactionRequestArguments<ApproveEnj> {
public:
    /// \brief Default constructor.
    ApproveEnj();

    ~ApproveEnj() override = default;

    std::string serialize() override;

    /// \brief Sets the amount of ENJ to approve.
    /// \param value The value.
    /// \return This request for chaining.
    /// \remarks The value is in Wei as 10^18 (e.g. 1 ENJ = 1000000000000000000).
    ApproveEnj& set_value(const std::string& value);

    bool operator==(const ApproveEnj& rhs) const;

    bool operator!=(const ApproveEnj& rhs) const;

private:
    std::optional<std::string> value;
};

template ENJINSDK_EXPORT ApproveEnj& TransactionFragmentArguments<ApproveEnj>::set_with_blockchain_data();

template ENJINSDK_EXPORT ApproveEnj& TransactionFragmentArguments<ApproveEnj>::set_with_meta();

template ENJINSDK_EXPORT ApproveEnj& TransactionFragmentArguments<ApproveEnj>::set_with_encoded_data();

template ENJINSDK_EXPORT ApproveEnj& TransactionFragmentArguments<ApproveEnj>::set_with_asset_data();

template ENJINSDK_EXPORT ApproveEnj& TransactionFragmentArguments<ApproveEnj>::set_with_signed_txs();

template ENJINSDK_EXPORT ApproveEnj& TransactionFragmentArguments<ApproveEnj>::set_with_error();

template ENJINSDK_EXPORT ApproveEnj& TransactionFragmentArguments<ApproveEnj>::set_with_nonce();

template ENJINSDK_EXPORT ApproveEnj& TransactionFragmentArguments<ApproveEnj>::set_with_state();

template ENJINSDK_EXPORT ApproveEnj& TransactionFragmentArguments<ApproveEnj>::set_with_receipt();

template ENJINSDK_EXPORT ApproveEnj& TransactionFragmentArguments<ApproveEnj>::set_with_receipt_logs();

template ENJINSDK_EXPORT ApproveEnj& TransactionFragmentArguments<ApproveEnj>::set_with_log_event();

template ENJINSDK_EXPORT ApproveEnj&
TransactionRequestArguments<ApproveEnj>::set_eth_address(const std::string& address);

template ENJINSDK_EXPORT ApproveEnj& TransactionRequestArguments<ApproveEnj>::set_send(bool send);

}

#endif //ENJINCPPSDK_SHAREDAPPROVEENJ_HPP
