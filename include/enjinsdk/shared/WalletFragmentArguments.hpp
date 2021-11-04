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

#ifndef ENJINCPPSDK_SHAREDWALLETFRAGMENTARGUMENTS_HPP
#define ENJINCPPSDK_SHAREDWALLETFRAGMENTARGUMENTS_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/internal/WalletFragmentArgumentsImpl.hpp"
#include "enjinsdk/models/BalanceFilter.hpp"
#include "enjinsdk/shared/AssetFragmentArguments.hpp"
#include "enjinsdk/shared/BalanceFragmentArguments.hpp"
#include "enjinsdk/shared/TransactionFragmentArguments.hpp"
#include <string>
#include <type_traits>
#include <utility>

namespace enjin::sdk::shared {

/// \brief Fragment interface used to request certain information from wallets returned by the platform.
/// \tparam T The type of the implementing class.
template<class T>
class ENJINSDK_EXPORT WalletFragmentArguments : public AssetFragmentArguments<T>,
                                                public BalanceFragmentArguments<T>,
                                                public TransactionFragmentArguments<T> {
public:
    ~WalletFragmentArguments() override = default;

    [[nodiscard]] std::string serialize() const override {
        return impl.serialize();
    }

    // WalletFragmentArguments functions

    /// \brief Sets the balance filter when used with with_wallet_balances().
    /// \param filter The filter.
    /// \return This request for chaining.
    virtual T& set_wallet_balance_filter(models::BalanceFilter filter) {
        impl.set_wallet_balance_filter(std::move(filter));
        return static_cast<T&>(*this);
    }

    /// Sets the request to include the assets created by the wallet.
    /// \return This request for chaining.
    virtual T& set_with_assets_created() {
        impl.set_with_assets_created();
        return static_cast<T&>(*this);
    }

    /// \brief Sets the request to include the asset balances of the wallet.
    /// \return This request for chaining.
    virtual T& set_with_wallet_balances() {
        impl.set_with_wallet_balances();
        return static_cast<T&>(*this);
    }

    /// \brief Sets the request to include the transactions the wallet has signed.
    /// \return This request for chaining.
    virtual T& set_with_wallet_transactions() {
        impl.set_with_wallet_transactions();
        return static_cast<T&>(*this);
    }

    // AssetFragmentArguments functions

    virtual T& set_asset_id_format(models::AssetIdFormat asset_id_format) override {
        impl.set_asset_id_format(asset_id_format);
        return static_cast<T&>(*this);
    }

    virtual T& set_with_state_data() override {
        impl.set_with_state_data();
        return static_cast<T&>(*this);
    }

    virtual T& set_with_config_data() override {
        impl.set_with_config_data();
        return static_cast<T&>(*this);
    }

    virtual T& set_with_asset_blocks() override {
        impl.set_with_asset_blocks();
        return static_cast<T&>(*this);
    }

    virtual T& set_with_creator() override {
        impl.set_with_creator();
        return static_cast<T&>(*this);
    }

    virtual T& set_with_melt_details() override {
        impl.set_with_melt_details();
        return static_cast<T&>(*this);
    }

    virtual T& set_with_metadata_uri() override {
        impl.set_with_metadata_uri();
        return static_cast<T&>(*this);
    }

    virtual T& set_with_supply_details() override {
        impl.set_with_supply_details();
        return static_cast<T&>(*this);
    }

    virtual T& set_with_transfer_settings() override {
        impl.set_with_transfer_settings();
        return static_cast<T&>(*this);
    }

    virtual T& set_with_asset_variant_mode() override {
        impl.set_with_asset_variant_mode();
        return static_cast<T&>(*this);
    }

    virtual T& set_with_asset_variants() override {
        impl.set_with_asset_variants();
        return static_cast<T&>(*this);
    }

    virtual T& set_with_variant_metadata() override {
        impl.set_with_variant_metadata();
        return static_cast<T&>(*this);
    }

    // BalanceFragmentArguments functions

    virtual T& set_bal_id_format(models::AssetIdFormat bal_id_format) override {
        impl.set_bal_id_format(bal_id_format);
        return static_cast<T&>(*this);
    }

    virtual T& set_bal_index_format(models::AssetIndexFormat bal_index_format) override {
        impl.set_bal_index_format(bal_index_format);
        return static_cast<T&>(*this);
    }

    virtual T& set_with_bal_project_uuid() override {
        impl.set_with_bal_project_uuid();
        return static_cast<T&>(*this);
    }

    virtual T& set_with_bal_wallet_address() override {
        impl.set_with_bal_wallet_address();
        return static_cast<T&>(*this);
    }

    // TransactionFragmentArguments functions

    virtual T& set_transaction_asset_id_format(models::AssetIdFormat asset_id_format) override {
        impl.set_transaction_asset_id_format(asset_id_format);
        return static_cast<T&>(*this);
    }

    virtual T& set_with_blockchain_data() override {
        impl.set_with_blockchain_data();
        return static_cast<T&>(*this);
    }

    virtual T& set_with_meta() override {
        impl.set_with_meta();
        return static_cast<T&>(*this);
    }

    virtual T& set_with_encoded_data() override {
        impl.set_with_encoded_data();
        return static_cast<T&>(*this);
    }

    virtual T& set_with_asset_data() override {
        impl.set_with_asset_data();
        return static_cast<T&>(*this);
    }

    virtual T& set_with_signed_txs() override {
        impl.set_with_signed_txs();
        return static_cast<T&>(*this);
    }

    virtual T& set_with_error() override {
        impl.set_with_error();
        return static_cast<T&>(*this);
    }

    virtual T& set_with_nonce() override {
        impl.set_with_nonce();
        return static_cast<T&>(*this);
    }

    virtual T& set_with_state() override {
        impl.set_with_state();
        return static_cast<T&>(*this);
    }

    virtual T& set_with_receipt() override {
        impl.set_with_receipt();
        return static_cast<T&>(*this);
    }

    virtual T& set_with_receipt_logs() override {
        impl.set_with_receipt_logs();
        return static_cast<T&>(*this);
    }

    virtual T& set_with_log_event() override {
        impl.set_with_log_event();
        return static_cast<T&>(*this);
    }

    virtual T& set_with_transaction_project_uuid() override {
        impl.set_with_transaction_project_uuid();
        return static_cast<T&>(*this);
    }

    virtual T& set_with_transaction_wallet_address() override {
        impl.set_with_transaction_wallet_address();
        return static_cast<T&>(*this);
    }

    bool operator==(const WalletFragmentArguments& rhs) const {
        return impl == rhs.impl;
    }

    bool operator!=(const WalletFragmentArguments& rhs) const {
        return impl != rhs.impl;
    }

protected:
    /// \brief Sole constructor.
    WalletFragmentArguments() {
        static_assert(std::is_base_of<WalletFragmentArguments, T>::value,
                      "Class T does not inherit from WalletFragmentArguments.");
    }

private:
    WalletFragmentArgumentsImpl impl;
};

}

#endif //ENJINCPPSDK_SHAREDWALLETFRAGMENTARGUMENTS_HPP
