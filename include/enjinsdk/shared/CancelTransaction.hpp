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

#ifndef ENJINCPPSDK_SHAREDCANCELTRANSACTION_HPP
#define ENJINCPPSDK_SHAREDCANCELTRANSACTION_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/internal/AbstractGraphqlRequest.hpp"
#include <optional>

namespace enjin::sdk::shared {

/// \brief Request for canceling a transaction on the platform.
class ENJINSDK_EXPORT CancelTransaction : public graphql::AbstractGraphqlRequest {
public:
    /// \brief Default constructor.
    CancelTransaction();

    ~CancelTransaction() override = default;

    [[nodiscard]] std::string serialize() const override;

    /// \brief Sets the ID of the transaction to cancel.
    /// \param id The ID.
    /// \return This request for chaining.
    CancelTransaction& set_id(int id);

    bool operator==(const CancelTransaction& rhs) const;

    bool operator!=(const CancelTransaction& rhs) const;

private:
    std::optional<int> id;
};

}

#endif //ENJINCPPSDK_SHAREDCANCELTRANSACTION_HPP
