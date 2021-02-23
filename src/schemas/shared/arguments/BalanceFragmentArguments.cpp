#include "enjinsdk/internal/BalanceFragmentArguments.hpp"

#include "EnumUtils.hpp"
#include "RapidJsonUtils.hpp"

namespace enjin::sdk::shared {

std::string BalanceFragmentArguments::serialize() {
    rapidjson::Document document(rapidjson::kObjectType);

    if (bal_id_format.has_value()) {
        utils::set_string_member(document,
                                 "balIdFormat",
                                 utils::serialize_asset_id_format(bal_id_format.value()));
    }
    if (bal_index_format.has_value()) {
        utils::set_string_member(document,
                                 "balIndexFormat",
                                 utils::serialize_asset_index_format(bal_index_format.value()));
    }
    if (with_bal_project_id.has_value()) {
        utils::set_boolean_member(document, "withBalAppId", with_bal_project_id.value());
    }
    if (with_bal_wallet_address.has_value()) {
        utils::set_boolean_member(document, "withBalWalletAddress", with_bal_wallet_address.value());
    }

    return utils::document_to_string(document);
}

void BalanceFragmentArguments::set_bal_id_format(models::AssetIdFormat bal_id_format) {
    BalanceFragmentArguments::bal_id_format = bal_id_format;
}

void BalanceFragmentArguments::set_bal_index_format(models::AssetIndexFormat bal_index_format) {
    BalanceFragmentArguments::bal_index_format = bal_index_format;
}

void BalanceFragmentArguments::set_with_bal_project_id() {
    with_bal_project_id = true;
}

void BalanceFragmentArguments::set_with_bal_wallet_address() {
    with_bal_wallet_address = true;
}

bool BalanceFragmentArguments::operator==(const BalanceFragmentArguments& rhs) const {
    return bal_id_format == rhs.bal_id_format &&
           bal_index_format == rhs.bal_index_format &&
           with_bal_project_id == rhs.with_bal_project_id &&
           with_bal_wallet_address == rhs.with_bal_wallet_address;
}

bool BalanceFragmentArguments::operator!=(const BalanceFragmentArguments& rhs) const {
    return !(rhs == *this);
}

}
