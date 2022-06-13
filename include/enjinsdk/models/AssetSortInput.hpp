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

#ifndef ENJINCPPSDK_ASSETSORTINPUT_HPP
#define ENJINCPPSDK_ASSETSORTINPUT_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/ISerializable.hpp"
#include "enjinsdk/models/SortDirection.hpp"
#include "enjinsdk/models/AssetField.hpp"
#include <memory>
#include <optional>
#include <string>

namespace enjin::sdk::models {

/// \brief Models sorting input for Assets.
class ENJINSDK_EXPORT AssetSortInput : public serialization::ISerializable {
public:
    /// \brief Constructs an instance of this class.
    AssetSortInput();

    /// \brief Constructs an instance as a copy of another.
    /// \param other The other instance.
    AssetSortInput(const AssetSortInput& other);

    /// \brief Constructs an instance via move.
    /// \param other The other instance being moved.
    AssetSortInput(AssetSortInput&& other) noexcept;

    /// \brief Deconstructs this instance.
    ~AssetSortInput() override;

    [[nodiscard]] std::string serialize() const override;

    /// \brief Sets the field to sort by.
    /// \param field The field.
    /// \return This input for chaining.
    AssetSortInput& set_field(AssetField field);

    /// \brief Sets the direction to sort by.
    /// \param direction The direction.
    /// \return This input for chaining.
    AssetSortInput& set_direction(SortDirection direction);

    [[nodiscard]] json::JsonValue to_json() const override;

    bool operator==(const AssetSortInput& rhs) const;

    bool operator!=(const AssetSortInput& rhs) const;

    AssetSortInput& operator=(const AssetSortInput& rhs);

private:
    class Impl;

    std::unique_ptr<Impl> pimpl;
};

}

#endif //ENJINCPPSDK_ASSETSORTINPUT_HPP
