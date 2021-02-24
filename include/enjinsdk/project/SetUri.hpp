#ifndef ENJINCPPSDK_PROJECTSETURI_HPP
#define ENJINCPPSDK_PROJECTSETURI_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/AbstractGraphqlRequest.hpp"
#include "enjinsdk/shared/TransactionRequestArgumentsTemplate.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::project {

/// \brief Request to set the metadata URI of an asset.
class ENJINSDK_EXPORT SetUri : public graphql::AbstractGraphqlRequest,
                               public shared::TransactionRequestArgumentsTemplate<SetUri> {
public:
    /// \brief Default constructor.
    SetUri();

    ~SetUri() override = default;

    std::string serialize() override;

    /// \brief Sets the asset ID.
    /// \param asset_id The ID.
    /// \return This request for chaining.
    SetUri& set_asset_id(const std::string& asset_id);

    /// \brief Sets the index for non-fungible assets.
    /// \param asset_index The index.
    /// \return This request for chaining.
    SetUri& set_asset_index(const std::string& asset_index);

    /// \brief Sets the new URI for the asset's metadata.
    /// \param uri The URI.
    /// \return This request for chaining.
    SetUri& set_uri(const std::string& uri);

    bool operator==(const SetUri& rhs) const;

    bool operator!=(const SetUri& rhs) const;

private:
    std::optional<std::string> asset_id;
    std::optional<std::string> asset_index;
    std::optional<std::string> uri;
};

}

#endif //ENJINCPPSDK_PROJECTSETURI_HPP
