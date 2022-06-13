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

#ifndef ENJINCPPSDK_SUPPLYMODELS_HPP
#define ENJINCPPSDK_SUPPLYMODELS_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/IDeserializable.hpp"
#include <memory>
#include <optional>
#include <string>

namespace enjin::sdk::models {

/// \brief Models the supply models used by the platform.
class ENJINSDK_EXPORT SupplyModels : public serialization::IDeserializable {
public:
    /// \brief Constructs an instance of this class.
    SupplyModels();

    /// \brief Constructs an instance as a copy of another.
    /// \param other The other instance.
    SupplyModels(const SupplyModels& other);

    /// \brief Constructs an instance via move.
    /// \param other The other instance being moved.
    SupplyModels(SupplyModels&& other) noexcept;

    /// \brief Deconstructs this instance.
    ~SupplyModels() override;

    void deserialize(const std::string& json) override;

    /// \brief Returns the fixed model.
    /// \return The fixed model.
    [[nodiscard]] const std::optional<std::string>& get_fixed() const;

    /// \brief Returns the settable model.
    /// \return The settable model.
    [[nodiscard]] const std::optional<std::string>& get_settable() const;

    /// \brief Returns the infinite model.
    /// \return The infinite model.
    [[nodiscard]] const std::optional<std::string>& get_infinite() const;

    /// \brief Returns the collapsing model.
    /// \return The collapsing model.
    [[nodiscard]] const std::optional<std::string>& get_collapsing() const;

    /// \brief Returns the annual value model.
    /// \return The annual value model.
    [[nodiscard]] const std::optional<std::string>& get_annual_value() const;

    /// \brief Returns the annual percentage model.
    /// \return The annual percentage model.
    [[nodiscard]] const std::optional<std::string>& get_annual_percentage() const;

    bool operator==(const SupplyModels& rhs) const;

    bool operator!=(const SupplyModels& rhs) const;

    SupplyModels& operator=(const SupplyModels& rhs);

private:
    class Impl;

    std::unique_ptr<Impl> pimpl;
};

}

#endif //ENJINCPPSDK_SUPPLYMODELS_HPP
