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

#ifndef ENJINCPPSDK_ASSETFILTER_HPP
#define ENJINCPPSDK_ASSETFILTER_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/ISerializable.hpp"
#include <optional>
#include <string>
#include <vector>

namespace enjin::sdk::models {

/// \brief Models a filter input for asset queries.
class ENJINSDK_EXPORT AssetFilter : public serialization::ISerializable {
public:
    /// \brief Default constructor.
    AssetFilter() = default;

    ~AssetFilter() override = default;

    [[nodiscard]] std::string serialize() const override;

    /// \brief Sets the filter to include other filters to intersect with.
    /// \param others The other filters.
    /// \return This filter for chaining.
    AssetFilter& set_and(const std::vector<AssetFilter>& others);

    /// \brief Sets the filter to include other filters to union with.
    /// \param others The other filters.
    /// \return This filter for chaining.
    AssetFilter& set_or(const std::vector<AssetFilter>& others);

    /// \brief Sets the asset ID to filter for.
    /// \param id The ID.
    /// \return This filter for chaining.
    AssetFilter& set_id(const std::string& id);

    /// \brief Sets the asset IDs to filter for.
    /// \param ids The IDs.
    /// \return This filter for chaining.
    AssetFilter& set_id_in(const std::vector<std::string>& ids);

    /// \brief Sets the name to filter.
    /// \param name The name.
    /// \return This filter for chaining.
    AssetFilter& set_name(const std::string& name);

    /// \brief Sets the filter to include
    /// \param text The text.
    /// \return This filter for chaining.
    AssetFilter& set_name_contains(const std::string& text);

    /// \brief Sets the names to filter for.
    /// \param names The names.
    /// \return This filter for chaining.
    AssetFilter& set_name_in(const std::vector<std::string>& names);

    /// \brief Sets the filter to include assets with names which start with the passed prefix.
    /// \param prefix The prefix.
    /// \return This filter for chaining.
    AssetFilter& set_name_starts_with(const std::string& prefix);

    /// \brief Sets the filter to include assets with names which end with the passed suffix.
    /// \param suffix The suffix.
    /// \return This filter for chaining.
    AssetFilter& set_name_ends_with(const std::string& suffix);

    /// \brief Sets the wallet to filter for.
    /// \param wallet The wallet address.
    /// \return This filter for chaining.
    AssetFilter& set_wallet(const std::string& wallet);

    /// \brief Sets the wallets to filter for.
    /// \param wallets The wallet addresses.
    /// \return This filter for chaining.
    AssetFilter& set_wallet_in(const std::vector<std::string>& wallets);

    bool operator==(const AssetFilter& rhs) const;

    bool operator!=(const AssetFilter& rhs) const;

private:
    std::optional<std::vector<AssetFilter>> and_filters;
    std::optional<std::vector<AssetFilter>> or_filters;
    std::optional<std::string> id;
    std::optional<std::vector<std::string>> id_in;
    std::optional<std::string> name;
    std::optional<std::string> name_contains;
    std::optional<std::vector<std::string>> name_in;
    std::optional<std::string> name_starts_with;
    std::optional<std::string> name_ends_with;
    std::optional<std::string> wallet;
    std::optional<std::vector<std::string>> wallet_in;

    constexpr static char AND_KEY[] = "and";
    constexpr static char OR_KEY[] = "or";
    constexpr static char ID_KEY[] = "id";
    constexpr static char ID_IN_KEY[] = "id_in";
    constexpr static char NAME_KEY[] = "name";
    constexpr static char NAME_CONTAINS_KEY[] = "name_contains";
    constexpr static char NAME_IN_KEY[] = "name_in";
    constexpr static char NAME_STARTS_WITH_KEY[] = "name_starts_with";
    constexpr static char NAME_ENDS_WITH_KEY[] = "name_ends_with";
    constexpr static char WALLET_KEY[] = "wallet";
    constexpr static char WALLET_IN_KEY[] = "wallet_in";
};

}

#endif //ENJINCPPSDK_ASSETFILTER_HPP
