#ifndef ENJINCPPSDK_MINTTOKEN_HPP
#define ENJINCPPSDK_MINTTOKEN_HPP

#include "enjinsdk/AbstractGraphqlRequest.hpp"
#include "enjinsdk/models/MintInput.hpp"
#include "enjinsdk/shared/TransactionRequestArgumentsTemplate.hpp"
#include <optional>
#include <string>
#include <vector>

namespace enjin::sdk::project {

/// \brief Request for minting a token (item).
class MintToken : public graphql::AbstractGraphqlRequest,
                  public shared::TransactionRequestArgumentsTemplate<MintToken> {
public:
    /// \brief Default constructor.
    MintToken();

    ~MintToken() override = default;

    std::string serialize() override;

    /// \brief Sets the token ID.
    /// \param token_id The ID.
    /// \return This request for chaining.
    MintToken& set_token_id(const std::string& token_id);

    /// \brief Sets the mints to be performed.
    /// \param mints The mints.
    /// \return This request for chaining.
    MintToken& set_mints(const std::vector<models::MintInput>& mints);

    bool operator==(const MintToken& rhs) const;

    bool operator!=(const MintToken& rhs) const;

private:
    std::optional<std::string> token_id;
    std::optional<std::vector<models::MintInput>> mints;
};

}

#endif //ENJINCPPSDK_MINTTOKEN_HPP
