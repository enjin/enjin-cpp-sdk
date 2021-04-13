#include "enjinsdk/models/Trade.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::models {

std::string Trade::serialize() const {
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

Trade& Trade::set_asset_id(const std::string& id) {
    asset_id = id;
    return *this;
}

Trade& Trade::set_asset_index(const std::string& index) {
    asset_index = index;
    return *this;
}

Trade& Trade::set_value(const std::string& value) {
    Trade::value = value;
    return *this;
}

bool Trade::operator==(const Trade& rhs) const {
    return asset_id == rhs.asset_id &&
           asset_index == rhs.asset_index &&
           value == rhs.value;
}

bool Trade::operator!=(const Trade& rhs) const {
    return !(rhs == *this);
}

}
