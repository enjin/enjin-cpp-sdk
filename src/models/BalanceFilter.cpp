#include "enjinsdk/models/BalanceFilter.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::models {

std::string BalanceFilter::serialize() {
    rapidjson::Document document(rapidjson::kObjectType);

    if (and_filters.has_value()) {
        utils::set_array_member_from_type_vector<BalanceFilter>(document, AND_KEY, and_filters.value());
    }
    if (or_filters.has_value()) {
        utils::set_array_member_from_type_vector<BalanceFilter>(document, OR_KEY, or_filters.value());
    }
    if (token_id.has_value()) {
        utils::set_string_member(document, TOKEN_ID_KEY, token_id.value());
    }
    if (token_id_in.has_value()) {
        utils::set_array_member_from_string_vector(document, TOKEN_ID_IN_KEY, token_id_in.value());
    }
    if (wallet.has_value()) {
        utils::set_string_member(document, WALLET_KEY, wallet.value());
    }
    if (wallet_in.has_value()) {
        utils::set_array_member_from_string_vector(document, WALLET_IN_KEY, wallet_in.value());
    }
    if (value.has_value()) {
        utils::set_integer_member(document, VALUE_KEY, value.value());
    }
    if (value_gt.has_value()) {
        utils::set_integer_member(document, VALUE_GT_KEY, value_gt.value());
    }
    if (value_gte.has_value()) {
        utils::set_integer_member(document, VALUE_GTE_KEY, value_gte.value());
    }
    if (value_lt.has_value()) {
        utils::set_integer_member(document, VALUE_LT_KEY, value_lt.value());
    }
    if (value_lte.has_value()) {
        utils::set_integer_member(document, VALUE_LTE_KEY, value_lte.value());
    }

    return utils::document_to_string(document);
}

BalanceFilter& BalanceFilter::set_and(const std::vector<BalanceFilter>& others) {
    and_filters = others;
    return *this;
}

BalanceFilter& BalanceFilter::set_or(const std::vector<BalanceFilter>& others) {
    or_filters = others;
    return *this;
}

BalanceFilter& BalanceFilter::set_token_id(const std::string& token_id) {
    BalanceFilter::token_id = token_id;
    return *this;
}

BalanceFilter& BalanceFilter::set_token_id_in(const std::vector<std::string>& token_ids) {
    token_id_in = token_ids;
    return *this;
}

BalanceFilter& BalanceFilter::set_wallet(const std::string& wallet) {
    BalanceFilter::wallet = wallet;
    return *this;
}

BalanceFilter& BalanceFilter::set_wallet_in(const std::vector<std::string>& wallets) {
    wallet_in = wallets;
    return *this;
}

BalanceFilter& BalanceFilter::set_value(int value) {
    BalanceFilter::value = value;
    return *this;
}

BalanceFilter& BalanceFilter::set_value_greater_than(int value) {
    value_gt = value;
    return *this;
}

BalanceFilter& BalanceFilter::set_value_greater_than_or_equal(int value) {
    value_gte = value;
    return *this;
}

BalanceFilter& BalanceFilter::set_value_less_than(int value) {
    value_lt = value;
    return *this;
}

BalanceFilter& BalanceFilter::set_value_less_than_or_equal(int value) {
    value_lte = value;
    return *this;
}

bool BalanceFilter::operator==(const BalanceFilter& rhs) const {
    return and_filters == rhs.and_filters &&
           or_filters == rhs.or_filters &&
           token_id == rhs.token_id &&
           token_id_in == rhs.token_id_in &&
           wallet == rhs.wallet &&
           wallet_in == rhs.wallet_in &&
           value == rhs.value &&
           value_gt == rhs.value_gt &&
           value_gte == rhs.value_gte &&
           value_lt == rhs.value_lt &&
           value_lte == rhs.value_lte;
}

bool BalanceFilter::operator!=(const BalanceFilter& rhs) const {
    return !(rhs == *this);
}

}
