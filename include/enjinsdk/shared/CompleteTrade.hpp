#ifndef ENJINCPPSDK_SHAREDCOMPLETETRADE_HPP
#define ENJINCPPSDK_SHAREDCOMPLETETRADE_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/internal/AbstractGraphqlRequest.hpp"
#include "enjinsdk/shared/TransactionRequestArguments.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::shared {

/// \brief Request for completing a trade between two wallets.
class ENJINSDK_EXPORT CompleteTrade : public graphql::AbstractGraphqlRequest,
                                      public TransactionRequestArguments<CompleteTrade> {
public:
    /// \brief Default constructor.
    CompleteTrade();

    ~CompleteTrade() override = default;

    std::string serialize() override;

    /// \brief Sets the trade ID.
    /// \param id The ID.
    /// \return This request for chaining.
    CompleteTrade& set_trade_id(const std::string& id);

    bool operator==(const CompleteTrade& rhs) const;

    bool operator!=(const CompleteTrade& rhs) const;

private:
    std::optional<std::string> trade_id;
};

template ENJINSDK_EXPORT CompleteTrade& TransactionFragmentArguments<CompleteTrade>::set_with_blockchain_data();

template ENJINSDK_EXPORT CompleteTrade& TransactionFragmentArguments<CompleteTrade>::set_with_meta();

template ENJINSDK_EXPORT CompleteTrade& TransactionFragmentArguments<CompleteTrade>::set_with_encoded_data();

template ENJINSDK_EXPORT CompleteTrade& TransactionFragmentArguments<CompleteTrade>::set_with_asset_data();

template ENJINSDK_EXPORT CompleteTrade& TransactionFragmentArguments<CompleteTrade>::set_with_signed_txs();

template ENJINSDK_EXPORT CompleteTrade& TransactionFragmentArguments<CompleteTrade>::set_with_error();

template ENJINSDK_EXPORT CompleteTrade& TransactionFragmentArguments<CompleteTrade>::set_with_nonce();

template ENJINSDK_EXPORT CompleteTrade& TransactionFragmentArguments<CompleteTrade>::set_with_state();

template ENJINSDK_EXPORT CompleteTrade& TransactionFragmentArguments<CompleteTrade>::set_with_receipt();

template ENJINSDK_EXPORT CompleteTrade& TransactionFragmentArguments<CompleteTrade>::set_with_receipt_logs();

template ENJINSDK_EXPORT CompleteTrade& TransactionFragmentArguments<CompleteTrade>::set_with_log_event();

template ENJINSDK_EXPORT CompleteTrade&
TransactionRequestArguments<CompleteTrade>::set_eth_address(const std::string& address);

template ENJINSDK_EXPORT CompleteTrade& TransactionRequestArguments<CompleteTrade>::set_send(bool send);

}

#endif //ENJINCPPSDK_SHAREDCOMPLETETRADE_HPP
