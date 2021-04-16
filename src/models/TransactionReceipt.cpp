/* Copyright 2021 Enjin Pte Ltd.
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

#include "enjinsdk/models/TransactionReceipt.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::models {

void TransactionReceipt::deserialize(const std::string& json) {
    rapidjson::Document document;
    document.Parse(json.c_str());
    if (document.IsObject()) {
        if (document.HasMember(BLOCK_HASH_KEY) && document[BLOCK_HASH_KEY].IsString()) {
            block_hash.emplace(document[BLOCK_HASH_KEY].GetString());
        }
        if (document.HasMember(BLOCK_NUMBER_KEY) && document[BLOCK_NUMBER_KEY].IsInt()) {
            block_number.emplace(document[BLOCK_NUMBER_KEY].GetInt());
        }
        if (document.HasMember(CUMULATIVE_GAS_USED_KEY) && document[CUMULATIVE_GAS_USED_KEY].IsInt()) {
            cumulative_gas_used.emplace(document[CUMULATIVE_GAS_USED_KEY].GetInt());
        }
        if (document.HasMember(GAS_USED_KEY) && document[GAS_USED_KEY].IsInt()) {
            gas_used.emplace(document[GAS_USED_KEY].GetInt());
        }
        if (document.HasMember(FROM_KEY) && document[FROM_KEY].IsString()) {
            from.emplace(document[FROM_KEY].GetString());
        }
        if (document.HasMember(TO_KEY) && document[TO_KEY].IsString()) {
            to.emplace(document[TO_KEY].GetString());
        }
        if (document.HasMember(TRANSACTION_HASH_KEY) && document[TRANSACTION_HASH_KEY].IsString()) {
            transaction_hash.emplace(document[TRANSACTION_HASH_KEY].GetString());
        }
        if (document.HasMember(TRANSACTION_INDEX_KEY) && document[TRANSACTION_INDEX_KEY].IsInt()) {
            transaction_index.emplace(document[TRANSACTION_INDEX_KEY].GetInt());
        }
        if (document.HasMember(STATUS_KEY) && document[STATUS_KEY].IsBool()) {
            status.emplace(document[STATUS_KEY].GetBool());
        }
        if (document.HasMember(LOGS_KEY) && document[LOGS_KEY].IsArray()) {
            logs.emplace(utils::get_array_as_type_vector<TransactionLog>(document, LOGS_KEY));
        }
    }
}

const std::optional<std::string>& TransactionReceipt::get_block_hash() const {
    return block_hash;
}

const std::optional<int>& TransactionReceipt::get_block_number() const {
    return block_number;
}

const std::optional<int>& TransactionReceipt::get_cumulative_gas_used() const {
    return cumulative_gas_used;
}

const std::optional<int>& TransactionReceipt::get_gas_used() const {
    return gas_used;
}

const std::optional<std::string>& TransactionReceipt::get_from() const {
    return from;
}

const std::optional<std::string>& TransactionReceipt::get_to() const {
    return to;
}

const std::optional<std::string>& TransactionReceipt::get_transaction_hash() const {
    return transaction_hash;
}

const std::optional<int>& TransactionReceipt::get_transaction_index() const {
    return transaction_index;
}

const std::optional<bool>& TransactionReceipt::get_status() const {
    return status;
}

const std::optional<std::vector<TransactionLog>>& TransactionReceipt::get_logs() const {
    return logs;
}

bool TransactionReceipt::operator==(const TransactionReceipt& rhs) const {
    return block_hash == rhs.block_hash &&
           block_number == rhs.block_number &&
           cumulative_gas_used == rhs.cumulative_gas_used &&
           gas_used == rhs.gas_used &&
           from == rhs.from &&
           to == rhs.to &&
           transaction_hash == rhs.transaction_hash &&
           transaction_index == rhs.transaction_index &&
           status == rhs.status &&
           logs == rhs.logs;
}

bool TransactionReceipt::operator!=(const TransactionReceipt& rhs) const {
    return !(rhs == *this);
}

}
