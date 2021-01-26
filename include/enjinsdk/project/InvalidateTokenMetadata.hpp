#ifndef ENJINCPPSDK_INVALIDATETOKENMETADATA_HPP
#define ENJINCPPSDK_INVALIDATETOKENMETADATA_HPP

#include "enjinsdk/AbstractGraphqlRequest.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::project {

/// \brief Request for invalidating the cached metadata of a token (item) on the platform.
class InvalidateTokenMetadata : public graphql::AbstractGraphqlRequest {
public:
    /// \brief Default constructor.
    InvalidateTokenMetadata();

    ~InvalidateTokenMetadata() override = default;

    std::string serialize() override;

    /// \brief Sets the token ID.
    /// \param id The ID.
    /// \return This request for chaining.
    InvalidateTokenMetadata& set_id(const std::string& id);

    bool operator==(const InvalidateTokenMetadata& rhs) const;

    bool operator!=(const InvalidateTokenMetadata& rhs) const;

private:
    std::optional<std::string> id;
};

}

#endif //ENJINCPPSDK_INVALIDATETOKENMETADATA_HPP
