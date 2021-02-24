#ifndef ENJINCPPSDK_SHAREDADVANCEDSENDASSET_HPP
#define ENJINCPPSDK_SHAREDADVANCEDSENDASSET_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/AbstractGraphqlRequest.hpp"
#include "enjinsdk/models/Transfer.hpp"
#include "enjinsdk/shared/TransactionRequestArgumentsTemplate.hpp"
#include <optional>
#include <string>
#include <vector>

namespace enjin::sdk::shared {

/// \brief Request for sending one or more assets in a single transaction.
class ENJINSDK_EXPORT AdvancedSendAsset : public enjin::sdk::graphql::AbstractGraphqlRequest,
                                          public TransactionRequestArgumentsTemplate<AdvancedSendAsset> {
public:
    /// \brief Default constructor.
    AdvancedSendAsset();

    ~AdvancedSendAsset() override = default;

    std::string serialize() override;

    /// \brief Sets the different transfers to perform.
    /// \param transfers The transfers.
    /// \return This request for chaining.
    AdvancedSendAsset& set_transfers(const std::vector<models::Transfer>& transfers);

    /// \brief Sets the data to forward with the transaction.
    /// \param data The data.
    /// \return This request for chaining.
    AdvancedSendAsset& set_data(const std::string& data);

    bool operator==(const AdvancedSendAsset& rhs) const;

    bool operator!=(const AdvancedSendAsset& rhs) const;

private:
    std::optional<std::vector<models::Transfer>> transfers;
    std::optional<std::string> data;
};

}

#endif //ENJINCPPSDK_SHAREDADVANCEDSENDASSET_HPP
