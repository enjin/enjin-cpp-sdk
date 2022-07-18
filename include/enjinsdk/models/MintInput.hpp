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

#ifndef ENJINCPPSDK_MINTINPUT_HPP
#define ENJINCPPSDK_MINTINPUT_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/ISerializable.hpp"
#include <memory>
#include <optional>
#include <string>

namespace enjin::sdk::models {

/// \brief Models a mint input for mint requests.
class ENJINSDK_EXPORT MintInput : public serialization::ISerializable {
public:
    /// \brief Constructs an instance of this class.
    MintInput();

    /// \brief Constructs an instance as a copy of another.
    /// \param other The other instance.
    MintInput(const MintInput& other);

    /// \brief Constructs an instance via move.
    /// \param other The other instance being moved.
    MintInput(MintInput&& other) noexcept;

    /// \brief Deconstructs this instance.
    ~MintInput() override;

    [[nodiscard]] std::string serialize() const override;

    /// \brief Sets the Ethereum address to mint to.
    /// \param address The address.
    /// \return This input for chaining.
    MintInput& set_to(std::string address);

    /// \brief Sets the amount of assets to mint.
    /// \param value The amount.
    /// \return This input for chaining.
    MintInput& set_value(std::string value);

    [[nodiscard]] json::JsonValue to_json() const override;

    bool operator==(const MintInput& rhs) const;

    bool operator!=(const MintInput& rhs) const;

    MintInput& operator=(const MintInput& rhs);

private:
    class Impl;

    std::unique_ptr<Impl> pimpl;
};

}

#endif //ENJINCPPSDK_MINTINPUT_HPP
