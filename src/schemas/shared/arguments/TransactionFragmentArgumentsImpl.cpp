#include "enjinsdk/internal/TransactionFragmentArgumentsImpl.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::shared {

std::string TransactionFragmentArgumentsImpl::serialize() {
    rapidjson::Document document(rapidjson::kObjectType);

    if (with_blockchain_data.has_value()) {
        utils::set_boolean_member(document, "withBlockchainData", with_blockchain_data.value());
    }
    if (with_meta.has_value()) {
        utils::set_boolean_member(document, "withMeta", with_meta.value());
    }
    if (with_encoded_data.has_value()) {
        utils::set_boolean_member(document, "withEncodedData", with_encoded_data.value());
    }
    if (with_asset_data.has_value()) {
        utils::set_boolean_member(document, "withAssetData", with_asset_data.value());
    }
    if (with_signed_txs.has_value()) {
        utils::set_boolean_member(document, "withSignedTxs", with_signed_txs.value());
    }
    if (with_error.has_value()) {
        utils::set_boolean_member(document, "withError", with_error.value());
    }
    if (with_nonce.has_value()) {
        utils::set_boolean_member(document, "withNonce", with_nonce.value());
    }
    if (with_state.has_value()) {
        utils::set_boolean_member(document, "withState", with_state.value());
    }
    if (with_receipt.has_value()) {
        utils::set_boolean_member(document, "withReceipt", with_receipt.value());
    }
    if (with_receipt_logs.has_value()) {
        utils::set_boolean_member(document, "withReceiptLogs", with_receipt_logs.value());
    }
    if (with_log_event.has_value()) {
        utils::set_boolean_member(document, "withLogEvent", with_log_event.value());
    }

    return utils::document_to_string(document);
}

void TransactionFragmentArgumentsImpl::set_with_blockchain_data() {
    with_blockchain_data = true;
}

void TransactionFragmentArgumentsImpl::set_with_meta() {
    with_meta = true;
}

void TransactionFragmentArgumentsImpl::set_with_encoded_data() {
    with_encoded_data = true;
}

void TransactionFragmentArgumentsImpl::set_with_asset_data() {
    with_asset_data = true;
}

void TransactionFragmentArgumentsImpl::set_with_signed_txs() {
    with_signed_txs = true;
}

void TransactionFragmentArgumentsImpl::set_with_error() {
    with_error = true;
}

void TransactionFragmentArgumentsImpl::set_with_nonce() {
    with_nonce = true;
}

void TransactionFragmentArgumentsImpl::set_with_state() {
    with_state = true;
}

void TransactionFragmentArgumentsImpl::set_with_receipt() {
    with_receipt = true;
}

void TransactionFragmentArgumentsImpl::set_with_receipt_logs() {
    with_receipt_logs = true;
}

void TransactionFragmentArgumentsImpl::set_with_log_event() {
    with_log_event = true;
}

bool TransactionFragmentArgumentsImpl::operator==(const TransactionFragmentArgumentsImpl& rhs) const {
    return with_blockchain_data == rhs.with_blockchain_data &&
           with_meta == rhs.with_meta &&
           with_encoded_data == rhs.with_encoded_data &&
           with_asset_data == rhs.with_asset_data &&
           with_signed_txs == rhs.with_signed_txs &&
           with_error == rhs.with_error &&
           with_nonce == rhs.with_nonce &&
           with_state == rhs.with_state &&
           with_receipt == rhs.with_receipt &&
           with_receipt_logs == rhs.with_receipt_logs &&
           with_log_event == rhs.with_log_event;
}

bool TransactionFragmentArgumentsImpl::operator!=(const TransactionFragmentArgumentsImpl& rhs) const {
    return !(rhs == *this);
}

}