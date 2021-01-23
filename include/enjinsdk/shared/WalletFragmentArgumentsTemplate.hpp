#ifndef ENJINCPPSDK_WALLETFRAGMENTARGUMENTSTEMPLATE_HPP
#define ENJINCPPSDK_WALLETFRAGMENTARGUMENTSTEMPLATE_HPP

#include "enjinsdk/internal/WalletFragmentArguments.hpp"
#include "enjinsdk/serialization/ISerializable.hpp"

namespace enjin::sdk::shared {

/// \brief Fragment interface used to request certain information from wallets returned by the platform.
/// \tparam T The type of the implementing class.
template<class T>
class WalletFragmentArgumentsTemplate : public serialization::ISerializable {
public:
    /// \brief Default constructor.
    WalletFragmentArgumentsTemplate() = default;

    ~WalletFragmentArgumentsTemplate() override = default;

    std::string serialize() override {
        return std::string();
    }

    /// Sets the request to include the tokens (items) created by the wallet.
    /// \return This request for chaining.
    T& set_with_tokens_created() {
        impl.set_with_tokens_created();
        return dynamic_cast<T&>(*this);
    }

    bool operator==(const WalletFragmentArgumentsTemplate& rhs) const {
        return impl == rhs.impl;
    }

    bool operator!=(const WalletFragmentArgumentsTemplate& rhs) const {
        return rhs != *this;
    }

private:
    WalletFragmentArguments impl;
};

}

#endif //ENJINCPPSDK_WALLETFRAGMENTARGUMENTSTEMPLATE_HPP
