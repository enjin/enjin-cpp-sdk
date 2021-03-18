#include "enjinsdk/internal/PaginationArgumentsImpl.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::shared {

std::string PaginationArgumentsImpl::serialize() {
    rapidjson::Document document(rapidjson::kObjectType);

    if (pagination.has_value()) {
        utils::set_object_member_from_type<models::PaginationOptions>(document, "pagination", pagination.value());
    }

    return utils::document_to_string(document);
}

void PaginationArgumentsImpl::set_pagination(models::PaginationOptions pagination) {
    PaginationArgumentsImpl::pagination = pagination;
}

void PaginationArgumentsImpl::set_pagination(int page, int limit) {
    PaginationArgumentsImpl::set_pagination(models::PaginationOptions().set_page(page)
                                                                       .set_limit(limit));
}

bool PaginationArgumentsImpl::operator==(const PaginationArgumentsImpl& rhs) const {
    return pagination == rhs.pagination;
}

bool PaginationArgumentsImpl::operator!=(const PaginationArgumentsImpl& rhs) const {
    return !(rhs == *this);
}

}
