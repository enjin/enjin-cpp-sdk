#ifndef ENJINCPPSDK_PAGINATIONCURSOR_HPP
#define ENJINCPPSDK_PAGINATIONCURSOR_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/IDeserializable.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::models {

/// \brief Models a pagination cursor for queries.
class ENJINSDK_EXPORT PaginationCursor : public serialization::IDeserializable {
public:
    /// \brief Default constructor.
    PaginationCursor() = default;

    ~PaginationCursor() override = default;

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

private:
    std::optional<int> total;
    std::optional<int> per_page;
    std::optional<int> current_page;
    std::optional<bool> has_pages;
    std::optional<int> from;
    std::optional<int> to;
    std::optional<int> last_page;
    std::optional<bool> has_more_pages;

    constexpr static char TOTAL_KEY[] = "total";
    constexpr static char PER_PAGE_KEY[] = "perPage";
    constexpr static char CURRENT_PAGE_KEY[] = "currentPage";
    constexpr static char HAS_PAGES_KEY[] = "hasPages";
    constexpr static char FROM_KEY[] = "from";
    constexpr static char TO_KEY[] = "to";
    constexpr static char LAST_PAGE_KEY[] = "lastPage";
    constexpr static char HAS_MORE_PAGES_KEY[] = "hasMorePages";
};

}

#endif //ENJINCPPSDK_PAGINATIONCURSOR_HPP
