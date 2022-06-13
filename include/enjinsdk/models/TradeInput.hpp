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

#ifndef ENJINCPPSDK_TRADEINPUT_HPP
#define ENJINCPPSDK_TRADEINPUT_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/ISerializable.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::models {

/// \brief Models a trade input for trade requests.
class ENJINSDK_EXPORT TradeInput : public serialization::ISerializable {
public:
    /// \brief Default constructor.
    TradeInput() = default;

    ~TradeInput() override = default;

    [[nodiscard]] std::string serialize() const override;

    /// Sets the asset ID to trade or ENJ if unused.
    /// \param id The ID.
    /// \return This input for chaining.
    TradeInput& set_asset_id(std::string id);

    /// Sets the index for non-fungible assets.
    /// \param index The index.
    /// \return This input for chaining.
    TradeInput& set_asset_index(std::string index);

    /// Sets the amount of assets to trade.
    /// \param value The amount.
    /// \return This input for chaining.
    TradeInput& set_value(std::string value);

    [[nodiscard]] json::JsonValue to_json() const override;

    bool operator==(const TradeInput& rhs) const;

    bool operator!=(const TradeInput& rhs) const;

private:
    std::optional<std::string> asset_id_opt;
    std::optional<std::string> asset_index_opt;
    std::optional<std::string> value_opt;
};

}

#endif //ENJINCPPSDK_TRADEINPUT_HPP
