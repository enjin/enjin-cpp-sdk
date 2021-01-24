#ifndef ENJINCPPSDK_APPROVEMAXENJ_HPP
#define ENJINCPPSDK_APPROVEMAXENJ_HPP

#include "enjinsdk/AbstractGraphqlRequest.hpp"
#include "enjinsdk/shared/TransactionRequestArgumentsTemplate.hpp"

namespace enjin::sdk::shared {

/// \brief Request for approving the crypto items contract to spend the maximum amount of ENJ.
class ApproveMaxEnj : public graphql::AbstractGraphqlRequest,
                      public TransactionRequestArgumentsTemplate<ApproveMaxEnj> {
public:
    /// \brief Default constructor.
    ApproveMaxEnj();

    ~ApproveMaxEnj() override = default;

    std::string serialize() override;

    bool operator==(const ApproveMaxEnj& rhs) const;

    bool operator!=(const ApproveMaxEnj& rhs) const;
};

}

#endif //ENJINCPPSDK_APPROVEMAXENJ_HPP
