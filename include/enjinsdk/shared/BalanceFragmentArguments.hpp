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

#ifndef ENJINCPPSDK_SHAREDBALANCEFRAGMENTARGUMENTS_HPP
#define ENJINCPPSDK_SHAREDBALANCEFRAGMENTARGUMENTS_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/ISerializable.hpp"
#include "enjinsdk/JsonUtils.hpp"
#include "enjinsdk/models/AssetIdFormat.hpp"
#include "enjinsdk/models/AssetIndexFormat.hpp"
#include <optional>
#include <string>
#include <type_traits>

namespace enjin::sdk::shared {

/// \brief Fragment interface used to request certain information from balances returned by the platform.
/// \tparam T The type of the implementing class.
template<class T>
class ENJINSDK_EXPORT BalanceFragmentArguments : public serialization::ISerializable {
public:
    ~BalanceFragmentArguments() override = default;

    [[nodiscard]] std::string serialize() const override {
        return to_json().to_string();
    }

    /// \brief Sets the desired asset ID format.
    /// \param bal_id_format The ID format.
    /// \return This request for chaining.
    T& set_bal_id_format(models::AssetIdFormat bal_id_format) {
        bal_id_format_opt = bal_id_format;
        return static_cast<T&>(*this);
    }

    /// \brief Sets the desired index format for non-fungible assets.
    /// \param bal_index_format The index format.
    /// \return This request for chaining.
    T& set_bal_index_format(models::AssetIndexFormat bal_index_format) {
        bal_index_format_opt = bal_index_format;
        return static_cast<T&>(*this);
    }

    /// \brief Sets the request to include the project UUID with the balance.
    /// \return This request for chaining.
    T& set_with_bal_project_uuid() {
        with_bal_project_uuid_opt = true;
        return static_cast<T&>(*this);
    }

    /// \brief Sets the request to include the wallet address with balance.
    /// \return This request for chaining.
    T& set_with_bal_wallet_address() {
        with_bal_wallet_address_opt = true;
        return static_cast<T&>(*this);
    }

    [[nodiscard]] json::JsonValue to_json() const override {
        json::JsonValue json = json::JsonValue::create_object();

        utils::JsonUtils::try_set_field(json, "balIdFormat", bal_id_format_opt);
        utils::JsonUtils::try_set_field(json, "balIndexFormat", bal_index_format_opt);
        utils::JsonUtils::try_set_field(json, "withBalProjectUuid", with_bal_project_uuid_opt);
        utils::JsonUtils::try_set_field(json, "withBalWalletAddress", with_bal_wallet_address_opt);

        return json;
    }

    bool operator==(const BalanceFragmentArguments& rhs) const {
        return bal_id_format_opt == rhs.bal_id_format_opt
               && bal_index_format_opt == rhs.bal_index_format_opt
               && with_bal_project_uuid_opt == rhs.with_bal_project_uuid_opt
               && with_bal_wallet_address_opt == rhs.with_bal_wallet_address_opt;
    }

    bool operator!=(const BalanceFragmentArguments& rhs) const {
        return !(*this == rhs);
    }

protected:
    /// \brief Sole constructor.
    BalanceFragmentArguments() {
        static_assert(std::is_base_of<BalanceFragmentArguments, T>::value,
                      "Class T does not inherit from BalanceFragmentArguments.");
    }

private:
    std::optional<models::AssetIdFormat> bal_id_format_opt;
    std::optional<models::AssetIndexFormat> bal_index_format_opt;
    std::optional<bool> with_bal_project_uuid_opt;
    std::optional<bool> with_bal_wallet_address_opt;
};

}

#endif //ENJINCPPSDK_SHAREDBALANCEFRAGMENTARGUMENTS_HPP
