#ifndef ENJINCPPSDK_TRANSACTIONREQUESTARGUMENTS_HPP
#define ENJINCPPSDK_TRANSACTIONREQUESTARGUMENTS_HPP

#include "enjinsdk/serialization/ISerializable.hpp"
#include "enjinsdk/internal/TransactionFragmentArguments.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::shared {

/// \brief Internal implementation class for storing values of a GraphQL Transaction request.
class TransactionRequestArguments : public TransactionFragmentArguments {
public:
    /// \brief Default constructor.
    TransactionRequestArguments() = default; // TODO: Consider making this constructor private and friend to its implementing template class.

    ~TransactionRequestArguments() override = default;

    std::string serialize() override;

    /// \brief Sets the value for the associated field to the given string.
    /// \param address The address.
    void set_eth_address(const std::string& address);

    /// \brief Sets the value for the associated field to the given boolean.
    /// \param test The test state.
    void set_test(bool test);

    /// \brief Sets the value for the associated field to the given boolean.
    /// \param send The send state.
    void set_send(bool send);

    bool operator==(const TransactionRequestArguments& rhs) const;

    bool operator!=(const TransactionRequestArguments& rhs) const;

private:
    std::optional<std::string> eth_address;
    std::optional<bool> test;
    std::optional<bool> send;
};

}

#endif //ENJINCPPSDK_TRANSACTIONREQUESTARGUMENTS_HPP
