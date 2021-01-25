#ifndef ENJINCPPSDK_GETBALANCES_HPP
#define ENJINCPPSDK_GETBALANCES_HPP

#include "enjinsdk/AbstractGraphqlRequest.hpp"
#include "enjinsdk/models/BalanceFilter.hpp"
#include "enjinsdk/shared/BalanceFragmentArgumentsTemplate.hpp"
#include "enjinsdk/shared/PaginationArgumentsTemplate.hpp"
#include <optional>

namespace enjin::sdk::shared {

/// \brief Request for getting balances on the platform.
class GetBalances : public graphql::AbstractGraphqlRequest,
                    public BalanceFragmentArgumentsTemplate<GetBalances>,
                    public PaginationArgumentsTemplate<GetBalances> {
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

#endif //ENJINCPPSDK_GETBALANCES_HPP
