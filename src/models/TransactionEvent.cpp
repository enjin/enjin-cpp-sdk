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

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::models {

void TransactionEvent::deserialize(const std::string& json) {
    rapidjson::Document document;
    document.Parse(json.c_str());
    if (document.IsObject()) {
        if (document.HasMember(NAME_KEY) && document[NAME_KEY].IsString()) {
            name.emplace(document[NAME_KEY].GetString());
        }
        if (document.HasMember(INPUTS_KEY) && document[INPUTS_KEY].IsArray()) {
            inputs.emplace(utils::get_array_as_serialized_vector(document, INPUTS_KEY));
        }
        if (document.HasMember(NON_INDEXED_INPUTS_KEY) && document[NON_INDEXED_INPUTS_KEY].IsArray()) {
            non_indexed_inputs.emplace(utils::get_array_as_serialized_vector(document, NON_INDEXED_INPUTS_KEY));
        }
        if (document.HasMember(INDEXED_INPUTS_KEY) && document[INDEXED_INPUTS_KEY].IsArray()) {
            indexed_inputs.emplace(utils::get_array_as_serialized_vector(document, INDEXED_INPUTS_KEY));
        }
        if (document.HasMember(SIGNATURE_KEY) && document[SIGNATURE_KEY].IsString()) {
            signature.emplace(document[SIGNATURE_KEY].GetString());
        }
        if (document.HasMember(ENCODED_SIGNATURE_KEY) && document[ENCODED_SIGNATURE_KEY].IsString()) {
            encoded_signature.emplace(document[ENCODED_SIGNATURE_KEY].GetString());
        }
    }
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
    return name == rhs.name &&
           inputs == rhs.inputs &&
           non_indexed_inputs == rhs.non_indexed_inputs &&
           indexed_inputs == rhs.indexed_inputs &&
           signature == rhs.signature &&
           encoded_signature == rhs.encoded_signature;
}

bool TransactionEvent::operator!=(const TransactionEvent& rhs) const {
    return !(rhs == *this);
}

}
