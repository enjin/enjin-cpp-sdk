#ifndef ENJINCPPSDK_PROJECTCREATEASSET_HPP
#define ENJINCPPSDK_PROJECTCREATEASSET_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/internal/AbstractGraphqlRequest.hpp"
#include "enjinsdk/models/AssetSupplyModel.hpp"
#include "enjinsdk/models/AssetTransferFeeSettings.hpp"
#include "enjinsdk/models/AssetTransferable.hpp"
#include "enjinsdk/shared/TransactionRequestArguments.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::project {

/// \brief Request for creating a asset on the platform.
class ENJINSDK_EXPORT CreateAsset : public graphql::AbstractGraphqlRequest,
                                    public shared::TransactionRequestArguments<CreateAsset> {
public:
    /// \brief Default constructor.
    CreateAsset();

    ~CreateAsset() override = default;

    [[nodiscard]] std::string serialize() const override;

    /// \brief Sets the name of the asset.
    /// \param name The name.
    /// \return This request for chaining.
    CreateAsset& set_name(const std::string& name);

    /// \brief Sets the total supply of the asset.
    /// \param total_supply The total supply.
    /// \return This request for chaining.
    CreateAsset& set_total_supply(const std::string& total_supply);

    /// \brief Sets the initial reserve of the asset.
    /// \param initial_reserve The reserve.
    /// \return This request for chaining.
    CreateAsset& set_initial_reserve(const std::string& initial_reserve);

    /// \brief Sets the supply model of the asset.
    /// \param supply_model The supply model.
    /// \return This request for chaining.
    CreateAsset& set_supply_model(models::AssetSupplyModel supply_model);

    /// \brief Sets the melt value of the asset.
    /// \param melt_value The value.
    /// \return This request for chaining.
    /// \remarks Corresponds to the exchange rate.
    CreateAsset& set_melt_value(const std::string& melt_value);

    /// \brief Sets the ratio of the melt value to be returned to the creator.
    /// \param melt_fee_ratio The ratio.
    /// \return This request for chaining.
    /// \remarks The ratio is in the range 0-5000 to allow fractional ratios, e.g. 1 = 0.01%, 5000 = 50%, ect...
    CreateAsset& set_melt_fee_ratio(int melt_fee_ratio);

    /// \brief Sets the transferable type of the asset.
    /// \param transferable The transferable type.
    /// \return This request for chaining.
    CreateAsset& set_transferable(models::AssetTransferable transferable);

    /// \brief Sets the transfer fee settings of the asset.
    /// \param transfer_fee_settings The settings.
    /// \return This request for chaining.
    CreateAsset& set_transfer_fee_settings(const models::AssetTransferFeeSettingsInput& transfer_fee_settings);

    /// \brief Sets the fungible state of the asset.
    /// \param non_fungible The state.
    /// \return This request for chaining.
    CreateAsset& set_non_fungible(bool non_fungible);

    bool operator==(const CreateAsset& rhs) const;

    bool operator!=(const CreateAsset& rhs) const;

private:
    std::optional<std::string> name;
    std::optional<std::string> total_supply;
    std::optional<std::string> initial_reserve;
    std::optional<models::AssetSupplyModel> supply_model;
    std::optional<std::string> melt_value;
    std::optional<int> melt_fee_ratio;
    std::optional<models::AssetTransferable> transferable;
    std::optional<models::AssetTransferFeeSettingsInput> transfer_fee_settings;
    std::optional<bool> non_fungible;
};

}

namespace enjin::sdk::shared {

template ENJINSDK_EXPORT project::CreateAsset&
TransactionFragmentArguments<project::CreateAsset>::set_with_blockchain_data();

template ENJINSDK_EXPORT project::CreateAsset& TransactionFragmentArguments<project::CreateAsset>::set_with_meta();

template ENJINSDK_EXPORT project::CreateAsset&
TransactionFragmentArguments<project::CreateAsset>::set_with_encoded_data();

template ENJINSDK_EXPORT project::CreateAsset&
TransactionFragmentArguments<project::CreateAsset>::set_with_asset_data();

template ENJINSDK_EXPORT project::CreateAsset&
TransactionFragmentArguments<project::CreateAsset>::set_with_signed_txs();

template ENJINSDK_EXPORT project::CreateAsset& TransactionFragmentArguments<project::CreateAsset>::set_with_error();

template ENJINSDK_EXPORT project::CreateAsset& TransactionFragmentArguments<project::CreateAsset>::set_with_nonce();

template ENJINSDK_EXPORT project::CreateAsset& TransactionFragmentArguments<project::CreateAsset>::set_with_state();

template ENJINSDK_EXPORT project::CreateAsset& TransactionFragmentArguments<project::CreateAsset>::set_with_receipt();

template ENJINSDK_EXPORT project::CreateAsset&
TransactionFragmentArguments<project::CreateAsset>::set_with_receipt_logs();

template ENJINSDK_EXPORT project::CreateAsset& TransactionFragmentArguments<project::CreateAsset>::set_with_log_event();

template ENJINSDK_EXPORT project::CreateAsset&
TransactionRequestArguments<project::CreateAsset>::set_eth_address(const std::string& address);

template ENJINSDK_EXPORT project::CreateAsset& TransactionRequestArguments<project::CreateAsset>::set_send(bool send);

}

#endif //ENJINCPPSDK_PROJECTCREATEASSET_HPP
