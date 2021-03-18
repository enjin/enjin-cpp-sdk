#ifndef ENJINCPPSDK_SHAREDCOMPLETETRADE_HPP
#define ENJINCPPSDK_SHAREDCOMPLETETRADE_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/AbstractGraphqlRequest.hpp"
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

}

#endif //ENJINCPPSDK_SHAREDCOMPLETETRADE_HPP
