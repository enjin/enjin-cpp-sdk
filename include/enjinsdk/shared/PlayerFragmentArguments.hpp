#ifndef ENJINCPPSDK_SHAREDPLAYERFRAGMENTARGUMENTS_HPP
#define ENJINCPPSDK_SHAREDPLAYERFRAGMENTARGUMENTS_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/ISerializable.hpp"
#include "enjinsdk/internal/PlayerFragmentArgumentsImpl.hpp"

namespace enjin::sdk::shared {

/// \brief Fragment interface used to request certain information from players returned by the platform.
/// \tparam T The type of the implementing class.
template<class T>
class ENJINSDK_EXPORT PlayerFragmentArguments : public serialization::ISerializable {
public:
    ~PlayerFragmentArguments() override = default;

    [[nodiscard]] std::string serialize() const override {
        return impl.serialize();
    }

    /// \brief Sets the request to include the linking information with the player.
    /// \return This request for chaining.
    T& set_with_linking_info() {
        impl.set_with_linking_info();
        return dynamic_cast<T&>(*this);
    }

    /// \brief Sets the desired size of the QR image in pixels when used with set_with_linking_info().
    /// \param size The size.
    /// \return This request for chaining.
    T& set_qr_size(int size) {
        impl.set_qr_size(size);
        return dynamic_cast<T&>(*this);
    }

    /// \brief Sets the request to include the wallet with the player.
    /// \return This request for chaining.
    T& set_with_wallet() {
        impl.set_with_wallet();
        return dynamic_cast<T&>(*this);
    }

    bool operator==(const PlayerFragmentArguments& rhs) const {
        return impl == rhs.impl;
    }

    bool operator!=(const PlayerFragmentArguments& rhs) const {
        return rhs != *this;
    }

protected:
    /// \brief Default constructor.
    PlayerFragmentArguments() = default;

private:
    PlayerFragmentArgumentsImpl impl;
};

}

#endif //ENJINCPPSDK_SHAREDPLAYERFRAGMENTARGUMENTS_HPP
