#ifndef ENJINCPPSDK_SHAREDBALANCEFRAGMENTARGUMENTS_HPP
#define ENJINCPPSDK_SHAREDBALANCEFRAGMENTARGUMENTS_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/ISerializable.hpp"
#include "enjinsdk/internal/BalanceFragmentArgumentsImpl.hpp"
#include "enjinsdk/models/AssetIdFormat.hpp"
#include "enjinsdk/models/AssetIndexFormat.hpp"

namespace enjin::sdk::shared {

/// \brief Fragment interface used to request certain information from balances returned by the platform.
/// \tparam T The type of the implementing class.
template<class T>
class ENJINSDK_EXPORT BalanceFragmentArguments : public serialization::ISerializable {
public:
    ~BalanceFragmentArguments() override = default;

    [[nodiscard]] std::string serialize() const override {
        return impl.serialize();
    }

    /// \brief Sets the desired asset ID format.
    /// \param bal_id_format The ID format.
    /// \return This request for chaining.
    T& set_bal_id_format(models::AssetIdFormat bal_id_format) {
        impl.set_bal_id_format(bal_id_format);
        return dynamic_cast<T&>(*this);
    }

    /// \brief Sets the desired index format for non-fungible assets.
    /// \param bal_index_format The index format.
    /// \return This request for chaining.
    T& set_bal_index_format(models::AssetIndexFormat bal_index_format) {
        impl.set_bal_index_format(bal_index_format);
        return dynamic_cast<T&>(*this);
    }

    /// \brief Sets the request to include the project ID with the balance.
    /// \return This request for chaining.
    T& set_with_bal_project_id() {
        impl.set_with_bal_project_id();
        return dynamic_cast<T&>(*this);
    }

    /// \brief Sets the request to include the wallet address with balance.
    /// \return This request for chaining.
    T& set_with_bal_wallet_address() {
        impl.set_with_bal_wallet_address();
        return dynamic_cast<T&>(*this);
    }

    bool operator==(const BalanceFragmentArguments& rhs) const {
        return impl == rhs.impl;
    }

    bool operator!=(const BalanceFragmentArguments& rhs) const {
        return rhs != *this;
    }

protected:
    /// \brief Default constructor.
    BalanceFragmentArguments() = default;

private:
    BalanceFragmentArgumentsImpl impl;
};

}

#endif //ENJINCPPSDK_SHAREDBALANCEFRAGMENTARGUMENTS_HPP
