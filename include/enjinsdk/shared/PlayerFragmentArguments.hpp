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

#ifndef ENJINCPPSDK_SHAREDPLAYERFRAGMENTARGUMENTS_HPP
#define ENJINCPPSDK_SHAREDPLAYERFRAGMENTARGUMENTS_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/JsonUtils.hpp"
#include "enjinsdk/JsonValue.hpp"
#include "enjinsdk/shared/WalletFragmentArguments.hpp"
#include <optional>
#include <string>
#include <type_traits>

namespace enjin::sdk::shared {

/// \brief Fragment interface used to request certain information from players returned by the platform.
/// \tparam T The type of the implementing class.
template<class T>
class ENJINSDK_EXPORT PlayerFragmentArguments : public WalletFragmentArguments<T> {
public:
    ~PlayerFragmentArguments() override = default;

    [[nodiscard]] std::string serialize() const override {
        return to_json().to_string();
    }

    /// \brief Sets the request to include the linking information with the player.
    /// \return This request for chaining.
    T& set_with_linking_info() {
        with_linking_info_opt = true;
        return static_cast<T&>(*this);
    }

    /// \brief Sets the desired size of the QR image in pixels when used with set_with_linking_info().
    /// \param size The size.
    /// \return This request for chaining.
    T& set_qr_size(int size) {
        qr_size_opt = size;
        return static_cast<T&>(*this);
    }

    /// \brief Sets the request to include the wallet with the player.
    /// \return This request for chaining.
    T& set_with_wallet() {
        with_wallet_opt = true;
        return static_cast<T&>(*this);
    }

    [[nodiscard]] json::JsonValue to_json() const override {
        json::JsonValue json = json::JsonValue::create_object();

        utils::JsonUtils::join_object(json, WalletFragmentArguments<T>::to_json());
        utils::JsonUtils::try_set_field(json, "withLinkingInfo", with_linking_info_opt);
        utils::JsonUtils::try_set_field(json, "linkingCodeQrSize", qr_size_opt);
        utils::JsonUtils::try_set_field(json, "withPlayerWallet", with_wallet_opt);

        return json;
    }

    bool operator==(const PlayerFragmentArguments& rhs) const {
        return static_cast<const WalletFragmentArguments<T>&>(*this) == rhs
               && with_linking_info_opt == rhs.with_linking_info_opt
               && qr_size_opt == rhs.qr_size_opt
               && with_wallet_opt == rhs.with_wallet_opt;
    }

    bool operator!=(const PlayerFragmentArguments& rhs) const {
        return !(*this == rhs);
    }

protected:
    /// \brief Sole constructor.
    PlayerFragmentArguments() : WalletFragmentArguments<T>() {
        static_assert(std::is_base_of<PlayerFragmentArguments, T>::value,
                      "Class T does not inherit from PlayerFragmentArguments.");
    }

private:
    std::optional<bool> with_linking_info_opt;
    std::optional<int> qr_size_opt;
    std::optional<bool> with_wallet_opt;
};

}

#endif //ENJINCPPSDK_SHAREDPLAYERFRAGMENTARGUMENTS_HPP
