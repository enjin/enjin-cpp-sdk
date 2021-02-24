#ifndef ENJINCPPSDK_SHAREDCANCELTRANSACTION_HPP
#define ENJINCPPSDK_SHAREDCANCELTRANSACTION_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/AbstractGraphqlRequest.hpp"
#include <optional>

namespace enjin::sdk::shared {

/// \brief Request for canceling a transaction on the platform.
class ENJINSDK_EXPORT CancelTransaction : public graphql::AbstractGraphqlRequest {
public:
    /// \brief Default constructor.
    CancelTransaction();

    ~CancelTransaction() override = default;

    std::string serialize() override;

    /// \brief Sets the ID of the transaction to cancel.
    /// \param id The ID.
    /// \return This request for chaining.
    CancelTransaction& set_id(int id);

    bool operator==(const CancelTransaction& rhs) const;

    bool operator!=(const CancelTransaction& rhs) const;

private:
    std::optional<int> id;
};

}

#endif //ENJINCPPSDK_SHAREDCANCELTRANSACTION_HPP
