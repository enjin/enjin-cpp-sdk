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

#ifndef ENJINCPPSDK_TRANSFERINPUT_HPP
#define ENJINCPPSDK_TRANSFERINPUT_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/ISerializable.hpp"
#include <memory>
#include <optional>
#include <string>

namespace enjin::sdk::models {

/// \brief Models a transfer input for transfer requests.
class ENJINSDK_EXPORT TransferInput : public serialization::ISerializable {
public:
    /// \brief Constructs an instance of this class.
    TransferInput();

    /// \brief Constructs an instance as a copy of another.
    /// \param other The other instance.
    TransferInput(const TransferInput& other);

    /// \brief Constructs an instance via move.
    /// \param other The other instance being moved.
    TransferInput(TransferInput&& other) noexcept;

    /// \brief Deconstructs this instance.
    ~TransferInput() override;

    [[nodiscard]] std::string serialize() const override;

    /// Sets the source Ethereum address.
    /// \param address The source.
    /// \return This input for chaining.
    TransferInput& set_from(std::string address);

    /// Sets the destination Ethereum address.
    /// \param address The destination.
    /// \return This input for chaining.
    TransferInput& set_to(std::string address);

    /// Sets the asset ID to transfer or ENJ if unused.
    /// \param id The ID.
    /// \return This input for chaining.
    TransferInput& set_asset_id(std::string id);

    /// Sets the index for non-fungible assets.
    /// \param index The index.
    /// \return This input for chaining.
    TransferInput& set_asset_index(std::string index);

    /// Sets the amount of assets to transfer.
    /// \param value The amount.
    /// \return This input for chaining.
    TransferInput& set_value(std::string value);

    [[nodiscard]] json::JsonValue to_json() const override;

    bool operator==(const TransferInput& rhs) const;

    bool operator!=(const TransferInput& rhs) const;

    TransferInput& operator=(const TransferInput& rhs);

private:
    class Impl;

    std::unique_ptr<Impl> pimpl;
};

}

#endif //ENJINCPPSDK_TRANSFERINPUT_HPP
