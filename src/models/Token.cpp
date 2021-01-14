#include "enjinsdk/models/Token.hpp"

#include "EnumUtils.hpp"
#include "RapidJsonUtils.hpp"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

namespace enjin::sdk::models {

void Token::deserialize(const std::string& json) {
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
            TokenStateData v;
            v.deserialize(utils::get_object_as_string(document, STATE_DATA_KEY));
            state_data.emplace(v);
        }
        if (document.HasMember(CONFIG_DATA_KEY) && document[CONFIG_DATA_KEY].IsObject()) {
            TokenConfigData v;
            v.deserialize(utils::get_object_as_string(document, CONFIG_DATA_KEY));
            config_data.emplace(v);
        }
        if (document.HasMember(VARIANT_MODE_KEY) && document[VARIANT_MODE_KEY].IsString()) {
            variant_mode.emplace(utils::deserialize_token_variant_mode(document[VARIANT_MODE_KEY].GetString()));
        }
        if (document.HasMember(VARIANTS_KEY) && document[VARIANTS_KEY].IsArray()) {
            std::vector<TokenVariant> v;
            for (auto& arr_el : document[VARIANTS_KEY].GetArray()) {
                TokenVariant v_el;
                rapidjson::StringBuffer buffer;
                rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
                arr_el.Accept(writer);

                v_el.deserialize(buffer.GetString());
                v.push_back(v_el);
            }
            variants.emplace(v);
        }
        if (document.HasMember(CREATED_AT_KEY) && document[CREATED_AT_KEY].IsString()) {
            created_at.emplace(document[CREATED_AT_KEY].GetString());
        }
        if (document.HasMember(UPDATED_AT_KEY) && document[UPDATED_AT_KEY].IsString()) {
            updated_at.emplace(document[UPDATED_AT_KEY].GetString());
        }
    }
}

const std::optional<std::string>& Token::get_id() const {
    return id;
}

const std::optional<std::string>& Token::get_name() const {
    return name;
}

const std::optional<TokenStateData>& Token::get_state_data() const {
    return state_data;
}

const std::optional<TokenConfigData>& Token::get_config_data() const {
    return config_data;
}

const std::optional<TokenVariantMode>& Token::get_variant_mode() const {
    return variant_mode;
}

const std::optional<std::vector<TokenVariant>>& Token::get_variants() const {
    return variants;
}

const std::optional<std::string>& Token::get_created_at() const {
    return created_at;
}

const std::optional<std::string>& Token::get_updated_at() const {
    return updated_at;
}

bool Token::operator==(const Token& rhs) const {
    return id == rhs.id &&
           name == rhs.name &&
           state_data == rhs.state_data &&
           config_data == rhs.config_data &&
           variant_mode == rhs.variant_mode &&
           variants == rhs.variants &&
           created_at == rhs.created_at &&
           updated_at == rhs.updated_at;
}

bool Token::operator!=(const Token& rhs) const {
    return !(rhs == *this);
}

}
