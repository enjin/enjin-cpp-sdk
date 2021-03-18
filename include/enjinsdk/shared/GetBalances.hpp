#ifndef ENJINCPPSDK_SHAREDGETBALANCES_HPP
#define ENJINCPPSDK_SHAREDGETBALANCES_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/AbstractGraphqlRequest.hpp"
#include "enjinsdk/models/BalanceFilter.hpp"
#include "enjinsdk/shared/BalanceFragmentArguments.hpp"
#include "enjinsdk/shared/PaginationArguments.hpp"
#include <optional>

namespace enjin::sdk::shared {

/// \brief Request for getting balances on the platform.
class ENJINSDK_EXPORT GetBalances : public graphql::AbstractGraphqlRequest,
                                    public BalanceFragmentArguments<GetBalances>,
                                    public PaginationArguments<GetBalances> {
public:
    /// \brief Default constructor.
    GetBalances();

    ~GetBalances() override = default;

    std::string serialize() override;

    /// \brief Sets the balance filter the request will use.
    /// \param filter The filter.
    /// \return This request for chaining.
    GetBalances& set_filter(models::BalanceFilter filter);

    bool operator==(const GetBalances& rhs) const;

    bool operator!=(const GetBalances& rhs) const;

private:
    std::optional<models::BalanceFilter> filter;
};

}

#endif //ENJINCPPSDK_SHAREDGETBALANCES_HPP
