#ifndef ENJINCPPSDK_SHAREDGETPLATFORM_HPP
#define ENJINCPPSDK_SHAREDGETPLATFORM_HPP

#include "enjinsdk/AbstractGraphqlRequest.hpp"
#include <optional>

namespace enjin::sdk::shared {

/// \brief Request for getting the platform details.
class GetPlatform : public graphql::AbstractGraphqlRequest {
public:
    /// \brief Default constructor.
    GetPlatform();

    ~GetPlatform() override = default;

    std::string serialize() override;

    /// \brief Sets the request to include the contracts with the platform.
    /// \return This request for chaining.
    GetPlatform& set_with_contracts();

    /// Sets the request to include the notification drivers with the platform.
    /// \return This request for chaining.
    GetPlatform& set_with_notifications();

    bool operator==(const GetPlatform& rhs) const;

    bool operator!=(const GetPlatform& rhs) const;

private:
    std::optional<bool> with_contracts;
    std::optional<bool> with_notifications;
};

}

#endif //ENJINCPPSDK_SHAREDGETPLATFORM_HPP
