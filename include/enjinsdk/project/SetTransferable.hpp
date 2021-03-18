#ifndef ENJINCPPSDK_PROJECTSETTRANSFERABLE_HPP
#define ENJINCPPSDK_PROJECTSETTRANSFERABLE_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/AbstractGraphqlRequest.hpp"
#include "enjinsdk/models/AssetTransferable.hpp"
#include "enjinsdk/shared/TransactionRequestArguments.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::project {

/// \brief Request for setting if a asset may be transferred.
class ENJINSDK_EXPORT SetTransferable : public graphql::AbstractGraphqlRequest,
                                        public shared::TransactionRequestArguments<SetTransferable> {
public:
    /// \brief Default constructor.
    SetTransferable();

    ~SetTransferable() override = default;

    std::string serialize() override;

    /// \brief Sets the asset ID.
    /// \param asset_id The ID.
    /// \return This request for chaining.
    SetTransferable& set_asset_id(const std::string& asset_id);

    /// \brief Sets the index for non-fungible assets.
    /// \param asset_index The index.
    /// \return This request for chaining.
    SetTransferable& set_asset_index(const std::string& asset_index);

    /// \brief Sets the new transfer mode.
    /// \param transferable The new mode.
    /// \return This request for chaining.
    SetTransferable& set_transferable(models::AssetTransferable transferable);

    bool operator==(const SetTransferable& rhs) const;

    bool operator!=(const SetTransferable& rhs) const;

private:
    std::optional<std::string> asset_id;
    std::optional<std::string> asset_index;
    std::optional<models::AssetTransferable> transferable;
};

}

#endif //ENJINCPPSDK_PROJECTSETTRANSFERABLE_HPP
