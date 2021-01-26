#ifndef ENJINCPPSDK_SHAREDPLAYERFRAGMENTARGUMENTSTEMPLATE_HPP
#define ENJINCPPSDK_SHAREDPLAYERFRAGMENTARGUMENTSTEMPLATE_HPP

#include "enjinsdk/internal/PlayerFragmentArguments.hpp"
#include "enjinsdk/serialization/ISerializable.hpp"

namespace enjin::sdk::shared {

/// \brief Fragment interface used to request certain information from players returned by the platform.
/// \tparam T The type of the implementing class.
template<class T>
class PlayerFragmentArgumentsTemplate : public serialization::ISerializable {
public:
    /// \brief Default constructor.
    PlayerFragmentArgumentsTemplate() = default;

    ~PlayerFragmentArgumentsTemplate() override = default;

    std::string serialize() override {
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

    bool operator==(const PlayerFragmentArgumentsTemplate& rhs) const {
        return impl == rhs.impl;
    }

    bool operator!=(const PlayerFragmentArgumentsTemplate& rhs) const {
        return rhs != *this;
    }

private:
    PlayerFragmentArguments impl;
};

}

#endif //ENJINCPPSDK_SHAREDPLAYERFRAGMENTARGUMENTSTEMPLATE_HPP
