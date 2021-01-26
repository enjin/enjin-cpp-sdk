#ifndef ENJINCPPSDK_SHAREDGETPROJECT_HPP
#define ENJINCPPSDK_SHAREDGETPROJECT_HPP

#include "enjinsdk/AbstractGraphqlRequest.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::shared {

/// \brief Request for getting a project on the platform.
class GetProject : public graphql::AbstractGraphqlRequest {
public:
    /// \brief Default constructor.
    GetProject();

    ~GetProject() override = default;

    std::string serialize() override;

    /// \brief Sets the project ID.
    /// \param id The ID.
    /// \return This request for chaining.
    GetProject& set_id(int id);

    /// Sets the project name.
    /// \param name The name.
    /// \return This request for chaining.
    GetProject& set_name(const std::string& name);

    bool operator==(const GetProject& rhs) const;

    bool operator!=(const GetProject& rhs) const;

private:
    std::optional<int> id;
    std::optional<std::string> name;
};

}

#endif //ENJINCPPSDK_SHAREDGETPROJECT_HPP
