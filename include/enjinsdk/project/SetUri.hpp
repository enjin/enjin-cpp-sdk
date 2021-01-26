#ifndef ENJINCPPSDK_PROJECTSETURI_HPP
#define ENJINCPPSDK_PROJECTSETURI_HPP

#include "enjinsdk/AbstractGraphqlRequest.hpp"
#include "enjinsdk/shared/TransactionRequestArgumentsTemplate.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::project {

/// \brief Request to set the metadata URI of an item.
class SetUri : public graphql::AbstractGraphqlRequest,
               public shared::TransactionRequestArgumentsTemplate<SetUri> {
public:
    /// \brief Default constructor.
    SetUri();

    ~SetUri() override = default;

    std::string serialize() override;

    /// \brief Sets the token (item) ID.
    /// \param token_id The ID.
    /// \return This request for chaining.
    SetUri& set_token_id(const std::string& token_id);

    /// \brief Sets the index for non-fungible items.
    /// \param token_index The index.
    /// \return This request for chaining.
    SetUri& set_token_index(const std::string& token_index);

    /// \brief Sets the new URI for the item's metadata.
    /// \param uri The URI.
    /// \return This request for chaining.
    SetUri& set_uri(const std::string& uri);

    bool operator==(const SetUri& rhs) const;

    bool operator!=(const SetUri& rhs) const;

private:
    std::optional<std::string> token_id;
    std::optional<std::string> token_index;
    std::optional<std::string> uri;
};

}

#endif //ENJINCPPSDK_PROJECTSETURI_HPP
