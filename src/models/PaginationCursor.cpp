#include "enjinsdk/models/PaginationCursor.hpp"

#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

namespace enjin::sdk::models {

void PaginationCursor::deserialize(const char* json) {
    rapidjson::Document document;
    document.Parse(json);
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

std::string PaginationCursor::serialize() {
    rapidjson::Document document;
    document.SetObject();

    if (total.has_value()) {
        rapidjson::Value v(total.value());
        document.AddMember(TOTAL_KEY, v, document.GetAllocator());
    }
    if (per_page.has_value()) {
        rapidjson::Value v(per_page.value());
        document.AddMember(PER_PAGE_KEY, v, document.GetAllocator());
    }
    if (current_page.has_value()) {
        rapidjson::Value v(current_page.value());
        document.AddMember(CURRENT_PAGE_KEY, v, document.GetAllocator());
    }
    if (has_pages.has_value()) {
        rapidjson::Value v(has_pages.value());
        document.AddMember(HAS_PAGES_KEY, v, document.GetAllocator());
    }
    if (from.has_value()) {
        rapidjson::Value v(from.value());
        document.AddMember(FROM_KEY, v, document.GetAllocator());
    }
    if (to.has_value()) {
        rapidjson::Value v(to.value());
        document.AddMember(TO_KEY, v, document.GetAllocator());
    }
    if (last_page.has_value()) {
        rapidjson::Value v(last_page.value());
        document.AddMember(LAST_PAGE_KEY, v, document.GetAllocator());
    }
    if (has_more_pages.has_value()) {
        rapidjson::Value v(has_more_pages.value());
        document.AddMember(HAS_MORE_PAGES_KEY, v, document.GetAllocator());
    }

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);
    const char* json = buffer.GetString();

    return std::string(json);
}

std::optional<int> PaginationCursor::get_total() {
    return total;
}

std::optional<int> PaginationCursor::get_per_page() {
    return per_page;
}

std::optional<int> PaginationCursor::get_current_page() {
    return current_page;
}

std::optional<bool> PaginationCursor::get_has_pages() {
    return has_pages;
}

std::optional<int> PaginationCursor::get_from() {
    return from;
}

std::optional<int> PaginationCursor::get_to() {
    return to;
}

std::optional<int> PaginationCursor::get_last_page() {
    return last_page;
}

std::optional<bool> PaginationCursor::get_has_more_pages() {
    return has_more_pages;
}

}
