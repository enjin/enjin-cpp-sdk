#ifndef ENJINCPPSDK_PROJECTDECREASEMAXTRANSFERFEE_HPP
#define ENJINCPPSDK_PROJECTDECREASEMAXTRANSFERFEE_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/AbstractGraphqlRequest.hpp"
#include "enjinsdk/shared/TransactionRequestArgumentsTemplate.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::project {

/// \brief Request for setting an asset's max transfer fee to a lower value.
class ENJINSDK_EXPORT DecreaseMaxTransferFee : public graphql::AbstractGraphqlRequest,
                                               public shared::TransactionRequestArgumentsTemplate<DecreaseMaxTransferFee> {
public:
    /// \brief Default constructor.
    DecreaseMaxTransferFee();

    ~DecreaseMaxTransferFee() override = default;

    std::string serialize() override;

    /// \brief Sets the asset ID.
    /// \param asset_id The ID.
    /// \return This request for chaining.
    DecreaseMaxTransferFee& set_asset_id(const std::string& asset_id);

    /// \brief Sets the index for non-fungible assets.
    /// \param asset_index The index.
    /// \return This request for chaining.
    DecreaseMaxTransferFee& set_asset_index(const std::string& asset_index);

    /// \brief Sets the new max transfer fee in Wei.
    /// \param max_transfer_fee The new fee.
    /// \return This request for chaining.
    DecreaseMaxTransferFee& set_max_transfer_fee(int max_transfer_fee);

    bool operator==(const DecreaseMaxTransferFee& rhs) const;

    bool operator!=(const DecreaseMaxTransferFee& rhs) const;

private:
    std::optional<std::string> asset_id;
    std::optional<std::string> asset_index;
    std::optional<int> max_transfer_fee;
};

}

#endif //ENJINCPPSDK_PROJECTDECREASEMAXTRANSFERFEE_HPP
