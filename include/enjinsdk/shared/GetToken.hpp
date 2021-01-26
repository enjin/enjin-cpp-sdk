#ifndef ENJINCPPSDK_SHAREDGETTOKEN_HPP
#define ENJINCPPSDK_SHAREDGETTOKEN_HPP

#include "enjinsdk/AbstractGraphqlRequest.hpp"
#include "enjinsdk/models/Token.hpp"
#include "enjinsdk/shared/TokenFragmentArgumentsTemplate.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::shared {

/// \brief Request for getting a token (item) on the platform.
class GetToken : public graphql::AbstractGraphqlRequest,
                 public TokenFragmentArgumentsTemplate<GetToken> {
public:
    /// \brief Default constructor.
    GetToken();

    ~GetToken() override = default;

    std::string serialize() override;

    /// \brief Sets the token (item) ID.
    /// \param id The ID.
    /// \return This request for chaining.
    GetToken& set_id(const std::string& id);

    bool operator==(const GetToken& rhs) const;

    bool operator!=(const GetToken& rhs) const;

private:
    std::optional<std::string> id;
};

}

#endif //ENJINCPPSDK_SHAREDGETTOKEN_HPP
