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

#ifndef ENJINCPPSDK_PAGINATIONINPUT_HPP
#define ENJINCPPSDK_PAGINATIONINPUT_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/ISerializable.hpp"
#include <memory>
#include <optional>
#include <string>

namespace enjin::sdk::models {

/// \brief Models a pagination input for pagination requests.
class ENJINSDK_EXPORT PaginationInput : public serialization::ISerializable {
public:
    /// \brief Constructs an instance of this class.
    PaginationInput();

    /// \brief Constructs an instance as a copy of another.
    /// \param other The other instance.
    PaginationInput(const PaginationInput& other);

    /// \brief Constructs an instance via move.
    /// \param other The other instance being moved.
    PaginationInput(PaginationInput&& other) noexcept;

    /// \brief Deconstructs this instance.
    ~PaginationInput() override;

    [[nodiscard]] std::string serialize() const override;

    /// \brief Sets the page number to start at for the pagination.
    /// \param page The page number.
    /// \return This input for chaining.
    PaginationInput& set_page(int page);

    /// \brief Sets the number of items per page for the pagination.
    /// \param limit The number of items per page.
    /// \return This input for chaining.
    PaginationInput& set_limit(int limit);

    [[nodiscard]] json::JsonValue to_json() const override;

    bool operator==(const PaginationInput& rhs) const;

    bool operator!=(const PaginationInput& rhs) const;

    PaginationInput& operator=(const PaginationInput& rhs);

private:
    class Impl;

    std::unique_ptr<Impl> pimpl;
};

}

#endif //ENJINCPPSDK_PAGINATIONINPUT_HPP
