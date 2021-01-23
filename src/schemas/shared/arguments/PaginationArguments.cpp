#include "enjinsdk/internal/PaginationArguments.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::shared {

std::string PaginationArguments::serialize() {
    rapidjson::Document document(rapidjson::kObjectType);

    if (pagination.has_value()) {
        utils::set_object_member_from_type<models::PaginationOptions>(document, "pagination", pagination.value());
    }

    return utils::document_to_string(document);
}

void PaginationArguments::set_pagination(models::PaginationOptions pagination) {
    PaginationArguments::pagination = pagination;
}

void PaginationArguments::set_pagination(int page, int limit) {
    PaginationArguments::set_pagination(models::PaginationOptions().set_page(page)
                                                                   .set_limit(limit));
}

bool PaginationArguments::operator==(const PaginationArguments& rhs) const {
    return pagination == rhs.pagination;
}

bool PaginationArguments::operator!=(const PaginationArguments& rhs) const {
    return !(rhs == *this);
}

}
