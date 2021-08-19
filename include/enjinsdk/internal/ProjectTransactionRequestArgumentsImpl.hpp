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

#ifndef ENJINSDK_PROJECTPROJECTTRANSACTIONREQUESTARGUMENTSIMPL_HPP
#define ENJINSDK_PROJECTPROJECTTRANSACTIONREQUESTARGUMENTSIMPL_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/internal/TransactionRequestArgumentsImpl.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::project {

/// \brief Internal implementation class for storing values of a GraphQL Transaction request in the project schema.
class ENJINSDK_EXPORT ProjectTransactionRequestArgumentsImpl : public shared::TransactionRequestArgumentsImpl {
public:
    /// \brief Default constructor.
    ProjectTransactionRequestArgumentsImpl() = default;

    ~ProjectTransactionRequestArgumentsImpl() override = default;

    [[nodiscard]] std::string serialize() const override;

    /// \brief Sets the value for the associated field to the given string.
    /// \param address The address.
    void set_eth_address(const std::string& address);

    bool operator==(const ProjectTransactionRequestArgumentsImpl& rhs) const;

    bool operator!=(const ProjectTransactionRequestArgumentsImpl& rhs) const;

private:
    std::optional<std::string> eth_address;
};

}

#endif //ENJINSDK_PROJECTPROJECTTRANSACTIONREQUESTARGUMENTSIMPL_HPP
