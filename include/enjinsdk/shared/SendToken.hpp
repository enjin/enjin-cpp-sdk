#ifndef ENJINCPPSDK_SHAREDSENDTOKEN_HPP
#define ENJINCPPSDK_SHAREDSENDTOKEN_HPP

#include "enjinsdk/AbstractGraphqlRequest.hpp"
#include "enjinsdk/shared/TransactionRequestArgumentsTemplate.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::shared {

/// \brief Request for sending a token (item).
class SendToken : public graphql::AbstractGraphqlRequest,
                  public TransactionRequestArgumentsTemplate<SendToken> {
public:
    /// \brief Default constructor.
    SendToken();

    ~SendToken() override = default;

    std::string serialize() override;

    /// \brief Sets the wallet address of the recipient.
    /// \param recipient_address The address.
    /// \return This request for chaining.
    SendToken& set_recipient_address(const std::string& recipient_address);

    /// \brief Sets the token (item) ID.
    /// \param token_id The ID.
    /// \return This request for chaining.
    SendToken& set_token_id(const std::string& token_id);

    /// \brief Sets the index for non-fungible items.
    /// \param token_index The index.
    /// \return This request for chaining.
    SendToken& set_token_index(const std::string& token_index);

    /// \brief Sets the amount to send.
    /// \param value The amount.
    /// \return This request for chaining.
    SendToken& set_value(const std::string& value);

    /// \brief Sets the data to forward with the transaction.
    /// \param data The data.
    /// \return This request for chaining.
    SendToken& set_data(const std::string& data);

    bool operator==(const SendToken& rhs) const;

    bool operator!=(const SendToken& rhs) const;

private:
    std::optional<std::string> recipient_address;
    std::optional<std::string> token_id;
    std::optional<std::string> token_index;
    std::optional<std::string> value;
    std::optional<std::string> data;
};

}

#endif //ENJINCPPSDK_SHAREDSENDTOKEN_HPP
