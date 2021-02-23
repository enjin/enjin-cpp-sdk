#include "enjinsdk/models/Asset.hpp"

#include "EnumUtils.hpp"
#include "RapidJsonUtils.hpp"

namespace enjin::sdk::models {

void Asset::deserialize(const std::string& json) {
    rapidjson::Document document;
    document.Parse(json.c_str());
    if (document.IsObject()) {
        if (document.HasMember(ID_KEY) && document[ID_KEY].IsString()) {
            id.emplace(document[ID_KEY].GetString());
        }
        if (document.HasMember(NAME_KEY) && document[NAME_KEY].IsString()) {
            name.emplace(document[NAME_KEY].GetString());
        }
        if (document.HasMember(STATE_DATA_KEY) && document[STATE_DATA_KEY].IsObject()) {
            state_data.emplace(utils::get_object_as_type<AssetStateData>(document, STATE_DATA_KEY));
        }
        if (document.HasMember(CONFIG_DATA_KEY) && document[CONFIG_DATA_KEY].IsObject()) {
            config_data.emplace(utils::get_object_as_type<AssetConfigData>(document, CONFIG_DATA_KEY));
        }
        if (document.HasMember(VARIANT_MODE_KEY) && document[VARIANT_MODE_KEY].IsString()) {
            variant_mode.emplace(utils::deserialize_asset_variant_mode(document[VARIANT_MODE_KEY].GetString()));
        }
        if (document.HasMember(VARIANTS_KEY) && document[VARIANTS_KEY].IsArray()) {
            variants.emplace(utils::get_array_as_type_vector<AssetVariant>(document, VARIANTS_KEY));
        }
        if (document.HasMember(CREATED_AT_KEY) && document[CREATED_AT_KEY].IsString()) {
            created_at.emplace(document[CREATED_AT_KEY].GetString());
        }
        if (document.HasMember(UPDATED_AT_KEY) && document[UPDATED_AT_KEY].IsString()) {
            updated_at.emplace(document[UPDATED_AT_KEY].GetString());
        }
    }
}

const std::optional<std::string>& Asset::get_id() const {
    return id;
}

const std::optional<std::string>& Asset::get_name() const {
    return name;
}

const std::optional<AssetStateData>& Asset::get_state_data() const {
    return state_data;
}

const std::optional<AssetConfigData>& Asset::get_config_data() const {
    return config_data;
}

const std::optional<AssetVariantMode>& Asset::get_variant_mode() const {
    return variant_mode;
}

const std::optional<std::vector<AssetVariant>>& Asset::get_variants() const {
    return variants;
}

const std::optional<std::string>& Asset::get_created_at() const {
    return created_at;
}

const std::optional<std::string>& Asset::get_updated_at() const {
    return updated_at;
}

bool Asset::operator==(const Asset& rhs) const {
    return id == rhs.id &&
           name == rhs.name &&
           state_data == rhs.state_data &&
           config_data == rhs.config_data &&
           variant_mode == rhs.variant_mode &&
           variants == rhs.variants &&
           created_at == rhs.created_at &&
           updated_at == rhs.updated_at;
}

bool Asset::operator!=(const Asset& rhs) const {
    return !(rhs == *this);
}

}
