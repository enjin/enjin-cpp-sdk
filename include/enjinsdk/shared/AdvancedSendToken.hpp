#ifndef ENJINCPPSDK_SHAREDADVANCEDSENDTOKEN_HPP
#define ENJINCPPSDK_SHAREDADVANCEDSENDTOKEN_HPP

#include "enjinsdk/AbstractGraphqlRequest.hpp"
#include "enjinsdk/models/Transfer.hpp"
#include "enjinsdk/shared/TransactionRequestArgumentsTemplate.hpp"
#include <optional>
#include <string>
#include <vector>

namespace enjin::sdk::shared {

/// \brief Request for sending one or more items in a single transaction.
class AdvancedSendToken : public enjin::sdk::graphql::AbstractGraphqlRequest,
                          public TransactionRequestArgumentsTemplate<AdvancedSendToken> {
public:
    /// \brief Default constructor.
    AdvancedSendToken();

    ~AdvancedSendToken() override = default;

    std::string serialize() override;

    /// \brief Sets the different transfers to perform.
    /// \param transfers The transfers.
    /// \return This request for chaining.
    AdvancedSendToken& set_transfers(const std::vector<models::Transfer>& transfers);

    /// \brief Sets the data to forward with the transaction.
    /// \param data The data.
    /// \return This request for chaining.
    AdvancedSendToken& set_data(const std::string& data);

    bool operator==(const AdvancedSendToken& rhs) const;

    bool operator!=(const AdvancedSendToken& rhs) const;

private:
    std::optional<std::vector<models::Transfer>> transfers;
    std::optional<std::string> data;
};

}

#endif //ENJINCPPSDK_SHAREDADVANCEDSENDTOKEN_HPP
