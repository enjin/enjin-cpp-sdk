#ifndef ENJINCPPSDK_PROJECTMINTASSET_HPP
#define ENJINCPPSDK_PROJECTMINTASSET_HPP

#include "enjinsdk/AbstractGraphqlRequest.hpp"
#include "enjinsdk/models/MintInput.hpp"
#include "enjinsdk/shared/TransactionRequestArgumentsTemplate.hpp"
#include <optional>
#include <string>
#include <vector>

namespace enjin::sdk::project {

/// \brief Request for minting a asset.
class MintAsset : public graphql::AbstractGraphqlRequest,
                  public shared::TransactionRequestArgumentsTemplate<MintAsset> {
public:
    /// \brief Default constructor.
    MintAsset();

    ~MintAsset() override = default;

    std::string serialize() override;

    /// \brief Sets the asset ID.
    /// \param asset_id The ID.
    /// \return This request for chaining.
    MintAsset& set_asset_id(const std::string& asset_id);

    /// \brief Sets the mints to be performed.
    /// \param mints The mints.
    /// \return This request for chaining.
    MintAsset& set_mints(const std::vector<models::MintInput>& mints);

    bool operator==(const MintAsset& rhs) const;

    bool operator!=(const MintAsset& rhs) const;

private:
    std::optional<std::string> asset_id;
    std::optional<std::vector<models::MintInput>> mints;
};

}

#endif //ENJINCPPSDK_PROJECTMINTASSET_HPP
