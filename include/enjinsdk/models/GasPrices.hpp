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

#ifndef ENJINCPPSDK_GASPRICES_HPP
#define ENJINCPPSDK_GASPRICES_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/IDeserializable.hpp"
#include <memory>
#include <optional>
#include <string>

namespace enjin::sdk::models {

/// \brief Models gas prices on the platform.
class ENJINSDK_EXPORT GasPrices : public serialization::IDeserializable {
public:
    /// \brief Constructs an instance of this class.
    GasPrices();

    /// \brief Constructs an instance as a copy of another.
    /// \param other The other instance.
    GasPrices(const GasPrices& other);

    /// \brief Constructs an instance via move.
    /// \param other The other instance being moved.
    GasPrices(GasPrices&& other) noexcept;

    /// \brief Deconstructs this instance.
    ~GasPrices() override;

    void deserialize(const std::string& json) override;

    /// \brief Returns the recommended safe gas price in Gwei.
    /// \return The gas price.
    /// \remarks Expected to be mined in less than 30 minutes.
    [[nodiscard]] const std::optional<float>& get_safe_low() const;

    /// \brief Returns the recommended average gas price in Gwei.
    /// \return The gas price.
    /// \remarks Expected to be mined in less than 5 minutes.
    [[nodiscard]] const std::optional<float>& get_average() const;

    /// \brief Returns the recommended fast gas price in Gwei.
    /// \return The gas price.
    /// \remarks Expected to be mined in less than 2 minutes.
    [[nodiscard]] const std::optional<float>& get_fast() const;

    /// \brief Returns the recommended fastest gas price in Gwei.
    /// \return The gas price.
    /// \remarks Expected to be mined in less than 30 seconds.
    [[nodiscard]] const std::optional<float>& get_fastest() const;

    bool operator==(const GasPrices& rhs) const;

    bool operator!=(const GasPrices& rhs) const;

    GasPrices& operator=(const GasPrices& rhs);

private:
    class Impl;

    std::unique_ptr<Impl> pimpl;
};

}

#endif //ENJINCPPSDK_GASPRICES_HPP
