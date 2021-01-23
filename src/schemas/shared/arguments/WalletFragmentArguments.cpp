#include "enjinsdk/internal/WalletFragmentArguments.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::shared {

std::string WalletFragmentArguments::serialize() {
    rapidjson::Document document(rapidjson::kObjectType);

    if (with_tokens_created.has_value()) {
        utils::set_boolean_member(document, "withTokensCreated", with_tokens_created.value());
    }

    return utils::document_to_string(document);
}

void WalletFragmentArguments::set_with_tokens_created() {
    with_tokens_created = true;
}

bool WalletFragmentArguments::operator==(const WalletFragmentArguments& rhs) const {
    return with_tokens_created == rhs.with_tokens_created;
}

bool WalletFragmentArguments::operator!=(const WalletFragmentArguments& rhs) const {
    return !(rhs == *this);
}

}
