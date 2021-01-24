#ifndef ENJINCPPSDK_SENDENJ_HPP
#define ENJINCPPSDK_SENDENJ_HPP

#include "enjinsdk/AbstractGraphqlRequest.hpp"
#include "enjinsdk/shared/TransactionRequestArgumentsTemplate.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::shared {

/// \brief Request for sending send ENJ.
class SendEnj : public graphql::AbstractGraphqlRequest,
                public TransactionRequestArgumentsTemplate<SendEnj> {
public:
    /// \brief Default constructor.
    SendEnj();

    ~SendEnj() override = default;

    std::string serialize() override;

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

}

#endif //ENJINCPPSDK_SENDENJ_HPP
