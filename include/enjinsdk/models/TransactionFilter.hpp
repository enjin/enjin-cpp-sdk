/* Copyright 2021 Enjin Pte Ltd.
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

#ifndef ENJINCPPSDK_TRANSACTIONFILTER_HPP
#define ENJINCPPSDK_TRANSACTIONFILTER_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/ISerializable.hpp"
#include "enjinsdk/models/RequestState.hpp"
#include "enjinsdk/models/RequestType.hpp"
#include <optional>
#include <string>
#include <vector>

namespace enjin::sdk::models {

/// \brief Models a filter input for transaction queries.
class ENJINSDK_EXPORT TransactionFilter : public serialization::ISerializable {
public:
    /// \brief Default constructor.
    TransactionFilter() = default;

    ~TransactionFilter() override = default;

    [[nodiscard]] std::string serialize() const override;

    /// \brief Sets the filter to include other filters to intersect with.
    /// \param others The other filters.
    /// \return This filter for chaining.
    TransactionFilter& set_and(const std::vector<TransactionFilter>& others);

    /// \brief Sets the filter to include other filters to union with.
    /// \param others The other filters.
    /// \return This filter for chaining.
    TransactionFilter& set_or(const std::vector<TransactionFilter>& others);

    /// \brief Sets the ID to filter for.
    /// \param id The ID.
    /// \return This filter for chaining.
    TransactionFilter& set_id(const std::string& id);

    /// \brief Sets the IDs to filter for.
    /// \param ids The IDs.
    /// \return This filter for chaining.
    TransactionFilter& set_id_in(const std::vector<std::string>& ids);

    /// \brief Sets the hash ID to filter for.
    /// \param transaction_id The hash ID.
    /// \return This filter for chaining.
    TransactionFilter& set_transaction_id(const std::string& transaction_id);

    /// \brief Sets the hash IDs to filter for.
    /// \param transaction_ids The hash IDs.
    /// \return This filter for chaining.
    TransactionFilter& set_transaction_id_in(const std::vector<std::string>& transaction_ids);

    /// \brief Sets the asset ID to filter for.
    /// \param asset_id The ID.
    /// \return This filter for chaining.
    TransactionFilter& set_asset_id(const std::string& asset_id);

    /// \brief Sets the asset IDs to filter for.
    /// \param asset_ids The IDs.
    /// \return This filter for chaining.
    TransactionFilter& set_asset_id_in(const std::vector<std::string>& asset_ids);

    /// \brief Sets the transaction type to filter for.
    /// \param type The type.
    /// \return This filter for chaining.
    TransactionFilter& set_type(const RequestType& type);

    /// \brief Sets the transaction types to filter for.
    /// \param types The types.
    /// \return This filter for chaining.
    TransactionFilter& set_type_in(const std::vector<RequestType>& types);

    /// \brief Sets the filter to include transactions equal to the passed value.
    /// \param value The value to compare by.
    /// \return This filter for chaining.
    TransactionFilter& set_value(int value);

    /// \brief Sets the filter to include transactions greater than the passed value.
    /// \param value The value to compare by.
    /// \return This filter for chaining.
    TransactionFilter& set_value_gt(int value);

    /// \brief Sets the filter to include transactions greater than or equal the passed value.
    /// \param value The value to compare by.
    /// \return This filter for chaining.
    TransactionFilter& set_value_gte(int value);

    /// \brief Sets the filter to include transactions less than the passed value.
    /// \param value The value to compare by.
    /// \return This filter for chaining.
    TransactionFilter& set_value_lt(int value);

    /// \brief Sets the filter to include transactions less than or equal the passed value.
    /// \param value The value to compare by.
    /// \return This filter for chaining.
    TransactionFilter& set_value_lte(int value);

    /// \brief Sets the request state to filter for.
    /// \param state The state.
    /// \return This filter for chaining.
    TransactionFilter& set_state(const RequestState& state);

    /// \brief Sets the request states to filter for.
    /// \param states The states.
    /// \return This filter for chaining.
    TransactionFilter& set_state_in(const std::vector<RequestState>& states);

    /// \brief Sets the wallet to filter for.
    /// \param wallet The wallet address.
    /// \return This filter for chaining.
    TransactionFilter& set_wallet(const std::string& wallet);

    /// \brief Sets the wallets to filter for.
    /// \param wallets The wallet addresses.
    /// \return This filter for chaining.
    TransactionFilter& set_wallet_in(const std::vector<std::string>& wallets);

    bool operator==(const TransactionFilter& rhs) const;

    bool operator!=(const TransactionFilter& rhs) const;


private:
    std::optional<std::vector<TransactionFilter>> and_filters;
    std::optional<std::vector<TransactionFilter>> or_filters;
    std::optional<std::string> id;
    std::optional<std::vector<std::string>> id_in;
    std::optional<std::string> transaction_id;
    std::optional<std::vector<std::string>> transaction_id_in;
    std::optional<std::string> asset_id;
    std::optional<std::vector<std::string>> asset_id_in;
    std::optional<RequestType> type;
    std::optional<std::vector<RequestType>> type_in;
    std::optional<int> value;
    std::optional<int> value_gt;
    std::optional<int> value_gte;
    std::optional<int> value_lt;
    std::optional<int> value_lte;
    std::optional<RequestState> state;
    std::optional<std::vector<RequestState>> state_in;
    std::optional<std::string> wallet;
    std::optional<std::vector<std::string>> wallet_in;

    constexpr static char AND_KEY[] = "and";
    constexpr static char OR_KEY[] = "or";
    constexpr static char ID_KEY[] = "id";
    constexpr static char ID_IN_KEY[] = "id_in";
    constexpr static char TRANSACTION_ID_KEY[] = "transactionId";
    constexpr static char TRANSACTION_ID_IN_KEY[] = "transactionId_in";
    constexpr static char ASSET_ID_KEY[] = "assetId";
    constexpr static char ASSET_ID_IN_KEY[] = "assetId_in";
    constexpr static char TYPE_KEY[] = "type";
    constexpr static char TYPE_IN_KEY[] = "type_in";
    constexpr static char VALUE_KEY[] = "value";
    constexpr static char VALUE_GT_KEY[] = "value_gt";
    constexpr static char VALUE_GTE_KEY[] = "value_gte";
    constexpr static char VALUE_LT_KEY[] = "value_lt";
    constexpr static char VALUE_LTE_KEY[] = "value_lte";
    constexpr static char STATE_KEY[] = "state";
    constexpr static char STATE_IN_KEY[] = "state_in";
    constexpr static char WALLET_KEY[] = "wallet";
    constexpr static char WALLET_IN_KEY[] = "wallet_in";
};

}

#endif //ENJINCPPSDK_TRANSACTIONFILTER_HPP
