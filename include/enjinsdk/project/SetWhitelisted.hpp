#ifndef ENJINCPPSDK_PROJECTSETWHITELISTED_HPP
#define ENJINCPPSDK_PROJECTSETWHITELISTED_HPP

#include "enjinsdk/AbstractGraphqlRequest.hpp"
#include "enjinsdk/models/Whitelisted.hpp"
#include "enjinsdk/shared/TransactionRequestArgumentsTemplate.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::project {

/// \brief Request for setting an item's whitelist.
class SetWhitelisted : public graphql::AbstractGraphqlRequest,
                       public shared::TransactionRequestArgumentsTemplate<SetWhitelisted> {
public:
    /// \brief Default constructor.
    SetWhitelisted();

    ~SetWhitelisted() override = default;

    std::string serialize() override;

    /// \brief Sets the token (item) ID.
    /// \param token_id The ID.
    /// \return This request for chaining.
    SetWhitelisted& set_token_id(const std::string& token_id);

    /// \brief Sets the account address to be added to the whitelist.
    /// \param account_address The address.
    /// \return This request for chaining.
    SetWhitelisted& set_account_address(const std::string& account_address);

    /// \brief Sets the whitelisted setting for the account.
    /// \param whitelisted The setting.
    /// \return This request for chaining.
    SetWhitelisted& set_whitelisted(models::Whitelisted whitelisted);

    /// \brief Sets the specified address for sending or receiving.
    /// \param whitelisted_address The address.
    /// \return This request for chaining.
    SetWhitelisted& set_whitelisted_address(const std::string& whitelisted_address);

    /// \brief Sets whether the whitelist setting is on or off.
    /// \param on The setting.
    /// \return This request for chaining.
    SetWhitelisted& set_on(bool on);

    bool operator==(const SetWhitelisted& rhs) const;

    bool operator!=(const SetWhitelisted& rhs) const;

private:
    std::optional<std::string> token_id;
    std::optional<std::string> account_address;
    std::optional<models::Whitelisted> whitelisted;
    std::optional<std::string> whitelisted_address;
    std::optional<bool> on;
};

}

#endif //ENJINCPPSDK_PROJECTSETWHITELISTED_HPP
