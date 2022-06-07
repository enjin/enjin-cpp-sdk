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

#include "enjinsdk/player/ResetEnjApproval.hpp"

using namespace enjin::sdk::graphql;
using namespace enjin::sdk::json;
using namespace enjin::sdk::player;
using namespace enjin::sdk::shared;

ResetEnjApproval::ResetEnjApproval() : AbstractGraphqlRequest("enjin.sdk.player.ResetEnjApproval"),
                                       TransactionFragmentArguments<ResetEnjApproval>() {
}

std::string ResetEnjApproval::serialize() const {
    return TransactionFragmentArguments<ResetEnjApproval>::serialize();
}

JsonValue ResetEnjApproval::to_json() const {
    return TransactionFragmentArguments<ResetEnjApproval>::to_json();
}

bool ResetEnjApproval::operator==(const ResetEnjApproval& rhs) const {
    return static_cast<const AbstractGraphqlRequest&>(*this) == rhs
           && static_cast<const TransactionFragmentArguments<ResetEnjApproval>&>(*this) == rhs;
}

bool ResetEnjApproval::operator!=(const ResetEnjApproval& rhs) const {
    return !(*this == rhs);
}
