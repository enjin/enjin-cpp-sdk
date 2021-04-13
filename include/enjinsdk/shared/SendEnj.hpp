#ifndef ENJINCPPSDK_SHAREDSENDENJ_HPP
#define ENJINCPPSDK_SHAREDSENDENJ_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/internal/AbstractGraphqlRequest.hpp"
#include "enjinsdk/shared/TransactionRequestArguments.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::shared {

/// \brief Request for sending send ENJ.
class ENJINSDK_EXPORT SendEnj : public graphql::AbstractGraphqlRequest,
                                public TransactionRequestArguments<SendEnj> {
public:
    /// \brief Default constructor.
    SendEnj();

    ~SendEnj() override = default;

    [[nodiscard]] std::string serialize() const override;

    /// \brief Sets the wallet address of the recipient.
    /// \param recipient_address The address.
    /// \return This request for chaining.
    SendEnj& set_recipient_address(const std::string& recipient_address);

    /// \brief Sets the amount of ENJ to send.
    /// \param value The value.
    /// \return This request for chaining.
    /// \remarks The value is in Wei as 10^18 (e.g. 1 ENJ = 1000000000000000000).
    SendEnj& set_value(const std::string& value);

    bool operator==(const SendEnj& rhs) const;

    bool operator!=(const SendEnj& rhs) const;

private:
    std::optional<std::string> recipient_address;
    std::optional<std::string> value;
};

template ENJINSDK_EXPORT SendEnj& TransactionFragmentArguments<SendEnj>::set_with_blockchain_data();

template ENJINSDK_EXPORT SendEnj& TransactionFragmentArguments<SendEnj>::set_with_meta();

template ENJINSDK_EXPORT SendEnj& TransactionFragmentArguments<SendEnj>::set_with_encoded_data();

template ENJINSDK_EXPORT SendEnj& TransactionFragmentArguments<SendEnj>::set_with_asset_data();

template ENJINSDK_EXPORT SendEnj& TransactionFragmentArguments<SendEnj>::set_with_signed_txs();

template ENJINSDK_EXPORT SendEnj& TransactionFragmentArguments<SendEnj>::set_with_error();

template ENJINSDK_EXPORT SendEnj& TransactionFragmentArguments<SendEnj>::set_with_nonce();

template ENJINSDK_EXPORT SendEnj& TransactionFragmentArguments<SendEnj>::set_with_state();

template ENJINSDK_EXPORT SendEnj& TransactionFragmentArguments<SendEnj>::set_with_receipt();

template ENJINSDK_EXPORT SendEnj& TransactionFragmentArguments<SendEnj>::set_with_receipt_logs();

template ENJINSDK_EXPORT SendEnj& TransactionFragmentArguments<SendEnj>::set_with_log_event();

template ENJINSDK_EXPORT SendEnj& TransactionRequestArguments<SendEnj>::set_eth_address(const std::string& address);

template ENJINSDK_EXPORT SendEnj& TransactionRequestArguments<SendEnj>::set_send(bool send);

}

#endif //ENJINCPPSDK_SHAREDSENDENJ_HPP
