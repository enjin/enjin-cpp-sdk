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

#ifndef ENJINCPPSDK_SHAREDPLAYERFRAGMENTARGUMENTSIMPL_HPP
#define ENJINCPPSDK_SHAREDPLAYERFRAGMENTARGUMENTSIMPL_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/internal/WalletFragmentArgumentsImpl.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::shared {

/// \brief Internal implementation class for storing values of a GraphQL Player fragment.
class ENJINSDK_EXPORT PlayerFragmentArgumentsImpl : public WalletFragmentArgumentsImpl {
public:
    /// \brief Default constructor to be used internally.
    PlayerFragmentArgumentsImpl() = default;

    ~PlayerFragmentArgumentsImpl() override = default;

    [[nodiscard]] std::string serialize() const override;

    /// \brief Sets the value for the associated field to true.
    void set_with_linking_info();

    /// \brief Sets the value for the associated field to the passed value.
    /// \param size The size.
    void set_qr_size(int size);

    /// \brief Sets the value for the associated field to true.
    void set_with_wallet();

    bool operator==(const PlayerFragmentArgumentsImpl& rhs) const;

    bool operator!=(const PlayerFragmentArgumentsImpl& rhs) const;

private:
    std::optional<bool> with_linking_info;
    std::optional<int> qr_size;
    std::optional<bool> with_wallet;
};

}

#endif //ENJINCPPSDK_SHAREDPLAYERFRAGMENTARGUMENTSIMPL_HPP
