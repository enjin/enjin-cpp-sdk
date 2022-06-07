/* Copyright 2021 Enjin Pte. Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ENJINCPPSDK_PROJECTCREATEASSET_HPP
#define ENJINCPPSDK_PROJECTCREATEASSET_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/internal/AbstractGraphqlRequest.hpp"
#include "enjinsdk/models/AssetSupplyModel.hpp"
#include "enjinsdk/models/AssetTransferFeeSettingsInput.hpp"
#include "enjinsdk/models/AssetTransferable.hpp"
#include "enjinsdk/project/ProjectTransactionRequestArguments.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::project {

/// \brief Request for creating a asset on the platform.
class ENJINSDK_EXPORT CreateAsset : public graphql::AbstractGraphqlRequest,
                                    public ProjectTransactionRequestArguments<CreateAsset> {
public:
    /// \brief Default constructor.
    CreateAsset();

    ~CreateAsset() override = default;

    [[nodiscard]] std::string serialize() const override;

    /// \brief Sets the name of the asset.
    /// \param name The name.
    /// \return This request for chaining.
    CreateAsset& set_name(std::string name);

    /// \brief Sets the total supply of the asset.
    /// \param total_supply The total supply.
    /// \return This request for chaining.
    CreateAsset& set_total_supply(std::string total_supply);

    /// \brief Sets the initial reserve of the asset.
    /// \param initial_reserve The reserve.
    /// \return This request for chaining.
    CreateAsset& set_initial_reserve(std::string initial_reserve);

    /// \brief Sets the supply model of the asset.
    /// \param supply_model The supply model.
    /// \return This request for chaining.
    CreateAsset& set_supply_model(models::AssetSupplyModel supply_model);

    /// \brief Sets the melt value of the asset.
    /// \param melt_value The value.
    /// \return This request for chaining.
    /// \remarks Corresponds to the exchange rate.
    CreateAsset& set_melt_value(std::string melt_value);

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
    CreateAsset& set_transfer_fee_settings(models::AssetTransferFeeSettingsInput transfer_fee_settings);

    /// \brief Sets the fungible state of the asset.
    /// \param non_fungible The state.
    /// \return This request for chaining.
    CreateAsset& set_non_fungible(bool non_fungible);

    [[nodiscard]] json::JsonValue to_json() const override;

    bool operator==(const CreateAsset& rhs) const;

    bool operator!=(const CreateAsset& rhs) const;

private:
    std::optional<std::string> name_opt;
    std::optional<std::string> total_supply_opt;
    std::optional<std::string> initial_reserve_opt;
    std::optional<models::AssetSupplyModel> supply_model_opt;
    std::optional<std::string> melt_value_opt;
    std::optional<int> melt_fee_ratio_opt;
    std::optional<models::AssetTransferable> transferable_opt;
    std::optional<models::AssetTransferFeeSettingsInput> transfer_fee_settings_opt;
    std::optional<bool> non_fungible_opt;
};

template ENJINSDK_EXPORT CreateAsset&
ProjectTransactionRequestArguments<CreateAsset>::set_eth_address(std::string address);

}

namespace enjin::sdk::shared {

template ENJINSDK_EXPORT project::CreateAsset&
TransactionFragmentArguments<project::CreateAsset>::set_transaction_asset_id_format(
        models::AssetIdFormat asset_id_format);

template ENJINSDK_EXPORT project::CreateAsset&
TransactionFragmentArguments<project::CreateAsset>::set_with_blockchain_data();

template ENJINSDK_EXPORT project::CreateAsset&
TransactionFragmentArguments<project::CreateAsset>::set_with_meta();

template ENJINSDK_EXPORT project::CreateAsset&
TransactionFragmentArguments<project::CreateAsset>::set_with_encoded_data();

template ENJINSDK_EXPORT project::CreateAsset&
TransactionFragmentArguments<project::CreateAsset>::set_with_asset_data();

template ENJINSDK_EXPORT project::CreateAsset&
TransactionFragmentArguments<project::CreateAsset>::set_with_signed_txs();

template ENJINSDK_EXPORT project::CreateAsset&
TransactionFragmentArguments<project::CreateAsset>::set_with_error();

template ENJINSDK_EXPORT project::CreateAsset&
TransactionFragmentArguments<project::CreateAsset>::set_with_nonce();

template ENJINSDK_EXPORT project::CreateAsset&
TransactionFragmentArguments<project::CreateAsset>::set_with_state();

template ENJINSDK_EXPORT project::CreateAsset&
TransactionFragmentArguments<project::CreateAsset>::set_with_receipt();

template ENJINSDK_EXPORT project::CreateAsset&
TransactionFragmentArguments<project::CreateAsset>::set_with_receipt_logs();

template ENJINSDK_EXPORT project::CreateAsset&
TransactionFragmentArguments<project::CreateAsset>::set_with_log_event();

template ENJINSDK_EXPORT project::CreateAsset&
TransactionFragmentArguments<project::CreateAsset>::set_with_transaction_project_uuid();

template ENJINSDK_EXPORT project::CreateAsset&
TransactionFragmentArguments<project::CreateAsset>::set_with_transaction_wallet_address();

}

#endif //ENJINCPPSDK_PROJECTCREATEASSET_HPP
