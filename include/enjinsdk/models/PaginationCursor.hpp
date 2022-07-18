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

#ifndef ENJINCPPSDK_PAGINATIONCURSOR_HPP
#define ENJINCPPSDK_PAGINATIONCURSOR_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/IDeserializable.hpp"
#include <memory>
#include <optional>
#include <string>

namespace enjin::sdk::models {

/// \brief Models a pagination cursor for queries.
class ENJINSDK_EXPORT PaginationCursor : public serialization::IDeserializable {
public:
    /// \brief Constructs an instance of this class.
    PaginationCursor();

    /// \brief Constructs an instance as a copy of another.
    /// \param other The other instance.
    PaginationCursor(const PaginationCursor& other);

    /// \brief Constructs an instance via move.
    /// \param other The other instance being moved.
    PaginationCursor(PaginationCursor&& other) noexcept;

    /// \brief Deconstructs this instance.
    ~PaginationCursor() override;

    void deserialize(const std::string& json) override;

    /// \brief Returns the total number of items selected by this cursor.
    /// \return The total number of items.
    [[nodiscard]] const std::optional<int>& get_total() const;

    /// \brief Returns the number of items per page for this cursor.
    /// \return The number items per page.
    [[nodiscard]] const std::optional<int>& get_per_page() const;

    /// \brief Returns the current page for this cursor.
    /// \return The current page number.
    [[nodiscard]] const std::optional<int>& get_current_page() const;

    /// \brief Returns whether this cursor has pages.
    /// \return Whether the cursor has pages.
    [[nodiscard]] const std::optional<bool>& get_has_pages() const;

    /// \brief Returns the first item returned for this cursor.
    /// \return The first item returned.
    [[nodiscard]] const std::optional<int>& get_from() const;

    /// \brief Returns the last item returned for this cursor.
    /// \return The last item returned.
    [[nodiscard]] const std::optional<int>& get_to() const;

    /// \brief Returns the last page (number of pages) for this cursor.
    /// \return The last page number.
    [[nodiscard]] const std::optional<int>& get_last_page() const;

    /// \brief Returns whether there are more pages for this cursor.
    /// \return Whether the cursor has more pages.
    [[nodiscard]] const std::optional<bool>& get_has_more_pages() const;

    bool operator==(const PaginationCursor& rhs) const;

    bool operator!=(const PaginationCursor& rhs) const;

    PaginationCursor& operator=(const PaginationCursor& rhs);

private:
    class Impl;

    std::unique_ptr<Impl> pimpl;
};

}

#endif //ENJINCPPSDK_PAGINATIONCURSOR_HPP
