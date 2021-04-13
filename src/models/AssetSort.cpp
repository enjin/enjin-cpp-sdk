#include "enjinsdk/models/AssetSort.hpp"

#include "EnumUtils.hpp"
#include "RapidJsonUtils.hpp"

namespace enjin::sdk::models {

std::string AssetSort::serialize() const {
    rapidjson::Document document(rapidjson::kObjectType);

    if (field.has_value()) {
        utils::set_string_member(document, FIELD_KEY, utils::serialize_asset_field(field.value()));
    }
    if (direction.has_value()) {
        utils::set_string_member(document, DIRECTION_KEY, utils::serialize_sort_direction(direction.value()));
    }

    return utils::document_to_string(document);
}

AssetSort& AssetSort::set_field(AssetField field) {
    AssetSort::field = field;
    return *this;
}

AssetSort& AssetSort::set_direction(SortDirection direction) {
    AssetSort::direction = direction;
    return *this;
}

bool AssetSort::operator==(const AssetSort& rhs) const {
    return field == rhs.field &&
           direction == rhs.direction;
}

bool AssetSort::operator!=(const AssetSort& rhs) const {
    return !(rhs == *this);
}

}
