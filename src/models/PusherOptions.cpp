/* Copyright 2021 Enjin Pte Ltd.
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

#include "enjinsdk/models/PusherOptions.hpp"

#include "rapidjson/document.h"

namespace enjin::sdk::models {

void PusherOptions::deserialize(const std::string& json) {
    rapidjson::Document document;
    document.Parse(json.c_str());
    if (document.IsObject()) {
        if (document.HasMember(CLUSTER_KEY) && document[CLUSTER_KEY].IsString()) {
            cluster.emplace(document[CLUSTER_KEY].GetString());
        }
        if (document.HasMember(ENCRYPTED_KEY) && document[ENCRYPTED_KEY].IsBool()) {
            encrypted.emplace(document[ENCRYPTED_KEY].GetBool());
        }
    }
}

const std::optional<std::string>& PusherOptions::get_cluster() const {
    return cluster;
}

const std::optional<bool>& PusherOptions::get_encrypted() const {
    return encrypted;
}

bool PusherOptions::operator==(const PusherOptions& rhs) const {
    return cluster == rhs.cluster &&
           encrypted == rhs.encrypted;
}

bool PusherOptions::operator!=(const PusherOptions& rhs) const {
    return !(rhs == *this);
}

}
