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

#ifndef ENJINCPPSDK_LINKINGINFO_HPP
#define ENJINCPPSDK_LINKINGINFO_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/IDeserializable.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::models {

/// \brief Models the linking information for a player.
class ENJINSDK_EXPORT LinkingInfo : public serialization::IDeserializable {
public:
    /// \brief Default constructor.
    LinkingInfo() = default;

    ~LinkingInfo() override = default;

    void deserialize(const std::string& json) override;

    /// \brief Returns the linking code used to link a wallet to the player this info belongs to.
    /// \return The linking code.
    [[nodiscard]] const std::optional<std::string>& get_code() const;

    /// \brief Returns the URL for the QR image that links a wallet to the player this info belongs to.
    /// \return The URL for the image.
    [[nodiscard]] const std::optional<std::string>& get_qr() const;

    bool operator==(const LinkingInfo& rhs) const;

    bool operator!=(const LinkingInfo& rhs) const;

private:
    std::optional<std::string> code;
    std::optional<std::string> qr;

    constexpr static char CODE_KEY[] = "code";
    constexpr static char QR_KEY[] = "qr";
};

}

#endif //ENJINCPPSDK_LINKINGINFO_HPP
