#include "enjinsdk/models/PaginationCursor.hpp"

#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

namespace enjin::sdk::models {

void PaginationCursor::deserialize(const std::string& json) {
    rapidjson::Document document;
    document.Parse(json.c_str());
    if (document.IsObject()) {
        if (document.HasMember(TOTAL_KEY) && document[TOTAL_KEY].IsInt()) {
            total.emplace(document[TOTAL_KEY].GetInt());
        }
        if (document.HasMember(PER_PAGE_KEY) && document[PER_PAGE_KEY].IsInt()) {
            per_page.emplace(document[PER_PAGE_KEY].GetInt());
        }
        if (document.HasMember(CURRENT_PAGE_KEY) && document[CURRENT_PAGE_KEY].IsInt()) {
            current_page.emplace(document[CURRENT_PAGE_KEY].GetInt());
        }
        if (document.HasMember(HAS_PAGES_KEY) && document[HAS_PAGES_KEY].IsBool()) {
            has_pages.emplace(document[HAS_PAGES_KEY].GetBool());
        }
        if (document.HasMember(FROM_KEY) && document[FROM_KEY].IsInt()) {
            from.emplace(document[FROM_KEY].GetInt());
        }
        if (document.HasMember(TO_KEY) && document[TO_KEY].IsInt()) {
            to.emplace(document[TO_KEY].GetInt());
        }
        if (document.HasMember(LAST_PAGE_KEY) && document[LAST_PAGE_KEY].IsInt()) {
            last_page.emplace(document[LAST_PAGE_KEY].GetInt());
        }
        if (document.HasMember(HAS_MORE_PAGES_KEY) && document[HAS_MORE_PAGES_KEY].IsBool()) {
            has_more_pages.emplace(document[HAS_MORE_PAGES_KEY].GetBool());
        }
    }
}

const std::optional<int>& PaginationCursor::get_total() const {
    return total;
}

const std::optional<int>& PaginationCursor::get_per_page() const {
    return per_page;
}

const std::optional<int>& PaginationCursor::get_current_page() const {
    return current_page;
}

const std::optional<bool>& PaginationCursor::get_has_pages() const {
    return has_pages;
}

const std::optional<int>& PaginationCursor::get_from() const {
    return from;
}

const std::optional<int>& PaginationCursor::get_to() const {
    return to;
}

const std::optional<int>& PaginationCursor::get_last_page() const {
    return last_page;
}

const std::optional<bool>& PaginationCursor::get_has_more_pages() const {
    return has_more_pages;
}

bool PaginationCursor::operator==(const PaginationCursor& rhs) const {
    return total == rhs.total &&
           per_page == rhs.per_page &&
           current_page == rhs.current_page &&
           has_pages == rhs.has_pages &&
           from == rhs.from &&
           to == rhs.to &&
           last_page == rhs.last_page &&
           has_more_pages == rhs.has_more_pages;
}

bool PaginationCursor::operator!=(const PaginationCursor& rhs) const {
    return !(rhs == *this);
}

}
