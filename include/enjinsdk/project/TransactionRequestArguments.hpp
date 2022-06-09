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

#ifndef ENJINSDK_PROJECTTRANSACTIONREQUESTARGUMENTS_HPP
#define ENJINSDK_PROJECTTRANSACTIONREQUESTARGUMENTS_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/JsonUtils.hpp"
#include "enjinsdk/JsonValue.hpp"
#include "enjinsdk/shared/TransactionFragmentArguments.hpp"
#include <optional>
#include <string>
#include <type_traits>
#include <utility>

namespace enjin::sdk::project {

/// \brief Interface used to set common arguments used in project transaction requests.
/// \tparam T The type of the implementing class.
template<class T>
class ENJINSDK_EXPORT TransactionRequestArguments : public shared::TransactionFragmentArguments<T> {
public:
    ~TransactionRequestArguments() override = default;

    [[nodiscard]] std::string serialize() const override {
        return to_json().to_string();
    }

    /// \brief Sets the Ethereum address of the sender.
    /// \param address The address.
    /// \return This request for chaining.
    T& set_eth_address(std::string address) {
        eth_address_opt = std::move(address);
        return static_cast<T&>(*this);
    }

    [[nodiscard]] json::JsonValue to_json() const override {
        json::JsonValue json = json::JsonValue::create_object();

        utils::JsonUtils::join_object(json, shared::TransactionFragmentArguments<T>::to_json());
        utils::JsonUtils::try_set_field(json, "ethAddress", eth_address_opt);

        return json;
    }

    bool operator==(const TransactionRequestArguments& rhs) const {
        return static_cast<const shared::TransactionFragmentArguments<T>&>(*this) == rhs
               && eth_address_opt == rhs.eth_address_opt;
    }

    bool operator!=(const TransactionRequestArguments& rhs) const {
        return !(*this == rhs);
    }

protected:
    /// \brief Constructs an instance of this class.
    TransactionRequestArguments() : shared::TransactionFragmentArguments<T>() {
        static_assert(std::is_base_of<TransactionRequestArguments, T>::value,
                      "Class T does not inherit from TransactionRequestArguments.");
    }

private:
    std::optional<std::string> eth_address_opt;
};

}

#endif //ENJINSDK_PROJECTTRANSACTIONREQUESTARGUMENTS_HPP
