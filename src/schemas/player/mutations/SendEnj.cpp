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

#include "enjinsdk/player/SendEnj.hpp"

#include "enjinsdk/JsonUtils.hpp"
#include <utility>

using namespace enjin::sdk::graphql;
using namespace enjin::sdk::json;
using namespace enjin::sdk::player;
using namespace enjin::sdk::shared;
using namespace enjin::sdk::utils;

SendEnj::SendEnj() : AbstractGraphqlRequest("enjin.sdk.player.SendEnj"),
                     TransactionFragmentArguments<SendEnj>() {
}

std::string SendEnj::serialize() const {
    return to_json().to_string();
}

SendEnj& SendEnj::set_recipient_address(std::string recipient_address) {
    recipient_address_opt = std::move(recipient_address);
    return *this;
}

SendEnj& SendEnj::set_value(std::string value) {
    value_opt = std::move(value);
    return *this;
}

JsonValue SendEnj::to_json() const {
    JsonValue json = JsonValue::create_object();

    JsonUtils::join_object(json, TransactionFragmentArguments<SendEnj>::to_json());
    JsonUtils::try_set_field(json, "recipientAddress", recipient_address_opt);
    JsonUtils::try_set_field(json, "value", value_opt);

    return json;
}

bool SendEnj::operator==(const SendEnj& rhs) const {
    return static_cast<const AbstractGraphqlRequest&>(*this) == rhs
           && static_cast<const TransactionFragmentArguments<SendEnj>&>(*this) == rhs
           && recipient_address_opt == rhs.recipient_address_opt
           && value_opt == rhs.value_opt;
}

bool SendEnj::operator!=(const SendEnj& rhs) const {
    return !(*this == rhs);
}
