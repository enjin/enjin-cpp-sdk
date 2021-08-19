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

#ifndef ENJINCPPSDK_SHAREDTRANSACTIONREQUESTARGUMENTSIMPL_HPP
#define ENJINCPPSDK_SHAREDTRANSACTIONREQUESTARGUMENTSIMPL_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/internal/TransactionFragmentArgumentsImpl.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::shared {

/// \brief Internal implementation class for storing values of a GraphQL Transaction request.
class ENJINSDK_EXPORT TransactionRequestArgumentsImpl : public TransactionFragmentArgumentsImpl {
public:
    /// \brief Default constructor.
    TransactionRequestArgumentsImpl() = default;

    ~TransactionRequestArgumentsImpl() override = default;

    [[nodiscard]] std::string serialize() const override;

    /// \brief Sets the value for the associated field to the given boolean.
    /// \param send The send state.
    void set_send(bool send);

    bool operator==(const TransactionRequestArgumentsImpl& rhs) const;

    bool operator!=(const TransactionRequestArgumentsImpl& rhs) const;

private:
    std::optional<bool> send;
};

}

#endif //ENJINCPPSDK_SHAREDTRANSACTIONREQUESTARGUMENTSIMPL_HPP
