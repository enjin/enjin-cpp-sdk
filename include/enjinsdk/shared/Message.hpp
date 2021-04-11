#ifndef ENJINCPPSDK_SHAREDMESSAGE_HPP
#define ENJINCPPSDK_SHAREDMESSAGE_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/internal/AbstractGraphqlRequest.hpp"
#include "enjinsdk/shared/TransactionRequestArguments.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::shared {

/// \brief Request to sign a message to prove wallet ownership.
class ENJINSDK_EXPORT Message : public graphql::AbstractGraphqlRequest,
                                public TransactionRequestArguments<Message> {
public:
    /// \brief Default constructor.
    Message();

    ~Message() override = default;

    std::string serialize() override;

    /// \brief Sets the message to sign.
    /// \param message The message.
    /// \return This request for chaining.
    Message& set_message(const std::string& message);

    bool operator==(const Message& rhs) const;

    bool operator!=(const Message& rhs) const;

private:
    std::optional<std::string> message;
};

template ENJINSDK_EXPORT Message& TransactionFragmentArguments<Message>::set_with_blockchain_data();

template ENJINSDK_EXPORT Message& TransactionFragmentArguments<Message>::set_with_meta();

template ENJINSDK_EXPORT Message& TransactionFragmentArguments<Message>::set_with_encoded_data();

template ENJINSDK_EXPORT Message& TransactionFragmentArguments<Message>::set_with_asset_data();

template ENJINSDK_EXPORT Message& TransactionFragmentArguments<Message>::set_with_signed_txs();

template ENJINSDK_EXPORT Message& TransactionFragmentArguments<Message>::set_with_error();

template ENJINSDK_EXPORT Message& TransactionFragmentArguments<Message>::set_with_nonce();

template ENJINSDK_EXPORT Message& TransactionFragmentArguments<Message>::set_with_state();

template ENJINSDK_EXPORT Message& TransactionFragmentArguments<Message>::set_with_receipt();

template ENJINSDK_EXPORT Message& TransactionFragmentArguments<Message>::set_with_receipt_logs();

template ENJINSDK_EXPORT Message& TransactionFragmentArguments<Message>::set_with_log_event();

template ENJINSDK_EXPORT Message& TransactionRequestArguments<Message>::set_eth_address(const std::string& address);

template ENJINSDK_EXPORT Message& TransactionRequestArguments<Message>::set_send(bool send);

}

#endif //ENJINCPPSDK_SHAREDMESSAGE_HPP
