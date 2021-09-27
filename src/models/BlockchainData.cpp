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

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::models {

void enjin::sdk::models::BlockchainData::deserialize(const std::string& json) {
    rapidjson::Document document;
    document.Parse(json.c_str());
    if (document.IsObject()) {
        if (document.HasMember(ENCODED_DATA_KEY) && document[ENCODED_DATA_KEY].IsString()) {
            encoded_data.emplace(document[ENCODED_DATA_KEY].GetString());
        }
        if (document.HasMember(SIGNED_TRANSACTION_KEY) && document[SIGNED_TRANSACTION_KEY].IsString()) {
            signed_transaction.emplace(document[SIGNED_TRANSACTION_KEY].GetString());
        }
        if (document.HasMember(SIGNED_BACKUP_TRANSACTION_KEY) && document[SIGNED_BACKUP_TRANSACTION_KEY].IsString()) {
            signed_backup_transaction.emplace(document[SIGNED_BACKUP_TRANSACTION_KEY].GetString());
        }
        if (document.HasMember(SIGNED_CANCEL_TRANSACTION_KEY) && document[SIGNED_CANCEL_TRANSACTION_KEY].IsString()) {
            signed_cancel_transaction.emplace(document[SIGNED_CANCEL_TRANSACTION_KEY].GetString());
        }
        if (document.HasMember(RECEIPT_KEY) && document[RECEIPT_KEY].IsObject()) {
            receipt.emplace(utils::get_object_as_type<TransactionReceipt>(document, RECEIPT_KEY));
        }
        if (document.HasMember(ERROR_KEY) && document[ERROR_KEY].IsString()) {
            error.emplace(document[ERROR_KEY].GetString());
        }
        if (document.HasMember(NONCE_KEY) && document[NONCE_KEY].IsString()) {
            nonce.emplace(document[NONCE_KEY].GetString());
        }
    }
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
    return encoded_data == rhs.encoded_data &&
           signed_transaction == rhs.signed_transaction &&
           signed_backup_transaction == rhs.signed_backup_transaction &&
           signed_cancel_transaction == rhs.signed_cancel_transaction &&
           receipt == rhs.receipt &&
           error == rhs.error &&
           nonce == rhs.nonce;
}

bool BlockchainData::operator!=(const BlockchainData& rhs) const {
    return !(rhs == *this);
}

}
