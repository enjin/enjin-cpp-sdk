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

#ifndef ENJINCPPSDK_PLAYERUNLINKWALLET_HPP
#define ENJINCPPSDK_PLAYERUNLINKWALLET_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/internal/AbstractGraphqlRequest.hpp"
#include <string>

namespace enjin::sdk::player {

/// \brief Request for unlinking a wallet from the player
class ENJINSDK_EXPORT UnlinkWallet : public graphql::AbstractGraphqlRequest {
public:
    /// \brief Default constructor.
    UnlinkWallet();

    ~UnlinkWallet() override = default;

    [[nodiscard]] std::string serialize() const override;

    bool operator==(const UnlinkWallet& rhs) const;

    bool operator!=(const UnlinkWallet& rhs) const;
};

}

#endif //ENJINCPPSDK_PLAYERUNLINKWALLET_HPP
