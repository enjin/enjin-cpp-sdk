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

#include "enjinsdk/models/TransactionLog.hpp"

#include "enjinsdk/JsonUtils.hpp"
#include "enjinsdk/JsonValue.hpp"

using namespace enjin::sdk::json;
using namespace enjin::sdk::models;
using namespace enjin::sdk::utils;

void TransactionLog::deserialize(const std::string& json) {
    JsonValue json_object;

    if (!json_object.try_parse_as_object(json)) {
        block_number.reset();
        address.reset();
        transaction_hash.reset();
        data.reset();
        topics.reset();
        event.reset();

        return;
    }

    JsonUtils::try_get_field(json_object, "blockNumber", block_number);
    JsonUtils::try_get_field(json_object, "address", address);
    JsonUtils::try_get_field(json_object, "transactionHash", transaction_hash);
    JsonUtils::try_get_field(json_object, "data", data);
    JsonUtils::try_get_field(json_object, "topics", topics);
    JsonUtils::try_get_field(json_object, "event", event);
}

const std::optional<int>& TransactionLog::get_block_number() const {
    return block_number;
}

const std::optional<std::string>& TransactionLog::get_address() const {
    return address;
}

const std::optional<std::string>& TransactionLog::get_transaction_hash() const {
    return transaction_hash;
}

const std::optional<std::vector<JsonValue>>& TransactionLog::get_data() const {
    return data;
}

const std::optional<std::vector<JsonValue>>& TransactionLog::get_topics() const {
    return topics;
}

const std::optional<TransactionEvent>& TransactionLog::get_event() const {
    return event;
}

bool TransactionLog::operator==(const TransactionLog& rhs) const {
    return block_number == rhs.block_number
           && address == rhs.address
           && transaction_hash == rhs.transaction_hash
           && data == rhs.data
           && topics == rhs.topics
           && event == rhs.event;
}

bool TransactionLog::operator!=(const TransactionLog& rhs) const {
    return !(*this == rhs);
}
