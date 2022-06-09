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

#include "enjinsdk/models/TransactionEvent.hpp"

#include "enjinsdk/JsonUtils.hpp"
#include "enjinsdk/JsonValue.hpp"

using namespace enjin::sdk::json;
using namespace enjin::sdk::models;
using namespace enjin::sdk::utils;

void TransactionEvent::deserialize(const std::string& json) {
    JsonValue json_object;

    if (!json_object.try_parse_as_object(json)) {
        name.reset();
        inputs.reset();
        non_indexed_inputs.reset();
        indexed_inputs.reset();
        signature.reset();
        encoded_signature.reset();

        return;
    }

    JsonUtils::try_get_field(json_object, "name", name);
    JsonUtils::try_get_field(json_object, "inputs", inputs);
    JsonUtils::try_get_field(json_object, "nonIndexedInputs", non_indexed_inputs);
    JsonUtils::try_get_field(json_object, "indexedInputs", indexed_inputs);
    JsonUtils::try_get_field(json_object, "signature", signature);
    JsonUtils::try_get_field(json_object, "encodedSignature", encoded_signature);
}

const std::optional<std::string>& TransactionEvent::get_name() const {
    return name;
}

const std::optional<std::vector<std::string>>& TransactionEvent::get_inputs() const {
    return inputs;
}

const std::optional<std::vector<std::string>>& TransactionEvent::get_non_indexed_inputs() const {
    return non_indexed_inputs;
}

const std::optional<std::vector<std::string>>& TransactionEvent::get_indexed_inputs() const {
    return indexed_inputs;
}

const std::optional<std::string>& TransactionEvent::get_signature() const {
    return signature;
}

const std::optional<std::string>& TransactionEvent::get_encoded_signature() const {
    return encoded_signature;
}

bool TransactionEvent::operator==(const TransactionEvent& rhs) const {
    return name == rhs.name
           && inputs == rhs.inputs
           && non_indexed_inputs == rhs.non_indexed_inputs
           && indexed_inputs == rhs.indexed_inputs
           && signature == rhs.signature
           && encoded_signature == rhs.encoded_signature;
}

bool TransactionEvent::operator!=(const TransactionEvent& rhs) const {
    return !(*this == rhs);
}
