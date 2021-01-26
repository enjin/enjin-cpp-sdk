#ifndef ENJINCPPSDK_DECREASEMAXMELTFEE_HPP
#define ENJINCPPSDK_DECREASEMAXMELTFEE_HPP

#include "enjinsdk/AbstractGraphqlRequest.hpp"
#include "enjinsdk/shared/TransactionRequestArgumentsTemplate.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::project {

/// \brief Request for setting the max melt fee of an item to a lower value.
class DecreaseMaxMeltFee : public graphql::AbstractGraphqlRequest,
                           public shared::TransactionRequestArgumentsTemplate<DecreaseMaxMeltFee> {
public:
    /// \brief Default constructor.
    DecreaseMaxMeltFee();

    ~DecreaseMaxMeltFee() override = default;

    std::string serialize() override;

    /// \brief Sets the token (item) ID.
    /// \param token_id The ID.
    /// \return This request for chaining.
    DecreaseMaxMeltFee& set_token_id(const std::string& token_id);

    /// \brief Sets the index for non-fungible items.
    /// \param token_index The index.
    /// \return This request for chaining.
    DecreaseMaxMeltFee& set_token_index(const std::string& token_index);

    /// \brief Sets the new max melt fee for the item.
    /// \param max_melt_fee The new ratio.
    /// \return This request for chaining.
    /// \remarks The ratio is in the range 0-5000 to allow fractional ratios, e.g. 1 = 0.01%, 5000 = 50%, ect...
    DecreaseMaxMeltFee& set_max_melt_fee(int max_melt_fee);

    bool operator==(const DecreaseMaxMeltFee& rhs) const;

    bool operator!=(const DecreaseMaxMeltFee& rhs) const;

private:
    std::optional<std::string> token_id;
    std::optional<std::string> token_index;
    std::optional<int> max_melt_fee;
};

}

#endif //ENJINCPPSDK_DECREASEMAXMELTFEE_HPP
