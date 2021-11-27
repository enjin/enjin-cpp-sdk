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

#include "enjinsdk/TrustedPlatformHandler.hpp"

#include "enjinsdk_utils/StringUtils.hpp"
#include <utility>

namespace enjin::sdk::http {

bool TrustedPlatformHandler::is_authenticated() const {
    std::lock_guard<std::mutex> guard(auth_token_mutex);
    return auth_token.has_value() && !utils::is_empty_or_whitespace(auth_token.value());
}

void TrustedPlatformHandler::set_auth_token(std::string auth_token) {
    std::lock_guard<std::mutex> guard(auth_token_mutex);
    TrustedPlatformHandler::auth_token = std::move(auth_token);
}

const std::optional<std::string>& TrustedPlatformHandler::get_auth_token() const {
    std::lock_guard<std::mutex> guard(auth_token_mutex);
    return auth_token;
}

}
