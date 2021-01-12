#include "enjinsdk/models/Token.hpp"
#include "rapidjson/document.h"

namespace enjin::sdk::models {

void Token::deserialize(const std::string& json) {
    rapidjson::Document document;
    document.Parse(json.c_str());
    if (document.IsObject()) {

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

}
