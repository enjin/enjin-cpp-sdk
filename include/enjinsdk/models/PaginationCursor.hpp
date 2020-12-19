#ifndef ENJINCPPSDK_PAGINATIONCURSOR_HPP
#define ENJINCPPSDK_PAGINATIONCURSOR_HPP

#include "enjinsdk/serialization/ISerializable.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::models {

/// \brief Models a pagination cursor for queries.
class PaginationCursor : public enjin::sdk::serialization::ISerializable {
public:
    /// \brief Default constructor.
    PaginationCursor() = default;

    bool operator==(const PaginationCursor& rhs) const;

    bool operator!=(const PaginationCursor& rhs) const;

    void deserialize(const char* json) override;

    std::string serialize() override;

    /// \brief Returns the total number of items selected by the cursor.
    /// \return Optional for the total number of items.
    std::optional<int> get_total();

    /// \brief Returns the number of items per page for the cursor.
    /// \return Optional for the number items per page.
    std::optional<int> get_per_page();

    /// \brief Returns the current page for the cursor.
    /// \return Optional for the current page number.
    std::optional<int> get_current_page();

    /// \brief Returns whether the cursor has pages.
    /// \return Optional for whether the cursor has pages.
    std::optional<bool> get_has_pages();

    /// \brief Returns the first item returned for the cursor.
    /// \return Optional for the first item returned.
    std::optional<int> get_from();

    /// \brief Returns the last item returned for the cursor.
    /// \return Optional for the last item returned.
    std::optional<int> get_to();

    /// \brief Returns the last page (number of pages) for the cursor.
    /// \return Optional for the last page number.
    std::optional<int> get_last_page();

    /// \brief Returns whether there are more pages for the cursor.
    /// \return Optional for whether the cursor has more pages.
    std::optional<bool> get_has_more_pages();

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
