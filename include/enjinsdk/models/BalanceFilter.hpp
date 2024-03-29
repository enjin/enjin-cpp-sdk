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

#ifndef ENJINCPPSDK_BALANCEFILTER_HPP
#define ENJINCPPSDK_BALANCEFILTER_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/ISerializable.hpp"
#include "enjinsdk/models/Operator.hpp"
#include <memory>
#include <optional>
#include <string>
#include <vector>

namespace enjin::sdk::models {

/// \brief Models a filter input for balance queries.
class ENJINSDK_EXPORT BalanceFilter : public serialization::ISerializable {
public:
    /// \brief Constructs an instance of this class.
    BalanceFilter();

    /// \brief Constructs an instance as a copy of another.
    /// \param other The other instance.
    BalanceFilter(const BalanceFilter& other);

    /// \brief Constructs an instance via move.
    /// \param other The other instance being moved.
    BalanceFilter(BalanceFilter&& other) noexcept;

    /// \brief Deconstructs this instance.
    ~BalanceFilter() override;

    [[nodiscard]] std::string serialize() const override;

    /// \brief Sets the filter to include other filters to intersect with.
    /// \param others The other filters.
    /// \return This filter for chaining.
    BalanceFilter& set_and(std::vector<BalanceFilter> others);

    /// \brief Sets the filter to include other filters to union with.
    /// \param others The other filters.
    /// \return This filter for chaining.
    BalanceFilter& set_or(std::vector<BalanceFilter> others);

    /// \brief Sets the asset ID to filter for.
    /// \param asset_id The asset ID.
    /// \return This filter for chaining.
    BalanceFilter& set_asset_id(std::string asset_id);

    /// \brief Sets the asset IDs to filter for.
    /// \param asset_ids The asset IDs.
    /// \return This filter for chaining.
    BalanceFilter& set_asset_id_in(std::vector<std::string> asset_ids);

    /// \brief Sets the wallet to filter by.
    /// \param wallet The wallet address.
    /// \return This filter for chaining.
    BalanceFilter& set_wallet(std::string wallet);

    /// \brief Sets the wallets to filter by.
    /// \param wallets The wallet addresses.
    /// \return This filter for chaining.
    BalanceFilter& set_wallet_in(std::vector<std::string> wallets);

    /// \brief Sets the filter to include balances equal to the passed value.
    /// \param value The value to compare by.
    /// \return This filter for chaining.
    BalanceFilter& set_value(int value);

    /// \brief Sets the filter operator type for values.
    /// \param value_is The operator for comparison.
    /// \return This filter for chaining.
    BalanceFilter& set_value_is(Operator value_is);

    [[nodiscard]] json::JsonValue to_json() const override;

    bool operator==(const BalanceFilter& rhs) const;

    bool operator!=(const BalanceFilter& rhs) const;

    BalanceFilter& operator=(const BalanceFilter& rhs);

private:
    class Impl;

    std::unique_ptr<Impl> pimpl;
};

}

#endif //ENJINCPPSDK_BALANCEFILTER_HPP
