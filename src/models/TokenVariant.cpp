#include "enjinsdk/models/TokenVariant.hpp"

#include "rapidjson/document.h"

namespace enjin::sdk::models {

void TokenVariant::deserialize(const std::string& json) {
    rapidjson::Document document;
    document.Parse(json.c_str());
    if (document.IsObject()) {
        if (document.HasMember(ID_KEY) && document[ID_KEY].IsInt()) {
            id.emplace(document[ID_KEY].GetInt());
        }
        if (document.HasMember(TOKEN_ID_KEY) && document[TOKEN_ID_KEY].IsString()) {
            token_id.emplace(document[TOKEN_ID_KEY].GetString());
        }
        if (document.HasMember(VARIANT_METADATA_KEY) && document[VARIANT_METADATA_KEY].IsString()) {
            variant_metadata.emplace(document[VARIANT_METADATA_KEY].GetString());
        }
        if (document.HasMember(USAGE_COUNT_KEY) && document[USAGE_COUNT_KEY].IsInt()) {
            usage_count.emplace(document[USAGE_COUNT_KEY].GetInt());
        }
        if (document.HasMember(CREATED_AT_KEY) && document[CREATED_AT_KEY].IsString()) {
            created_at.emplace(document[CREATED_AT_KEY].GetString());
        }
        if (document.HasMember(UPDATED_AT_KEY) && document[UPDATED_AT_KEY].IsString()) {
            updated_at.emplace(document[UPDATED_AT_KEY].GetString());
        }
    }
}

const std::optional<int>& TokenVariant::get_id() const {
    return id;
}

const std::optional<std::string>& TokenVariant::get_token_id() const {
    return token_id;
}

const std::optional<std::string>& TokenVariant::get_variant_metadata() const {
    return variant_metadata;
}

const std::optional<int>& TokenVariant::get_usage_count() const {
    return usage_count;
}

const std::optional<std::string>& TokenVariant::get_created_at() const {
    return created_at;
}

const std::optional<std::string>& TokenVariant::get_updated_at() const {
    return updated_at;
}

bool TokenVariant::operator==(const TokenVariant& rhs) const {
    return id == rhs.id &&
           token_id == rhs.token_id &&
           variant_metadata == rhs.variant_metadata &&
           usage_count == rhs.usage_count &&
           created_at == rhs.created_at &&
           updated_at == rhs.updated_at;
}

bool TokenVariant::operator!=(const TokenVariant& rhs) const {
    return !(rhs == *this);
}

}
