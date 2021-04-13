#include "enjinsdk/internal/PlayerFragmentArgumentsImpl.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::shared {

std::string PlayerFragmentArgumentsImpl::serialize() const {
    rapidjson::Document document(rapidjson::kObjectType);

    if (with_linking_info.has_value()) {
        utils::set_boolean_member(document, "withLinkingInfo", with_linking_info.value());
    }
    if (qr_size.has_value()) {
        utils::set_integer_member(document, "linkingCodeQrSize", qr_size.value());
    }
    if (with_wallet.has_value()) {
        utils::set_boolean_member(document, "withPlayerWallet", with_wallet.value());
    }

    return utils::document_to_string(document);
}

void PlayerFragmentArgumentsImpl::set_with_linking_info() {
    with_linking_info = true;
}

void PlayerFragmentArgumentsImpl::set_qr_size(int size) {
    qr_size = size;
}

void PlayerFragmentArgumentsImpl::set_with_wallet() {
    with_wallet = true;
}

bool PlayerFragmentArgumentsImpl::operator==(const PlayerFragmentArgumentsImpl& rhs) const {
    return with_linking_info == rhs.with_linking_info &&
           qr_size == rhs.qr_size &&
           with_wallet == rhs.with_wallet;
}

bool PlayerFragmentArgumentsImpl::operator!=(const PlayerFragmentArgumentsImpl& rhs) const {
    return !(rhs == *this);
}

}
