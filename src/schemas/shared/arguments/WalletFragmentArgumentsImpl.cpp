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

#include "enjinsdk/internal/WalletFragmentArgumentsImpl.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::shared {

std::string WalletFragmentArgumentsImpl::serialize() const {
    rapidjson::Document document(rapidjson::kObjectType);
    utils::join_serialized_object_to_document(document, AssetFragmentArgumentsImpl::serialize());

    if (with_assets_created.has_value()) {
        utils::set_boolean_member(document, "withAssetsCreated", with_assets_created.value());
    }

    return utils::document_to_string(document);
}

void WalletFragmentArgumentsImpl::set_with_assets_created() {
    with_assets_created = true;
}

bool WalletFragmentArgumentsImpl::operator==(const WalletFragmentArgumentsImpl& rhs) const {
    return static_cast<const AssetFragmentArgumentsImpl&>(*this) ==
           static_cast<const AssetFragmentArgumentsImpl&>(rhs) &&
           with_assets_created == rhs.with_assets_created;
}

bool WalletFragmentArgumentsImpl::operator!=(const WalletFragmentArgumentsImpl& rhs) const {
    return !(rhs == *this);
}

}
