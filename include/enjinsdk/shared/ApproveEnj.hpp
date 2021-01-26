#ifndef ENJINCPPSDK_SHAREDAPPROVEENJ_HPP
#define ENJINCPPSDK_SHAREDAPPROVEENJ_HPP

#include "enjinsdk/AbstractGraphqlRequest.hpp"
#include "enjinsdk/shared/TransactionRequestArgumentsTemplate.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::shared {

/// \brief Request for approving the crypto items contract to spend ENJ.
class ApproveEnj : public graphql::AbstractGraphqlRequest,
                   public TransactionRequestArgumentsTemplate<ApproveEnj> {
public:
    /// \brief Default constructor.
    ApproveEnj();

    ~ApproveEnj() override = default;

    std::string serialize() override;

    /// \brief Sets the amount of ENJ to approve.
    /// \param value The value.
    /// \return This request for chaining.
    /// \remarks The value is in Wei as 10^18 (e.g. 1 ENJ = 1000000000000000000).
    ApproveEnj& set_value(const std::string& value);

    bool operator==(const ApproveEnj& rhs) const;

    bool operator!=(const ApproveEnj& rhs) const;

private:
    std::optional<std::string> value;
};

}

#endif //ENJINCPPSDK_SHAREDAPPROVEENJ_HPP
