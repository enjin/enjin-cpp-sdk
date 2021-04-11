#ifndef ENJINCPPSDK_SHAREDGETBALANCES_HPP
#define ENJINCPPSDK_SHAREDGETBALANCES_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/internal/AbstractGraphqlRequest.hpp"
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

template ENJINSDK_EXPORT GetBalances&
BalanceFragmentArguments<GetBalances>::set_bal_id_format(models::AssetIdFormat bal_id_format);

template ENJINSDK_EXPORT GetBalances&
BalanceFragmentArguments<GetBalances>::set_bal_index_format(models::AssetIndexFormat bal_index_format);

template ENJINSDK_EXPORT GetBalances& BalanceFragmentArguments<GetBalances>::set_with_bal_project_id();

template ENJINSDK_EXPORT GetBalances& BalanceFragmentArguments<GetBalances>::set_with_bal_wallet_address();

template ENJINSDK_EXPORT GetBalances&
PaginationArguments<GetBalances>::set_pagination(models::PaginationOptions pagination);

template ENJINSDK_EXPORT GetBalances& PaginationArguments<GetBalances>::set_pagination(int page, int limit);

}

#endif //ENJINCPPSDK_SHAREDGETBALANCES_HPP
