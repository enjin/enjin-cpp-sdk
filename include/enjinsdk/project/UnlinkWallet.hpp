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

#ifndef ENJINCPPSDK_PROJECTUNLINKWALLET_HPP
#define ENJINCPPSDK_PROJECTUNLINKWALLET_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/internal/AbstractGraphqlRequest.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::project {

/// \brief Request for unlinking a wallet from the project.
class ENJINSDK_EXPORT UnlinkWallet : public graphql::AbstractGraphqlRequest {
public:
    /// \brief Default constructor.
    UnlinkWallet();

    ~UnlinkWallet() override = default;

    [[nodiscard]] std::string serialize() const override;

    /// \brief Sets the Ethereum address of the wallet to unlink.
    /// \param eth_address The address.
    /// \return This request for chaining.
    UnlinkWallet& set_eth_address(std::string eth_address);

    [[nodiscard]] json::JsonValue to_json() const override;

    bool operator==(const UnlinkWallet& rhs) const;

    bool operator!=(const UnlinkWallet& rhs) const;

private:
    std::optional<std::string> eth_address_opt;
};

}

#endif //ENJINCPPSDK_PROJECTUNLINKWALLET_HPP
