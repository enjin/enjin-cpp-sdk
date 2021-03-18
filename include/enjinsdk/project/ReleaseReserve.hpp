#ifndef ENJINCPPSDK_PROJECTRELEASERESERVE_HPP
#define ENJINCPPSDK_PROJECTRELEASERESERVE_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/AbstractGraphqlRequest.hpp"
#include "enjinsdk/shared/TransactionRequestArguments.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::project {

/// \brief Request for releasing the reserve of an asset.
class ENJINSDK_EXPORT ReleaseReserve : public graphql::AbstractGraphqlRequest,
                                       public shared::TransactionRequestArguments<ReleaseReserve> {
public:
    /// \brief Default constructor.
    ReleaseReserve();

    ~ReleaseReserve() override = default;

    std::string serialize() override;

    /// \brief Sets the asset ID.
    /// \param asset_id The ID.
    /// \return This request for chaining.
    ReleaseReserve& set_asset_id(const std::string& asset_id);

    /// \brief Sets the amount to release.
    /// \param value The amount.
    /// \return This request for chaining.
    ReleaseReserve& set_value(const std::string& value);

    bool operator==(const ReleaseReserve& rhs) const;

    bool operator!=(const ReleaseReserve& rhs) const;

private:
    std::optional<std::string> asset_id;
    std::optional<std::string> value;
};

}

#endif //ENJINCPPSDK_PROJECTRELEASERESERVE_HPP
