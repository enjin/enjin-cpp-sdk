#include "enjinsdk/models/PaginationOptions.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::models {

std::string PaginationOptions::serialize() {
    rapidjson::Document document(rapidjson::kObjectType);

    if (page.has_value()) {
        utils::set_integer_member(document, PAGE_KEY, page.value());
    }
    if (limit.has_value()) {
        utils::set_integer_member(document, LIMIT_KEY, limit.value());
    }

    return utils::document_to_string(document);
}

PaginationOptions& PaginationOptions::set_page(int page) {
    PaginationOptions::page = page;
    return *this;
}

PaginationOptions& PaginationOptions::set_limit(int limit) {
    PaginationOptions::limit = limit;
    return *this;
}

bool PaginationOptions::operator==(const PaginationOptions& rhs) const {
    return page == rhs.page &&
           limit == rhs.limit;
}

bool PaginationOptions::operator!=(const PaginationOptions& rhs) const {
    return !(rhs == *this);
}

}
