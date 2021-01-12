#include "enjinsdk/models/TokenVariant.hpp"

namespace enjin::sdk::models {

void TokenVariant::deserialize(const std::string& json) {

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

}
