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

#include "enjinsdk/models/MintInput.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::models {

std::string MintInput::serialize() const {
    rapidjson::Document document(rapidjson::kObjectType);

    if (to.has_value()) {
        utils::set_string_member(document, TO_KEY, to.value());
    }
    if (value.has_value()) {
        utils::set_string_member(document, VALUE_KEY, value.value());
    }

    return utils::document_to_string(document);
}

MintInput& MintInput::set_to(const std::string& address) {
    to = address;
    return *this;
}

MintInput& MintInput::set_value(const std::string& value) {
    MintInput::value = value;
    return *this;
}

bool MintInput::operator==(const MintInput& rhs) const {
    return to == rhs.to &&
           value == rhs.value;
}

bool MintInput::operator!=(const MintInput& rhs) const {
    return !(rhs == *this);
}

}
