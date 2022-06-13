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

#include "enjinsdk/shared/GetPlatform.hpp"

#include "enjinsdk/JsonUtils.hpp"

using namespace enjin::sdk::graphql;
using namespace enjin::sdk::json;
using namespace enjin::sdk::shared;
using namespace enjin::sdk::utils;

GetPlatform::GetPlatform() : AbstractGraphqlRequest("enjin.sdk.shared.GetPlatform") {
}

std::string GetPlatform::serialize() const {
    return to_json().to_string();
}

GetPlatform& GetPlatform::set_with_contracts() {
    with_contracts_opt = true;
    return *this;
}

GetPlatform& GetPlatform::set_with_notifications() {
    with_notifications_opt = true;
    return *this;
}

JsonValue GetPlatform::to_json() const {
    JsonValue json = JsonValue::create_object();

    JsonUtils::try_set_field(json, "withContracts", with_contracts_opt);
    JsonUtils::try_set_field(json, "withNotificationDrivers", with_notifications_opt);

    return json;
}

bool GetPlatform::operator==(const GetPlatform& rhs) const {
    return static_cast<const AbstractGraphqlRequest&>(*this) == rhs
           && with_contracts_opt == rhs.with_contracts_opt
           && with_notifications_opt == rhs.with_notifications_opt;
}

bool GetPlatform::operator!=(const GetPlatform& rhs) const {
    return !(*this == rhs);
}
