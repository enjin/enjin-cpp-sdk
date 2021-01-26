#ifndef ENJINCPPSDK_SHAREDRESETENJAPPROVAL_HPP
#define ENJINCPPSDK_SHAREDRESETENJAPPROVAL_HPP

#include "enjinsdk/AbstractGraphqlRequest.hpp"
#include "enjinsdk/shared/TransactionRequestArgumentsTemplate.hpp"
#include <optional>

namespace enjin::sdk::shared {

/// \brief Request for resetting the crypto items contract approval for ENJ.
class ResetEnjApproval : public graphql::AbstractGraphqlRequest,
                         public TransactionRequestArgumentsTemplate<ResetEnjApproval> {
public:
    /// \brief Default constructor.
    ResetEnjApproval();

    ~ResetEnjApproval() override = default;

    std::string serialize() override;

    bool operator==(const ResetEnjApproval& rhs) const;

    bool operator!=(const ResetEnjApproval& rhs) const;
};

}

#endif //ENJINCPPSDK_SHAREDRESETENJAPPROVAL_HPP
