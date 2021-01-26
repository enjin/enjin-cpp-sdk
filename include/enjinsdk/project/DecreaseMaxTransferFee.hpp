#ifndef ENJINCPPSDK_PROJECTDECREASEMAXTRANSFERFEE_HPP
#define ENJINCPPSDK_PROJECTDECREASEMAXTRANSFERFEE_HPP

#include "enjinsdk/AbstractGraphqlRequest.hpp"
#include "enjinsdk/shared/TransactionRequestArgumentsTemplate.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::project {

/// \brief Request for setting an item's max transfer fee to a lower value.
class DecreaseMaxTransferFee : public graphql::AbstractGraphqlRequest,
                               public shared::TransactionRequestArgumentsTemplate<DecreaseMaxTransferFee> {
public:
    /// \brief Default constructor.
    DecreaseMaxTransferFee();

    ~DecreaseMaxTransferFee() override = default;

    std::string serialize() override;

    /// \brief Sets the token ID.
    /// \param token_id The ID.
    /// \return This request for chaining.
    DecreaseMaxTransferFee& set_token_id(const std::string& token_id);

    /// \brief Sets the index for non-fungible items.
    /// \param token_index The index.
    /// \return This request for chaining.
    DecreaseMaxTransferFee& set_token_index(const std::string& token_index);

    /// \brief Sets the new max transfer fee in Wei.
    /// \param max_transfer_fee The new fee.
    /// \return This request for chaining.
    DecreaseMaxTransferFee& set_max_transfer_fee(int max_transfer_fee);

    bool operator==(const DecreaseMaxTransferFee& rhs) const;

    bool operator!=(const DecreaseMaxTransferFee& rhs) const;

private:
    std::optional<std::string> token_id;
    std::optional<std::string> token_index;
    std::optional<int> max_transfer_fee;
};

}

#endif //ENJINCPPSDK_PROJECTDECREASEMAXTRANSFERFEE_HPP
