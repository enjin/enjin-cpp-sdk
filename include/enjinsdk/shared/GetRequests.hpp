#ifndef ENJINCPPSDK_SHAREDGETREQUESTS_HPP
#define ENJINCPPSDK_SHAREDGETREQUESTS_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/AbstractGraphqlRequest.hpp"
#include "enjinsdk/models/TransactionFilter.hpp"
#include "enjinsdk/models/TransactionSort.hpp"
#include "enjinsdk/shared/PaginationArguments.hpp"
#include "enjinsdk/shared/TransactionFragmentArguments.hpp"
#include <optional>

namespace enjin::sdk::shared {

/// \brief Request for getting transactions on the platform.
class ENJINSDK_EXPORT GetRequests : public graphql::AbstractGraphqlRequest,
                                    public TransactionFragmentArguments<GetRequests>,
                                    public PaginationArguments<GetRequests> {
public:
    /// \brief Default constructor.
    GetRequests();

    ~GetRequests() override = default;

    std::string serialize() override;

    /// \brief Sets the filter the request will use.
    /// \param filter The filter.
    /// \return This request for chaining.
    GetRequests& set_filter(const models::TransactionFilter& filter);

    /// Sets the request to sort the results by the specified options.
    /// \param sort The sort options.
    /// \return This request for chaining.
    GetRequests& set_sort(const models::TransactionSort& sort);

    bool operator==(const GetRequests& rhs) const;

    bool operator!=(const GetRequests& rhs) const;

private:
    std::optional<models::TransactionFilter> filter;
    std::optional<models::TransactionSort> sort;
};

}

#endif //ENJINCPPSDK_SHAREDGETREQUESTS_HPP
