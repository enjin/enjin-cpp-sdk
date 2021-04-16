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

#include "enjinsdk/shared/GetPlatform.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::shared {

GetPlatform::GetPlatform() : graphql::AbstractGraphqlRequest("enjin.sdk.shared.GetPlatform") {
}

std::string GetPlatform::serialize() const {
    rapidjson::Document document(rapidjson::kObjectType);

    if (with_contracts.has_value()) {
        utils::set_boolean_member(document, "withContracts", with_contracts.value());
    }
    if (with_notifications.has_value()) {
        utils::set_boolean_member(document, "withNotificationDrivers", with_notifications.value());
    }

    return utils::document_to_string(document);
}

GetPlatform& GetPlatform::set_with_contracts() {
    with_contracts = true;
    return *this;
}

GetPlatform& GetPlatform::set_with_notifications() {
    with_notifications = true;
    return *this;
}

bool GetPlatform::operator==(const GetPlatform& rhs) const {
    return static_cast<const graphql::AbstractGraphqlRequest&>(*this) ==
           static_cast<const graphql::AbstractGraphqlRequest&>(rhs) &&
           with_contracts == rhs.with_contracts &&
           with_notifications == rhs.with_notifications;
}

bool GetPlatform::operator!=(const GetPlatform& rhs) const {
    return !(rhs == *this);
}

}
