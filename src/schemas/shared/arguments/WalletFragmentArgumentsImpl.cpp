#include "enjinsdk/internal/WalletFragmentArgumentsImpl.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::shared {

std::string WalletFragmentArgumentsImpl::serialize() const {
    rapidjson::Document document(rapidjson::kObjectType);

    if (with_assets_created.has_value()) {
        utils::set_boolean_member(document, "withAssetsCreated", with_assets_created.value());
    }

    return utils::document_to_string(document);
}

void WalletFragmentArgumentsImpl::set_with_assets_created() {
    with_assets_created = true;
}

bool WalletFragmentArgumentsImpl::operator==(const WalletFragmentArgumentsImpl& rhs) const {
    return with_assets_created == rhs.with_assets_created;
}

bool WalletFragmentArgumentsImpl::operator!=(const WalletFragmentArgumentsImpl& rhs) const {
    return !(rhs == *this);
}

}
