#ifndef ENJINCPPSDK_SETTRANSFERABLE_HPP
#define ENJINCPPSDK_SETTRANSFERABLE_HPP

#include "enjinsdk/AbstractGraphqlRequest.hpp"
#include "enjinsdk/models/TokenTransferable.hpp"
#include "enjinsdk/shared/TransactionRequestArgumentsTemplate.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::project {

/// \brief Request for setting if a item may be transferred.
class SetTransferable : public graphql::AbstractGraphqlRequest,
                        public shared::TransactionRequestArgumentsTemplate<SetTransferable> {
public:
    /// \brief Default constructor.
    SetTransferable();

    ~SetTransferable() override = default;

    std::string serialize() override;

    /// \brief Sets the token ID.
    /// \param token_id The ID.
    /// \return This request for chaining.
    SetTransferable& set_token_id(const std::string& token_id);

    /// \brief Sets the index for non-fungible items.
    /// \param token_index The index.
    /// \return This request for chaining.
    SetTransferable& set_token_index(const std::string& token_index);

    /// \brief Sets the new transfer mode.
    /// \param transferable The new mode.
    /// \return This request for chaining.
    SetTransferable& set_transferable(models::TokenTransferable transferable);

    bool operator==(const SetTransferable& rhs) const;

    bool operator!=(const SetTransferable& rhs) const;

private:
    std::optional<std::string> token_id;
    std::optional<std::string> token_index;
    std::optional<models::TokenTransferable> transferable;
};

}

#endif //ENJINCPPSDK_SETTRANSFERABLE_HPP
