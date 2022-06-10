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

#include "enjinsdk/models/TransactionReceipt.hpp"

#include "enjinsdk/JsonUtils.hpp"
#include "enjinsdk/JsonValue.hpp"

using namespace enjin::sdk::json;
using namespace enjin::sdk::models;
using namespace enjin::sdk::serialization;
using namespace enjin::sdk::utils;

class TransactionReceipt::Impl final : public IDeserializable {
public:
    Impl() = default;

    ~Impl() override = default;

    void deserialize(const std::string& json) override {
        JsonValue json_object;

        if (!json_object.try_parse_as_object(json)) {
            block_hash.reset();
            block_number.reset();
            cumulative_gas_used.reset();
            gas_used.reset();
            from.reset();
            to.reset();
            transaction_hash.reset();
            transaction_index.reset();
            status.reset();
            logs.reset();

            return;
        }

        JsonUtils::try_get_field(json_object, "blockHash", block_hash);
        JsonUtils::try_get_field(json_object, "blockNumber", block_number);
        JsonUtils::try_get_field(json_object, "cumulativeGasUsed", cumulative_gas_used);
        JsonUtils::try_get_field(json_object, "gasUsed", gas_used);
        JsonUtils::try_get_field(json_object, "from", from);
        JsonUtils::try_get_field(json_object, "to", to);
        JsonUtils::try_get_field(json_object, "transactionHash", transaction_hash);
        JsonUtils::try_get_field(json_object, "transactionIndex", transaction_index);
        JsonUtils::try_get_field(json_object, "status", status);
        JsonUtils::try_get_field(json_object, "logs", logs);
    }

    [[nodiscard]] const std::optional<std::string>& get_block_hash() const {
        return block_hash;
    }

    [[nodiscard]] const std::optional<int>& get_block_number() const {
        return block_number;
    }

    [[nodiscard]] const std::optional<int>& get_cumulative_gas_used() const {
        return cumulative_gas_used;
    }

    [[nodiscard]] const std::optional<int>& get_gas_used() const {
        return gas_used;
    }

    [[nodiscard]] const std::optional<std::string>& get_from() const {
        return from;
    }

    [[nodiscard]] const std::optional<std::string>& get_to() const {
        return to;
    }

    [[nodiscard]] const std::optional<std::string>& get_transaction_hash() const {
        return transaction_hash;
    }

    [[nodiscard]] const std::optional<int>& get_transaction_index() const {
        return transaction_index;
    }

    [[nodiscard]] const std::optional<bool>& get_status() const {
        return status;
    }

    [[nodiscard]] const std::optional<std::vector<TransactionLog>>& get_logs() const {
        return logs;
    }

    bool operator==(const Impl& rhs) const {
        return block_hash == rhs.block_hash
               && block_number == rhs.block_number
               && cumulative_gas_used == rhs.cumulative_gas_used
               && gas_used == rhs.gas_used
               && from == rhs.from
               && to == rhs.to
               && transaction_hash == rhs.transaction_hash
               && transaction_index == rhs.transaction_index
               && status == rhs.status
               && logs == rhs.logs;
    }

    bool operator!=(const Impl& rhs) const {
        return !(*this == rhs);
    }

private:
    std::optional<std::string> block_hash;
    std::optional<int> block_number;
    std::optional<int> cumulative_gas_used;
    std::optional<int> gas_used;
    std::optional<std::string> from;
    std::optional<std::string> to;
    std::optional<std::string> transaction_hash;
    std::optional<int> transaction_index;
    std::optional<bool> status;
    std::optional<std::vector<TransactionLog>> logs;
};

TransactionReceipt::TransactionReceipt() : pimpl(std::make_unique<Impl>()) {
}

TransactionReceipt::TransactionReceipt(const TransactionReceipt& other) : pimpl(std::make_unique<Impl>(*other.pimpl)) {
}

TransactionReceipt::TransactionReceipt(TransactionReceipt&& other) noexcept = default;

TransactionReceipt::~TransactionReceipt() = default;

void TransactionReceipt::deserialize(const std::string& json) {
    pimpl->deserialize(json);
}

const std::optional<std::string>& TransactionReceipt::get_block_hash() const {
    return pimpl->get_block_hash();
}

const std::optional<int>& TransactionReceipt::get_block_number() const {
    return pimpl->get_block_number();
}

const std::optional<int>& TransactionReceipt::get_cumulative_gas_used() const {
    return pimpl->get_cumulative_gas_used();
}

const std::optional<int>& TransactionReceipt::get_gas_used() const {
    return pimpl->get_gas_used();
}

const std::optional<std::string>& TransactionReceipt::get_from() const {
    return pimpl->get_from();
}

const std::optional<std::string>& TransactionReceipt::get_to() const {
    return pimpl->get_to();
}

const std::optional<std::string>& TransactionReceipt::get_transaction_hash() const {
    return pimpl->get_transaction_hash();
}

const std::optional<int>& TransactionReceipt::get_transaction_index() const {
    return pimpl->get_transaction_index();
}

const std::optional<bool>& TransactionReceipt::get_status() const {
    return pimpl->get_status();
}

const std::optional<std::vector<TransactionLog>>& TransactionReceipt::get_logs() const {
    return pimpl->get_logs();
}

bool TransactionReceipt::operator==(const TransactionReceipt& rhs) const {
    return *pimpl == *rhs.pimpl;
}

bool TransactionReceipt::operator!=(const TransactionReceipt& rhs) const {
    return *pimpl != *rhs.pimpl;
}

TransactionReceipt& TransactionReceipt::operator=(const TransactionReceipt& rhs) {
    pimpl = std::make_unique<Impl>(*rhs.pimpl);
    return *this;
}
