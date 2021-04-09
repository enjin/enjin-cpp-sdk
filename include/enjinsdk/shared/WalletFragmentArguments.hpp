#ifndef ENJINCPPSDK_SHAREDWALLETFRAGMENTARGUMENTS_HPP
#define ENJINCPPSDK_SHAREDWALLETFRAGMENTARGUMENTS_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/ISerializable.hpp"
#include "enjinsdk/internal/WalletFragmentArgumentsImpl.hpp"

namespace enjin::sdk::shared {

/// \brief Fragment interface used to request certain information from wallets returned by the platform.
/// \tparam T The type of the implementing class.
template<class T>
class ENJINSDK_EXPORT WalletFragmentArguments : public serialization::ISerializable {
public:
    ~WalletFragmentArguments() override = default;

    std::string serialize() override {
        return impl.serialize();
    }

    /// Sets the request to include the assets created by the wallet.
    /// \return This request for chaining.
    T& set_with_assets_created() {
        impl.set_with_assets_created();
        return dynamic_cast<T&>(*this);
    }

    bool operator==(const WalletFragmentArguments& rhs) const {
        return impl == rhs.impl;
    }

    bool operator!=(const WalletFragmentArguments& rhs) const {
        return rhs != *this;
    }

protected:
    /// \brief Default constructor.
    WalletFragmentArguments() = default;

private:
    WalletFragmentArgumentsImpl impl;
};

}

#endif //ENJINCPPSDK_SHAREDWALLETFRAGMENTARGUMENTS_HPP
