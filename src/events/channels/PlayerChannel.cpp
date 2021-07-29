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

#include "PlayerChannel.hpp"

#include "enjinsdk_utils/StringUtils.hpp"
#include <sstream>
#include <utility>

namespace enjin::sdk::events {

PlayerChannel::PlayerChannel(const models::Platform& platform, std::string project_uuid, std::string player_id)
        : platform(platform), project_uuid(std::move(project_uuid)), player_id(std::move(player_id)) {
}

std::string PlayerChannel::channel() const {
    std::stringstream ss;
    ss << "enjincloud."
       << utils::to_lower(platform.get_network().value())
       << ".project."
       << project_uuid
       << ".player."
       << player_id;
    return ss.str();
}

}
