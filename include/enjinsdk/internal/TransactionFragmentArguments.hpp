#ifndef ENJINCPPSDK_TRANSACTIONFRAGMENTARGUMENTS_HPP
#define ENJINCPPSDK_TRANSACTIONFRAGMENTARGUMENTS_HPP

#include "enjinsdk/serialization/ISerializable.hpp"
#include <optional>

namespace enjin::sdk::shared {

/// \brief Internal implementation class for storing values of a GraphQL Transaction fragment.
class TransactionFragmentArguments : public serialization::ISerializable {
public:
    /// \brief Default constructor.
    TransactionFragmentArguments() = default; // TODO: Consider making this constructor private and friend to its implementing template class.

    ~TransactionFragmentArguments() override = default;

    std::string serialize() override;

    /// \brief Sets the value for the associated field to true.
    void set_with_blockchain_data();

    /// \brief Sets the value for the associated field to true.
    void set_with_meta();

    /// \brief Sets the value for the associated field to true.
    void set_with_encoded_data();

    /// \brief Sets the value for the associated field to true.
    void set_with_token_data();

    /// \brief Sets the value for the associated field to true.
    void set_with_signed_txs();

    /// \brief Sets the value for the associated field to true.
    void set_with_error();

    /// \brief Sets the value for the associated field to true.
    void set_with_nonce();

    /// \brief Sets the value for the associated field to true.
    void set_with_state();

    /// \brief Sets the value for the associated field to true.
    void set_with_receipt();

    /// \brief Sets the value for the associated field to true.
    void set_with_receipt_logs();

    /// \brief Sets the value for the associated field to true.
    void set_with_log_event();

    bool operator==(const TransactionFragmentArguments& rhs) const;

    bool operator!=(const TransactionFragmentArguments& rhs) const;

private:
    std::optional<bool> with_blockchain_data;
    std::optional<bool> with_meta;
    std::optional<bool> with_encoded_data;
    std::optional<bool> with_token_data;
    std::optional<bool> with_signed_txs;
    std::optional<bool> with_error;
    std::optional<bool> with_nonce;
    std::optional<bool> with_state;
    std::optional<bool> with_receipt;
    std::optional<bool> with_receipt_logs;
    std::optional<bool> with_log_event;
};

}

#endif //ENJINCPPSDK_TRANSACTIONFRAGMENTARGUMENTS_HPP
