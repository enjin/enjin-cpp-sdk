#ifndef ENJINCPPSDK_RELEASERESERVE_HPP
#define ENJINCPPSDK_RELEASERESERVE_HPP

#include "enjinsdk/AbstractGraphqlRequest.hpp"
#include "enjinsdk/shared/TransactionRequestArgumentsTemplate.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::project {

/// \brief Request for releasing the reserve of an item.
class ReleaseReserve : public graphql::AbstractGraphqlRequest,
                       public shared::TransactionRequestArgumentsTemplate<ReleaseReserve> {
public:
    /// \brief Default constructor.
    ReleaseReserve();

    ~ReleaseReserve() override = default;

    std::string serialize() override;

    /// \brief Sets the token ID.
    /// \param token_id The ID.
    /// \return This request for chaining.
    ReleaseReserve& set_token_id(const std::string& token_id);

    /// \brief Sets the amount to release.
    /// \param value The amount.
    /// \return This request for chaining.
    ReleaseReserve& set_value(const std::string& value);

    bool operator==(const ReleaseReserve& rhs) const;

    bool operator!=(const ReleaseReserve& rhs) const;

private:
    std::optional<std::string> token_id;
    std::optional<std::string> value;
};

}

#endif //ENJINCPPSDK_RELEASERESERVE_HPP
