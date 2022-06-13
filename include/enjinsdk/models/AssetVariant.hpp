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

#ifndef ENJINCPPSDK_ASSETVARIANT_HPP
#define ENJINCPPSDK_ASSETVARIANT_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/IDeserializable.hpp"
#include "enjinsdk/JsonValue.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::models {

/// \brief Models a asset variant.
class ENJINSDK_EXPORT AssetVariant : public serialization::IDeserializable {
public:
    /// \brief Default constructor.
    AssetVariant() = default;

    ~AssetVariant() override = default;

    void deserialize(const std::string& json) override;

    /// \brief Returns the ID of this variant.
    /// \return The ID.
    [[nodiscard]] const std::optional<int>& get_id() const;

    /// \brief Returns the the ID of the asset this variant belongs to.
    /// \return The asset ID.
    [[nodiscard]] const std::optional<std::string>& get_asset_id() const;

    /// \brief Returns the metadata of this variant.
    /// \return The metadata.
    [[nodiscard]] const std::optional<json::JsonValue>& get_variant_metadata() const;

    /// \brief Returns the usage count of this variant.
    /// \return The usage count.
    [[nodiscard]] const std::optional<int>& get_usage_count() const;

    /// \brief Returns the datetime when this variant was created.
    /// \return The datetime.
    /// \remarks The datetime is formatted using the ISO 8601 date format.
    [[nodiscard]] const std::optional<std::string>& get_created_at() const;

    /// \brief Returns the datetime when this variant was last updated.
    /// \return The datetime.
    /// \remarks The datetime is formatted using the ISO 8601 date format.
    [[nodiscard]] const std::optional<std::string>& get_updated_at() const;

    bool operator==(const AssetVariant& rhs) const;

    bool operator!=(const AssetVariant& rhs) const;

private:
    std::optional<int> id;
    std::optional<std::string> asset_id;
    std::optional<json::JsonValue> variant_metadata;
    std::optional<int> usage_count;
    std::optional<std::string> created_at;
    std::optional<std::string> updated_at;
};

}

#endif //ENJINCPPSDK_ASSETVARIANT_HPP
