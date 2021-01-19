#include "enjinsdk/models/PlayerFilter.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::models {

std::string PlayerFilter::serialize() {
    rapidjson::Document document(rapidjson::kObjectType);
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

    if (and_filters.has_value()) {
        utils::set_array_member_from_type_vector<PlayerFilter>(document, AND_KEY, and_filters.value());
    }
    if (or_filters.has_value()) {
        utils::set_array_member_from_type_vector<PlayerFilter>(document, OR_KEY, or_filters.value());
    }
    if (id.has_value()) {
        utils::set_string_member(document, ID_KEY, id.value());
    }
    if (id_in.has_value()) {
        utils::set_array_member_from_string_vector(document, ID_IN_KEY, id_in.value());
    }

    return utils::document_to_string(document);
}

PlayerFilter& PlayerFilter::set_and(const std::vector<PlayerFilter>& others) {
    and_filters = others;
    return *this;
}

PlayerFilter& PlayerFilter::set_or(const std::vector<PlayerFilter>& others) {
    or_filters = others;
    return *this;
}

PlayerFilter& PlayerFilter::set_id(const std::string& id) {
    PlayerFilter::id = id;
    return *this;
}

PlayerFilter& PlayerFilter::set_id_in(const std::vector<std::string>& ids) {
    id_in = ids;
    return *this;
}

bool PlayerFilter::operator==(const PlayerFilter& rhs) const {
    return and_filters == rhs.and_filters &&
           or_filters == rhs.or_filters &&
           id == rhs.id &&
           id_in == rhs.id_in;
}

bool PlayerFilter::operator!=(const PlayerFilter& rhs) const {
    return !(rhs == *this);
}

}
