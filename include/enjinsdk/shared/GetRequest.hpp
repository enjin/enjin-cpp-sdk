#ifndef ENJINCPPSDK_SHAREDGETREQUEST_HPP
#define ENJINCPPSDK_SHAREDGETREQUEST_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/AbstractGraphqlRequest.hpp"
#include "enjinsdk/shared/TransactionFragmentArguments.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::shared {

/// \brief Request for getting a transaction on the platform.
class ENJINSDK_EXPORT GetRequest : public graphql::AbstractGraphqlRequest,
                                   public TransactionFragmentArguments<GetRequest> {
public:
    /// \brief Default constructor.
    GetRequest();

    ~GetRequest() override = default;

    std::string serialize() override;

    /// \brief Sets the transaction ID.
    /// \param id The ID.
    /// \return This request for chaining.
    GetRequest& set_id(int id);

    /// \brief Sets the transaction hash ID.
    /// \param id The hash ID.
    /// \return This request for chaining.
    GetRequest& set_transaction_id(const std::string& id);

    bool operator==(const GetRequest& rhs) const;

    bool operator!=(const GetRequest& rhs) const;

private:
    std::optional<int> id;
    std::optional<std::string> transaction_id;
};

}

#endif //ENJINCPPSDK_SHAREDGETREQUEST_HPP
