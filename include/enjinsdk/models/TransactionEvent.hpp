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

#ifndef ENJINCPPSDK_TRANSACTIONEVENT_HPP
#define ENJINCPPSDK_TRANSACTIONEVENT_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/IDeserializable.hpp"
#include <optional>
#include <string>
#include <vector>

namespace enjin::sdk::models {

/// \brief Models a blockchain transaction event.
class ENJINSDK_EXPORT TransactionEvent : public serialization::IDeserializable {
public:
    /// \brief Default constructor.
    TransactionEvent() = default;

    ~TransactionEvent() override = default;

    void deserialize(const std::string& json) override;

    /// \brief Returns the name of this event.
    /// \return The name.
    [[nodiscard]] const std::optional<std::string>& get_name() const;

    /// \brief Returns the serialized parameters for this event.
    /// \return The parameters.
    [[nodiscard]] const std::optional<std::vector<std::string>>& get_inputs() const;

    /// \brief Returns the serialized non-indexed parameters for this event.
    /// \return The non-indexed parameters.
    [[nodiscard]] const std::optional<std::vector<std::string>>& get_non_indexed_inputs() const;

    /// \brief Returns the serialized indexed parameters for this event.
    /// \return The indexed parameters.
    [[nodiscard]] const std::optional<std::vector<std::string>>& get_indexed_inputs() const;

    /// \brief Returns the event signature.
    /// \return The signature.
    /// \remarks If the event was anonymous, then the optional will not have a value.
    [[nodiscard]] const std::optional<std::string>& get_signature() const;

    /// \brief Returns the encoded signature.
    /// \return The encoded signature.
    [[nodiscard]] const std::optional<std::string>& get_encoded_signature() const;

    bool operator==(const TransactionEvent& rhs) const;

    bool operator!=(const TransactionEvent& rhs) const;

private:
    std::optional<std::string> name;
    std::optional<std::vector<std::string>> inputs;
    std::optional<std::vector<std::string>> non_indexed_inputs;
    std::optional<std::vector<std::string>> indexed_inputs;
    std::optional<std::string> signature;
    std::optional<std::string> encoded_signature;
};

}

#endif //ENJINCPPSDK_TRANSACTIONEVENT_HPP
