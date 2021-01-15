#include "enjinsdk/models/TransactionLog.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::models {

void TransactionLog::deserialize(const std::string& json) {
    rapidjson::Document document;
    document.Parse(json.c_str());
    if (document.IsObject()) {
        if (document.HasMember(BLOCK_NUMBER_KEY) && document[BLOCK_NUMBER_KEY].IsInt()) {
            block_number.emplace(document[BLOCK_NUMBER_KEY].GetInt());
        }
        if (document.HasMember(ADDRESS_KEY) && document[ADDRESS_KEY].IsString()) {
            address.emplace(document[ADDRESS_KEY].GetString());
        }
        if (document.HasMember(TRANSACTION_HASH_KEY) && document[TRANSACTION_HASH_KEY].IsString()) {
            transaction_hash.emplace(document[TRANSACTION_HASH_KEY].GetString());
        }
        if (document.HasMember(DATA_KEY) && document[DATA_KEY].IsArray()) {
            data.emplace(utils::get_array_as_serialized_vector(document, DATA_KEY));
        }
        if (document.HasMember(TOPICS_KEY) && document[TOPICS_KEY].IsArray()) {
            topics.emplace(utils::get_array_as_serialized_vector(document, TOPICS_KEY));
        }
        if (document.HasMember(EVENT_KEY) && document[EVENT_KEY].IsObject()) {
            event.emplace(utils::get_object_as_type<TransactionEvent>(document, EVENT_KEY));
        }
    }
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

const std::optional<std::vector<std::string>>& TransactionLog::get_data() const {
    return data;
}

const std::optional<std::vector<std::string>>& TransactionLog::get_topics() const {
    return topics;
}

const std::optional<TransactionEvent>& TransactionLog::get_event() const {
    return event;
}

bool TransactionLog::operator==(const TransactionLog& rhs) const {
    return block_number == rhs.block_number &&
           address == rhs.address &&
           transaction_hash == rhs.transaction_hash &&
           data == rhs.data &&
           topics == rhs.topics &&
           event == rhs.event;
}

bool TransactionLog::operator!=(const TransactionLog& rhs) const {
    return !(rhs == *this);
}

}
