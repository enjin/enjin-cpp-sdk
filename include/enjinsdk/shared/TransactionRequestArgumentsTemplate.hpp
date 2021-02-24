#ifndef ENJINCPPSDK_SHAREDTRANSACTIONREQUESTARGUMENTSTEMPLATE_HPP
#define ENJINCPPSDK_SHAREDTRANSACTIONREQUESTARGUMENTSTEMPLATE_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/internal/TransactionRequestArguments.hpp"
#include "enjinsdk/shared/TransactionFragmentArgumentsTemplate.hpp"
#include <string>

namespace enjin::sdk::shared {

/// \brief Interface used to set common arguments used in transaction requests.
/// \tparam T The type of the implementing class.
template<class T>
class ENJINSDK_EXPORT TransactionRequestArgumentsTemplate : public TransactionFragmentArgumentsTemplate<T> {
public:
    ~TransactionRequestArgumentsTemplate() override = default;

    std::string serialize() override {
        return impl.serialize();
    }

    /// \brief Sets the Ethereum address of the sender.
    /// \param address The address.
    /// \return The request for chaining.
    T& set_eth_address(const std::string& address) {
        impl.set_eth_address(address);
        return dynamic_cast<T&>(*this);
    }

    /// \brief Sets whether the request will send the transaction to the blockchain.
    /// \param send The send state.
    /// \return This request for chaining.
    T& set_send(bool send) {
        impl.set_send(send);
        return dynamic_cast<T&>(*this);
    }

protected:
    /// \brief Default constructor.
    TransactionRequestArgumentsTemplate() = default;

private:
    TransactionRequestArguments impl;
};

}

#endif //ENJINCPPSDK_SHAREDTRANSACTIONREQUESTARGUMENTSTEMPLATE_HPP
