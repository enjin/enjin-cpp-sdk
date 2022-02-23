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

#if _WIN32
#define _SILENCE_CXX17_ITERATOR_BASE_CLASS_DEPRECATION_WARNING
#endif

#include "enjinsdk/models/LinkingInfo.hpp"

#include "rapidjson/document.h"

namespace enjin::sdk::models {

void enjin::sdk::models::LinkingInfo::deserialize(const std::string& json) {
    rapidjson::Document document;
    document.Parse(json.c_str());
    if (document.IsObject()) {
        if (document.HasMember(CODE_KEY) && document[CODE_KEY].IsString()) {
            code.emplace(document[CODE_KEY].GetString());
        }
        if (document.HasMember(QR_KEY) && document[QR_KEY].IsString()) {
            qr.emplace(document[QR_KEY].GetString());
        }
    }
}

const std::optional<std::string>& LinkingInfo::get_code() const {
    return code;
}

const std::optional<std::string>& LinkingInfo::get_qr() const {
    return qr;
}

bool LinkingInfo::operator==(const LinkingInfo& rhs) const {
    return code == rhs.code &&
           qr == rhs.qr;
}

bool LinkingInfo::operator!=(const LinkingInfo& rhs) const {
    return !(rhs == *this);
}

}
