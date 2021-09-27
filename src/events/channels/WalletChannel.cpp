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

#include "WalletChannel.hpp"

#include "enjinsdk_utils/StringUtils.hpp"
#include <sstream>
#include <utility>

namespace enjin::sdk::events {

WalletChannel::WalletChannel(const models::Platform& platform, std::string eth_address)
        : platform(platform), eth_address(std::move(eth_address)) {
}

std::string WalletChannel::channel() const {
    std::stringstream ss;
    ss << "enjincloud."
       << utils::to_lower(platform.get_network().value())
       << ".wallet."
       << eth_address;
    return ss.str();
}

}
