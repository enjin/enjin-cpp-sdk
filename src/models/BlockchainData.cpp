/* Copyright 2021 Enjin Pte. Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "enjinsdk/models/BlockchainData.hpp"

#include "enjinsdk/JsonUtils.hpp"
#include "enjinsdk/JsonValue.hpp"

using namespace enjin::sdk::json;
using namespace enjin::sdk::models;
using namespace enjin::sdk::utils;

void enjin::sdk::models::BlockchainData::deserialize(const std::string& json) {
    JsonValue json_object;

    if (!json_object.try_parse_as_object(json)) {
        encoded_data.reset();
        signed_transaction.reset();
        signed_backup_transaction.reset();
        signed_cancel_transaction.reset();
        receipt.reset();
        error.reset();
        nonce.reset();

        return;
    }

    JsonUtils::try_get_field(json_object, "encodedData", encoded_data);
    JsonUtils::try_get_field(json_object, "signedTransaction", signed_transaction);
    JsonUtils::try_get_field(json_object, "signedBackupTransaction", signed_backup_transaction);
    JsonUtils::try_get_field(json_object, "signedCancelTransaction", signed_cancel_transaction);
    JsonUtils::try_get_field(json_object, "receipt", receipt);
    JsonUtils::try_get_field(json_object, "error", error);
    JsonUtils::try_get_field(json_object, "nonce", nonce);
}

const std::optional<std::string>& BlockchainData::get_encoded_data() const {
    return encoded_data;
}

const std::optional<std::string>& BlockchainData::get_signed_transaction() const {
    return signed_transaction;
}

const std::optional<std::string>& BlockchainData::get_signed_backup_transaction() const {
    return signed_backup_transaction;
}

const std::optional<std::string>& BlockchainData::get_signed_cancel_transaction() const {
    return signed_cancel_transaction;
}

const std::optional<TransactionReceipt>& BlockchainData::get_receipt() const {
    return receipt;
}

const std::optional<std::string>& BlockchainData::get_error() const {
    return error;
}

const std::optional<std::string>& BlockchainData::get_nonce() const {
    return nonce;
}

bool BlockchainData::operator==(const BlockchainData& rhs) const {
    return encoded_data == rhs.encoded_data
           && signed_transaction == rhs.signed_transaction
           && signed_backup_transaction == rhs.signed_backup_transaction
           && signed_cancel_transaction == rhs.signed_cancel_transaction
           && receipt == rhs.receipt
           && error == rhs.error
           && nonce == rhs.nonce;
}

bool BlockchainData::operator!=(const BlockchainData& rhs) const {
    return !(*this == rhs);
}
