#include "enjinsdk/models/TransactionSort.hpp"

#include "EnumUtils.hpp"
#include "RapidJsonUtils.hpp"

namespace enjin::sdk::models {

std::string TransactionSort::serialize() const {
    rapidjson::Document document(rapidjson::kObjectType);

    if (field.has_value()) {
        utils::set_string_member(document, FIELD_KEY, utils::serialize_transaction_field(field.value()));
    }
    if (direction.has_value()) {
        utils::set_string_member(document, DIRECTION_KEY, utils::serialize_sort_direction(direction.value()));
    }

    return utils::document_to_string(document);
}

TransactionSort& TransactionSort::set_field(TransactionField field) {
    TransactionSort::field = field;
    return *this;
}

TransactionSort& TransactionSort::set_direction(SortDirection direction) {
    TransactionSort::direction = direction;
    return *this;
}

bool TransactionSort::operator==(const TransactionSort& rhs) const {
    return field == rhs.field &&
           direction == rhs.direction;
}

bool TransactionSort::operator!=(const TransactionSort& rhs) const {
    return !(rhs == *this);
}

}
