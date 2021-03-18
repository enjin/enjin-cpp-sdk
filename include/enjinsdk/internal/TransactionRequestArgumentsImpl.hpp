#ifndef ENJINCPPSDK_SHAREDTRANSACTIONREQUESTARGUMENTSIMPL_HPP
#define ENJINCPPSDK_SHAREDTRANSACTIONREQUESTARGUMENTSIMPL_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/ISerializable.hpp"
#include "enjinsdk/internal/TransactionFragmentArgumentsImpl.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::shared {

/// \brief Internal implementation class for storing values of a GraphQL Transaction request.
class ENJINSDK_EXPORT TransactionRequestArgumentsImpl : public TransactionFragmentArgumentsImpl {
public:
    /// \brief Default constructor.
    TransactionRequestArgumentsImpl() = default;

    ~TransactionRequestArgumentsImpl() override = default;

    std::string serialize() override;

    /// \brief Sets the value for the associated field to the given string.
    /// \param address The address.
    void set_eth_address(const std::string& address);

    /// \brief Sets the value for the associated field to the given boolean.
    /// \param send The send state.
    void set_send(bool send);

    bool operator==(const TransactionRequestArgumentsImpl& rhs) const;

    bool operator!=(const TransactionRequestArgumentsImpl& rhs) const;

private:
    std::optional<std::string> eth_address;
    std::optional<bool> send;
};

}

#endif //ENJINCPPSDK_SHAREDTRANSACTIONREQUESTARGUMENTSIMPL_HPP
