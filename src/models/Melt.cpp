#include "enjinsdk/models/Melt.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::models {

std::string Melt::serialize() const {
    rapidjson::Document document(rapidjson::kObjectType);

    if (asset_id.has_value()) {
        utils::set_string_member(document, ASSET_ID_KEY, asset_id.value());
    }
    if (asset_index.has_value()) {
        utils::set_string_member(document, ASSET_INDEX_KEY, asset_index.value());
    }
    if (value.has_value()) {
        utils::set_string_member(document, VALUE_KEY, value.value());
    }

    return utils::document_to_string(document);
}

Melt& Melt::set_asset_id(const std::string& id) {
    asset_id = id;
    return *this;
}

Melt& Melt::set_asset_index(const std::string& index) {
    asset_index = index;
    return *this;
}

Melt& Melt::set_value(const std::string& value) {
    Melt::value = value;
    return *this;
}

bool Melt::operator==(const Melt& rhs) const {
    return asset_id == rhs.asset_id &&
           asset_index == rhs.asset_index &&
           value == rhs.value;
}

bool Melt::operator!=(const Melt& rhs) const {
    return !(rhs == *this);
}

}
