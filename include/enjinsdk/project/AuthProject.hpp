#ifndef ENJINCPPSDK_PROJECTAUTHPROJECT_HPP
#define ENJINCPPSDK_PROJECTAUTHPROJECT_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/internal/AbstractGraphqlRequest.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::project {

/// \brief Request to obtain the access token for a project.
class ENJINSDK_EXPORT AuthProject : public graphql::AbstractGraphqlRequest {
public:
    /// \brief Default constructor.
    AuthProject();

    ~AuthProject() override = default;

    [[nodiscard]] std::string serialize() const override;

    /// \brief Sets the project ID.
    /// \param id The ID.
    /// \return This request for chaining.
    AuthProject& set_id(int id);

    /// \brief Sets the secret.
    /// \param secret The secret.
    /// \return This request for chaining.
    AuthProject& set_secret(const std::string& secret);

    bool operator==(const AuthProject& rhs) const;

    bool operator!=(const AuthProject& rhs) const;

private:
    std::optional<int> id;
    std::optional<std::string> secret;
};

}

#endif //ENJINCPPSDK_PROJECTAUTHPROJECT_HPP
