#include "enjinsdk/internal/WalletFragmentArguments.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::shared {

std::string WalletFragmentArguments::serialize() {
    rapidjson::Document document(rapidjson::kObjectType);

    if (with_assets_created.has_value()) {
        utils::set_boolean_member(document, "withAssetsCreated", with_assets_created.value());
    }

    return utils::document_to_string(document);
}

void WalletFragmentArguments::set_with_assets_created() {
    with_assets_created = true;
}

bool WalletFragmentArguments::operator==(const WalletFragmentArguments& rhs) const {
    return with_assets_created == rhs.with_assets_created;
}

bool WalletFragmentArguments::operator!=(const WalletFragmentArguments& rhs) const {
    return !(rhs == *this);
}

}
