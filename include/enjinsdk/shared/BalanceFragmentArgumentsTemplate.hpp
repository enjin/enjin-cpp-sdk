#ifndef ENJINCPPSDK_BALANCEFRAGMENTARGUMENTSTEMPLATE_HPP
#define ENJINCPPSDK_BALANCEFRAGMENTARGUMENTSTEMPLATE_HPP

#include "enjinsdk/internal/BalanceFragmentArguments.hpp"
#include "enjinsdk/models/TokenIdFormat.hpp"
#include "enjinsdk/models/TokenIndexFormat.hpp"
#include "enjinsdk/serialization/ISerializable.hpp"

namespace enjin::sdk::shared {

/// \brief Fragment interface used to request certain information from balances returned by the platform.
/// \tparam T The type of the implementing class.
template<class T>
class BalanceFragmentArgumentsTemplate : public serialization::ISerializable {
public:
    /// \brief Default constructor.
    BalanceFragmentArgumentsTemplate() = default;

    ~BalanceFragmentArgumentsTemplate() override = default;

    std::string serialize() override {
        return impl.serialize();
    }

    /// \brief Sets the desired token (item) ID format.
    /// \param bal_id_format The ID format.
    /// \return This request for chaining.
    T& set_bal_id_format(models::TokenIdFormat bal_id_format) {
        impl.set_bal_id_format(bal_id_format);
        return dynamic_cast<T&>(*this);
    }

    /// \brief Sets the desired index format for non-fungible tokens (items).
    /// \param bal_index_format The index format.
    /// \return This request for chaining.
    T& set_bal_index_format(models::TokenIndexFormat bal_index_format) {
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

    bool operator==(const BalanceFragmentArgumentsTemplate& rhs) const {
        return impl == rhs.impl;
    }

    bool operator!=(const BalanceFragmentArgumentsTemplate& rhs) const {
        return rhs != *this;
    }

private:
    BalanceFragmentArguments impl;
};

}

#endif //ENJINCPPSDK_BALANCEFRAGMENTARGUMENTSTEMPLATE_HPP
