#ifndef ENJINCPPSDK_PROJECTINVALIDATEASSETMETADATA_HPP
#define ENJINCPPSDK_PROJECTINVALIDATEASSETMETADATA_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/AbstractGraphqlRequest.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::project {

/// \brief Request for invalidating the cached metadata of a asset on the platform.
class ENJINSDK_EXPORT InvalidateAssetMetadata : public graphql::AbstractGraphqlRequest {
public:
    /// \brief Default constructor.
    InvalidateAssetMetadata();

    ~InvalidateAssetMetadata() override = default;

    std::string serialize() override;

    /// \brief Sets the asset ID.
    /// \param id The ID.
    /// \return This request for chaining.
    InvalidateAssetMetadata& set_id(const std::string& id);

    bool operator==(const InvalidateAssetMetadata& rhs) const;

    bool operator!=(const InvalidateAssetMetadata& rhs) const;

private:
    std::optional<std::string> id;
};

}

#endif //ENJINCPPSDK_PROJECTINVALIDATEASSETMETADATA_HPP
