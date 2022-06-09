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

#ifndef ENJINCPPSDK_TRANSACTIONLOG_HPP
#define ENJINCPPSDK_TRANSACTIONLOG_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/IDeserializable.hpp"
#include "enjinsdk/JsonValue.hpp"
#include "enjinsdk/models/TransactionEvent.hpp"
#include <optional>
#include <string>
#include <vector>

namespace enjin::sdk::models {

/// \brief Models a blockchain transaction log.
class ENJINSDK_EXPORT TransactionLog : public serialization::IDeserializable {
public:
    /// \brief Default constructor.
    TransactionLog() = default;

    ~TransactionLog() override = default;

    void deserialize(const std::string& json) override;

    /// \brief Returns the block number.
    /// \return The block number.
    [[nodiscard]] const std::optional<int>& get_block_number() const;

    /// \brief Returns the originating address.
    /// \return The address.
    [[nodiscard]] const std::optional<std::string>& get_address() const;

    /// \brief Returns the hash for the transaction (request).
    /// \return The hash.
    [[nodiscard]] const std::optional<std::string>& get_transaction_hash() const;

    /// \brief Returns the data objects.
    /// \return The data objects.
    [[nodiscard]] const std::optional<std::vector<json::JsonValue>>& get_data() const;

    /// \brief Returns the topics.
    /// \return The topics.
    [[nodiscard]] const std::optional<std::vector<json::JsonValue>>& get_topics() const;

    /// \brief Returns the transaction (request) event.
    /// \return The transaction event.
    [[nodiscard]] const std::optional<TransactionEvent>& get_event() const;

    bool operator==(const TransactionLog& rhs) const;

    bool operator!=(const TransactionLog& rhs) const;

private:
    std::optional<int> block_number;
    std::optional<std::string> address;
    std::optional<std::string> transaction_hash;
    std::optional<std::vector<json::JsonValue>> data;
    std::optional<std::vector<json::JsonValue>> topics;
    std::optional<TransactionEvent> event;
};

}

#endif //ENJINCPPSDK_TRANSACTIONLOG_HPP
