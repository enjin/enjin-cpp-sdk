#ifndef ENJINCPPSDK_SHAREDGETTOKENS_HPP
#define ENJINCPPSDK_SHAREDGETTOKENS_HPP

#include "enjinsdk/AbstractGraphqlRequest.hpp"
#include "enjinsdk/models/Token.hpp"
#include "enjinsdk/models/TokenFilter.hpp"
#include "enjinsdk/models/TokenSort.hpp"
#include "enjinsdk/shared/PaginationArgumentsTemplate.hpp"
#include "enjinsdk/shared/TokenFragmentArgumentsTemplate.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::shared {

/// \brief Request for getting tokens (items) on the platform.
class GetTokens : public graphql::AbstractGraphqlRequest,
                  public TokenFragmentArgumentsTemplate<GetTokens>,
                  public PaginationArgumentsTemplate<GetTokens> {
public:
    /// \brief Default constructor.
    GetTokens();

    ~GetTokens() override = default;

    std::string serialize() override;

    /// \brief Sets the filter the request will use.
    /// \param filter The filter.
    /// \return This request for chaining.
    GetTokens& set_filter(const models::TokenFilter& filter);

    /// \brief Sets the request to sort the results by the specified options.
    /// \param sort The sort options.
    /// \return This request for chaining.
    GetTokens& set_sort(const models::TokenSort& sort);

    bool operator==(const GetTokens& rhs) const;

    bool operator!=(const GetTokens& rhs) const;

private:
    std::optional<models::TokenFilter> filter;
    std::optional<models::TokenSort> sort;
};

}

#endif //ENJINCPPSDK_SHAREDGETTOKENS_HPP
