#ifndef ENJINCPPSDK_SHAREDCREATETRADE_HPP
#define ENJINCPPSDK_SHAREDCREATETRADE_HPP

#include "enjinsdk/AbstractGraphqlRequest.hpp"
#include "enjinsdk/models/Trade.hpp"
#include "enjinsdk/shared/TransactionRequestArgumentsTemplate.hpp"
#include <optional>
#include <string>
#include <vector>

namespace enjin::sdk::shared {

/// \brief Request for creating a trade between two wallets.
class CreateTrade : public graphql::AbstractGraphqlRequest,
                    public TransactionRequestArgumentsTemplate<CreateTrade> {
public:
    /// \brief Default constructor.
    CreateTrade();

    ~CreateTrade() override = default;

    std::string serialize() override;

    /// \brief Sets the tokens (items) the sender is asking for.
    /// \param tokens The items.
    /// \return This request for chaining.
    CreateTrade& set_asking_tokens(std::vector<models::Trade> tokens);

    /// \brief Sets the tokens (items) to be offered bu the sender.
    /// \param tokens The items.
    /// \return This request for chaining.
    CreateTrade& set_offering_tokens(std::vector<models::Trade> tokens);

    /// \brief Sets the wallet address of the recipient.
    /// \param recipient_address The address.
    /// \return This request for chaining.
    CreateTrade& set_recipient_address(const std::string& recipient_address);

    bool operator==(const CreateTrade& rhs) const;

    bool operator!=(const CreateTrade& rhs) const;

private:
    std::optional<std::vector<models::Trade>> asking_tokens;
    std::optional<std::vector<models::Trade>> offering_tokens;
    std::optional<std::string> recipient_address;
};

}

#endif //ENJINCPPSDK_SHAREDCREATETRADE_HPP
