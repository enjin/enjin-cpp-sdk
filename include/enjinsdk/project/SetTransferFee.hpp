#ifndef ENJINCPPSDK_PROJECTSETTRANSFERFEE_HPP
#define ENJINCPPSDK_PROJECTSETTRANSFERFEE_HPP

#include "enjinsdk/AbstractGraphqlRequest.hpp"
#include "enjinsdk/shared/TransactionRequestArgumentsTemplate.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::project {

/// \brief Request for setting the transfer fee of a asset.
class SetTransferFee : public graphql::AbstractGraphqlRequest,
                       public shared::TransactionRequestArgumentsTemplate<SetTransferFee> {
public:
    /// \brief Default constructor.
    SetTransferFee();

    ~SetTransferFee() override = default;

    std::string serialize() override;

    /// \brief Sets the asset ID.
    /// \param asset_id The ID.
    /// \return This request for chaining.
    SetTransferFee& set_asset_id(const std::string& asset_id);

    /// \brief Sets the index for non-fungible assets.
    /// \param asset_index The index.
    /// \return This request for chaining.
    SetTransferFee& set_asset_index(const std::string& asset_index);

    /// \brief Sets the new transfer fee value in Wei.
    /// \param transfer_fee The new transfer fee.
    /// \return This request for chaining.
    SetTransferFee& set_transfer_fee(const std::string& transfer_fee);

    bool operator==(const SetTransferFee& rhs) const;

    bool operator!=(const SetTransferFee& rhs) const;

private:
    std::optional<std::string> asset_id;
    std::optional<std::string> asset_index;
    std::optional<std::string> transfer_fee;
};

}

#endif //ENJINCPPSDK_PROJECTSETTRANSFERFEE_HPP
