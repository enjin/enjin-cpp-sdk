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
#include "enjinsdk/internal/PlayerFragmentArgumentsImpl.hpp"
#include "enjinsdk/shared/WalletFragmentArguments.hpp"
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
        return impl.serialize();
    }

    /// \brief Sets the request to include the linking information with the player.
    /// \return This request for chaining.
    T& set_with_linking_info() {
        impl.set_with_linking_info();
        return static_cast<T&>(*this);
    }

    /// \brief Sets the desired size of the QR image in pixels when used with set_with_linking_info().
    /// \param size The size.
    /// \return This request for chaining.
    T& set_qr_size(int size) {
        impl.set_qr_size(size);
        return static_cast<T&>(*this);
    }

    /// \brief Sets the request to include the wallet with the player.
    /// \return This request for chaining.
    T& set_with_wallet() {
        impl.set_with_wallet();
        return static_cast<T&>(*this);
    }

    bool operator==(const PlayerFragmentArguments& rhs) const {
        return impl == rhs.impl;
    }

    bool operator!=(const PlayerFragmentArguments& rhs) const {
        return rhs != *this;
    }

protected:
    /// \brief Sole constructor.
    PlayerFragmentArguments() {
        static_assert(std::is_base_of<PlayerFragmentArguments, T>::value,
                      "Class T does not inherit from PlayerFragmentArguments.");
    }

private:
    PlayerFragmentArgumentsImpl impl;
};

}

#endif //ENJINCPPSDK_SHAREDPLAYERFRAGMENTARGUMENTS_HPP
