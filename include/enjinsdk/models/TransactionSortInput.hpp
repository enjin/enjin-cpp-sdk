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

#ifndef ENJINCPPSDK_TRANSACTIONSORTINPUT_HPP
#define ENJINCPPSDK_TRANSACTIONSORTINPUT_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/ISerializable.hpp"
#include "enjinsdk/models/SortDirection.hpp"
#include "enjinsdk/models/TransactionField.hpp"
#include <optional>

namespace enjin::sdk::models {

/// \brief Models sorting input for transactions.
class ENJINSDK_EXPORT TransactionSortInput : public serialization::ISerializable {
public:
    /// \brief Default constructor.
    TransactionSortInput() = default;

    ~TransactionSortInput() override = default;

    [[nodiscard]] std::string serialize() const override;

    /// \brief Sets the field to sort by.
    /// \param field The field.
    /// \return This input for chaining.
    TransactionSortInput& set_field(TransactionField field);

    /// \brief Sets the direction to sort by.
    /// \param direction The direction.
    /// \return This input for chaining.
    TransactionSortInput& set_direction(SortDirection direction);

    [[nodiscard]] json::JsonValue to_json() const override;

    bool operator==(const TransactionSortInput& rhs) const;

    bool operator!=(const TransactionSortInput& rhs) const;

private:
    std::optional<TransactionField> field_opt;
    std::optional<SortDirection> direction_opt;
};

}

#endif //ENJINCPPSDK_TRANSACTIONSORTINPUT_HPP
