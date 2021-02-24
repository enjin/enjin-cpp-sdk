#ifndef ENJINCPPSDK_SHAREDGETASSET_HPP
#define ENJINCPPSDK_SHAREDGETASSET_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/AbstractGraphqlRequest.hpp"
#include "enjinsdk/models/Asset.hpp"
#include "enjinsdk/shared/AssetFragmentArgumentsTemplate.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::shared {

/// \brief Request for getting a asset on the platform.
class ENJINSDK_EXPORT GetAsset : public graphql::AbstractGraphqlRequest,
                                 public AssetFragmentArgumentsTemplate<GetAsset> {
public:
    /// \brief Default constructor.
    GetAsset();

    ~GetAsset() override = default;

    std::string serialize() override;

    /// \brief Sets the asset ID.
    /// \param id The ID.
    /// \return This request for chaining.
    GetAsset& set_id(const std::string& id);

    bool operator==(const GetAsset& rhs) const;

    bool operator!=(const GetAsset& rhs) const;

private:
    std::optional<std::string> id;
};

}

#endif //ENJINCPPSDK_SHAREDGETASSET_HPP
