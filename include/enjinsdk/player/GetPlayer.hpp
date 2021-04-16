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

#ifndef ENJINCPPSDK_PLAYERGETPLAYER_HPP
#define ENJINCPPSDK_PLAYERGETPLAYER_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/internal/AbstractGraphqlRequest.hpp"
#include "enjinsdk/shared/PlayerFragmentArguments.hpp"

namespace enjin::sdk::player {

/// \brief Request for getting information about the player.
class ENJINSDK_EXPORT GetPlayer : public graphql::AbstractGraphqlRequest,
                                  public shared::PlayerFragmentArguments<GetPlayer> {
public:
    /// \brief Default constructor.
    GetPlayer();

    ~GetPlayer() override = default;

    [[nodiscard]] std::string serialize() const override;

    bool operator==(const GetPlayer& rhs) const;

    bool operator!=(const GetPlayer& rhs) const;
};

}

namespace enjin::sdk::shared {

template ENJINSDK_EXPORT player::GetPlayer& PlayerFragmentArguments<player::GetPlayer>::set_with_linking_info();

template ENJINSDK_EXPORT player::GetPlayer& PlayerFragmentArguments<player::GetPlayer>::set_qr_size(int size);

template ENJINSDK_EXPORT player::GetPlayer& PlayerFragmentArguments<player::GetPlayer>::set_with_wallet();

}

#endif //ENJINCPPSDK_PLAYERGETPLAYER_HPP
