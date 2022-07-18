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
#include <memory>
#include <optional>
#include <string>
#include <vector>

namespace enjin::sdk::models {

/// \brief Models a filter input for asset queries.
class ENJINSDK_EXPORT AssetFilter : public serialization::ISerializable {
public:
    /// \brief Constructs an instance of this class.
    AssetFilter();

    /// \brief Constructs an instance as a copy of another.
    /// \param other The other instance.
    AssetFilter(const AssetFilter& other);

    /// \brief Constructs an instance via move.
    /// \param other The other instance being moved.
    AssetFilter(AssetFilter&& other) noexcept;

    /// \brief Deconstructs this instance.
    ~AssetFilter() override;

    [[nodiscard]] std::string serialize() const override;

    /// \brief Sets the filter to include other filters to intersect with.
    /// \param others The other filters.
    /// \return This filter for chaining.
    AssetFilter& set_and(std::vector<AssetFilter> others);

    /// \brief Sets the filter to include other filters to union with.
    /// \param others The other filters.
    /// \return This filter for chaining.
    AssetFilter& set_or(std::vector<AssetFilter> others);

    /// \brief Sets the asset ID to filter for.
    /// \param id The ID.
    /// \return This filter for chaining.
    AssetFilter& set_id(std::string id);

    /// \brief Sets the asset IDs to filter for.
    /// \param ids The IDs.
    /// \return This filter for chaining.
    AssetFilter& set_id_in(std::vector<std::string> ids);

    /// \brief Sets the name to filter.
    /// \param name The name.
    /// \return This filter for chaining.
    AssetFilter& set_name(std::string name);

    /// \brief Sets the filter to include
    /// \param text The text.
    /// \return This filter for chaining.
    AssetFilter& set_name_contains(std::string text);

    /// \brief Sets the names to filter for.
    /// \param names The names.
    /// \return This filter for chaining.
    AssetFilter& set_name_in(std::vector<std::string> names);

    /// \brief Sets the filter to include assets with names which start with the passed prefix.
    /// \param prefix The prefix.
    /// \return This filter for chaining.
    AssetFilter& set_name_starts_with(std::string prefix);

    /// \brief Sets the filter to include assets with names which end with the passed suffix.
    /// \param suffix The suffix.
    /// \return This filter for chaining.
    AssetFilter& set_name_ends_with(std::string suffix);

    /// \brief Sets the wallet to filter for.
    /// \param wallet The wallet address.
    /// \return This filter for chaining.
    AssetFilter& set_wallet(std::string wallet);

    /// \brief Sets the wallets to filter for.
    /// \param wallets The wallet addresses.
    /// \return This filter for chaining.
    AssetFilter& set_wallet_in(std::vector<std::string> wallets);

    [[nodiscard]] json::JsonValue to_json() const override;

    bool operator==(const AssetFilter& rhs) const;

    bool operator!=(const AssetFilter& rhs) const;

    AssetFilter& operator=(const AssetFilter& rhs);

private:
    class Impl;

    std::unique_ptr<Impl> pimpl;
};

}

#endif //ENJINCPPSDK_ASSETFILTER_HPP
