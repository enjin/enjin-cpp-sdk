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

#include "enjinsdk/project/ResetEnjApproval.hpp"

using namespace enjin::sdk::graphql;
using namespace enjin::sdk::json;
using namespace enjin::sdk::project;

ResetEnjApproval::ResetEnjApproval() : AbstractGraphqlRequest("enjin.sdk.project.ResetEnjApproval"),
                                       ProjectTransactionRequestArguments<ResetEnjApproval>() {
}

std::string ResetEnjApproval::serialize() const {
    return ProjectTransactionRequestArguments<ResetEnjApproval>::serialize();
}

JsonValue ResetEnjApproval::to_json() const {
    return ProjectTransactionRequestArguments<ResetEnjApproval>::to_json();
}

bool ResetEnjApproval::operator==(const ResetEnjApproval& rhs) const {
    return static_cast<const AbstractGraphqlRequest&>(*this) == rhs
           && static_cast<const ProjectTransactionRequestArguments<ResetEnjApproval>&>(*this) == rhs;
}

bool ResetEnjApproval::operator!=(const ResetEnjApproval& rhs) const {
    return !(*this == rhs);
}
