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
#include <memory>
#include <optional>
#include <string>

namespace enjin::sdk::models {

/// \brief Models a trade input for trade requests.
class ENJINSDK_EXPORT TradeInput : public serialization::ISerializable {
public:
    /// \brief Constructs an instance of this class.
    TradeInput();

    /// \brief Constructs an instance as a copy of another.
    /// \param other The other instance.
    TradeInput(const TradeInput& other);

    /// \brief Constructs an instance via move.
    /// \param other The other instance being moved.
    TradeInput(TradeInput&& other) noexcept;

    /// \brief Deconstructs this instance.
    ~TradeInput() override;

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

    TradeInput& operator=(const TradeInput& rhs);

private:
    class Impl;

    std::unique_ptr<Impl> pimpl;
};

}

#endif //ENJINCPPSDK_TRADEINPUT_HPP
