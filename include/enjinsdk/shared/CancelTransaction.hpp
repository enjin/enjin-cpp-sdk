#ifndef ENJINCPPSDK_CANCELTRANSACTION_HPP
#define ENJINCPPSDK_CANCELTRANSACTION_HPP

#include "enjinsdk/AbstractGraphqlRequest.hpp"
#include <optional>

namespace enjin::sdk::shared {

/// \brief Request for canceling a transaction on the platform.
class CancelTransaction : public graphql::AbstractGraphqlRequest {
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

#endif //ENJINCPPSDK_CANCELTRANSACTION_HPP
