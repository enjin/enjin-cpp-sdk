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

#include "enjinsdk/player/UnlinkWallet.hpp"

using namespace enjin::sdk::graphql;
using namespace enjin::sdk::json;
using namespace enjin::sdk::player;

UnlinkWallet::UnlinkWallet() : AbstractGraphqlRequest("enjin.sdk.player.UnlinkWallet") {
}

std::string UnlinkWallet::serialize() const {
    return to_json().to_string();
}

JsonValue UnlinkWallet::to_json() const {
    return JsonValue::create_object();
}

bool UnlinkWallet::operator==(const UnlinkWallet& rhs) const {
    return static_cast<const AbstractGraphqlRequest&>(*this) == rhs;
}

bool UnlinkWallet::operator!=(const UnlinkWallet& rhs) const {
    return !(*this == rhs);
}
