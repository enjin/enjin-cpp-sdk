#ifndef ENJINCPPSDK_SHAREDAPPROVEMAXENJ_HPP
#define ENJINCPPSDK_SHAREDAPPROVEMAXENJ_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/AbstractGraphqlRequest.hpp"
#include "enjinsdk/shared/TransactionRequestArguments.hpp"

namespace enjin::sdk::shared {

/// \brief Request for approving the crypto items contract to spend the maximum amount of ENJ.
class ENJINSDK_EXPORT ApproveMaxEnj : public graphql::AbstractGraphqlRequest,
                                      public TransactionRequestArguments<ApproveMaxEnj> {
public:
    /// \brief Default constructor.
    ApproveMaxEnj();

    ~ApproveMaxEnj() override = default;

    std::string serialize() override;

    bool operator==(const ApproveMaxEnj& rhs) const;

    bool operator!=(const ApproveMaxEnj& rhs) const;
};

}

#endif //ENJINCPPSDK_SHAREDAPPROVEMAXENJ_HPP
