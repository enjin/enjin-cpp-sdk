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

#ifndef ENJINCPPSDK_SHAREDBALANCEFRAGMENTARGUMENTSIMPL_HPP
#define ENJINCPPSDK_SHAREDBALANCEFRAGMENTARGUMENTSIMPL_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/ISerializable.hpp"
#include "enjinsdk/models/AssetIdFormat.hpp"
#include "enjinsdk/models/AssetIndexFormat.hpp"
#include <optional>

namespace enjin::sdk::shared {

/// \brief Internal implementation class for storing values of a GraphQL Balance fragment.
class ENJINSDK_EXPORT BalanceFragmentArgumentsImpl : public serialization::ISerializable {
public:
    /// \brief Default constructor to be used internally.
    BalanceFragmentArgumentsImpl() = default;

    ~BalanceFragmentArgumentsImpl() override = default;

    [[nodiscard]] std::string serialize() const override;

    /// \brief Sets the value for the associated field to the passed value.
    /// \param bal_id_format The ID format.
    void set_bal_id_format(models::AssetIdFormat bal_id_format);

    /// \brief Sets the value for the associated field to the passed value.
    /// \param bal_index_format The index format.
    void set_bal_index_format(models::AssetIndexFormat bal_index_format);

    /// \brief Sets the value for the associated field to true.
    void set_with_bal_project_id();

    /// \brief Sets the value for the associated field to true.
    void set_with_bal_wallet_address();

    bool operator==(const BalanceFragmentArgumentsImpl& rhs) const;

    bool operator!=(const BalanceFragmentArgumentsImpl& rhs) const;

private:
    std::optional<models::AssetIdFormat> bal_id_format;
    std::optional<models::AssetIndexFormat> bal_index_format;
    std::optional<bool> with_bal_project_id;
    std::optional<bool> with_bal_wallet_address;
};

}

#endif //ENJINCPPSDK_SHAREDBALANCEFRAGMENTARGUMENTSIMPL_HPP
