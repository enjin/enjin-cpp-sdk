#include "enjinsdk/models/TokenFilter.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::models {

std::string TokenFilter::serialize() {
    rapidjson::Document document(rapidjson::kObjectType);
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

    if (and_filters.has_value()) {
        utils::set_array_member_from_type_vector<TokenFilter>(document, AND_KEY, and_filters.value());
    }
    if (or_filters.has_value()) {
        utils::set_array_member_from_type_vector<TokenFilter>(document, OR_KEY, or_filters.value());
    }
    if (id.has_value()) {
        utils::set_string_member(document, ID_KEY, id.value());
    }
    if (id_in.has_value()) {
        utils::set_array_member_from_string_vector(document, ID_IN_KEY, id_in.value());
    }
    if (name.has_value()) {
        utils::set_string_member(document, NAME_KEY, name.value());
    }
    if (name_contains.has_value()) {
        utils::set_string_member(document, NAME_CONTAINS_KEY, name_contains.value());
    }
    if (name_in.has_value()) {
        utils::set_array_member_from_string_vector(document, NAME_IN_KEY, name_in.value());
    }
    if (name_starts_with.has_value()) {
        utils::set_string_member(document, NAME_STARTS_WITH_KEY, name_starts_with.value());
    }
    if (name_ends_with.has_value()) {
        utils::set_string_member(document, NAME_ENDS_WITH_KEY, name_ends_with.value());
    }
    if (wallet.has_value()) {
        utils::set_string_member(document, WALLET_KEY, wallet.value());
    }
    if (wallet_in.has_value()) {
        utils::set_array_member_from_string_vector(document, WALLET_IN_KEY, wallet_in.value());
    }

    return utils::document_to_string(document);
}

TokenFilter& TokenFilter::set_and(const std::vector<TokenFilter>& others) {
    and_filters = others;
    return *this;
}

TokenFilter& TokenFilter::set_or(const std::vector<TokenFilter>& others) {
    or_filters = others;
    return *this;
}

TokenFilter& TokenFilter::set_id(const std::string& id) {
    TokenFilter::id = id;
    return *this;
}

TokenFilter& TokenFilter::set_id_in(const std::vector<std::string>& ids) {
    id_in = ids;
    return *this;
}

TokenFilter& TokenFilter::set_name(const std::string& name) {
    TokenFilter::name = name;
    return *this;
}

TokenFilter& TokenFilter::set_name_contains(const std::string& text) {
    name_contains = text;
    return *this;
}

TokenFilter& TokenFilter::set_name_in(const std::vector<std::string>& names) {
    name_in = names;
    return *this;
}

TokenFilter& TokenFilter::set_name_starts_with(const std::string& prefix) {
    name_starts_with = prefix;
    return *this;
}

TokenFilter& TokenFilter::set_name_ends_with(const std::string& suffix) {
    name_ends_with = suffix;
    return *this;
}

TokenFilter& TokenFilter::set_wallet(const std::string& wallet) {
    TokenFilter::wallet = wallet;
    return *this;
}

TokenFilter& TokenFilter::set_wallet_in(const std::vector<std::string>& wallets) {
    wallet_in = wallets;
    return *this;
}

bool TokenFilter::operator==(const TokenFilter& rhs) const {
    return and_filters == rhs.and_filters &&
           or_filters == rhs.or_filters &&
           id == rhs.id &&
           id_in == rhs.id_in &&
           name == rhs.name &&
           name_contains == rhs.name_contains &&
           name_in == rhs.name_in &&
           name_starts_with == rhs.name_starts_with &&
           name_ends_with == rhs.name_ends_with &&
           wallet == rhs.wallet &&
           wallet_in == rhs.wallet_in;
}

bool TokenFilter::operator!=(const TokenFilter& rhs) const {
    return !(rhs == *this);
}

}
