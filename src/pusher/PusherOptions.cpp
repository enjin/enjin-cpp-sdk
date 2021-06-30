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

#include "PusherOptions.hpp"

#include <sstream>

namespace enjin::pusher {

PusherOptions& PusherOptions::set_cluster(const std::string& cluster) {
    PusherOptions::cluster = cluster;
    return *this;
}

PusherOptions& PusherOptions::set_encrypted(bool encrypted) {
    PusherOptions::encrypted = encrypted;
    return *this;
}

std::string PusherOptions::get_cluster() const {
    return cluster.value_or(DEFAULT_CLUSTER);
}

std::chrono::milliseconds PusherOptions::get_client_timeout() const {
    return client_timeout.value_or(DEFAULT_CLIENT_TIMEOUT);
}

bool PusherOptions::is_encrypted() const {
    return encrypted.value_or(DEFAULT_ENCRYPTION);
}

std::string PusherOptions::host() const {
    std::stringstream ss;
    ss << "ws-"
       << get_cluster()
       << ".pusher.com";
    return ss.str();
}

}
