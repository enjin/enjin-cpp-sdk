#ifndef ENJINCPPSDK_SHAREDTRANSACTIONFRAGMENTARGUMENTSIMPL_HPP
#define ENJINCPPSDK_SHAREDTRANSACTIONFRAGMENTARGUMENTSIMPL_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/ISerializable.hpp"
#include <optional>

namespace enjin::sdk::shared {

/// \brief Internal implementation class for storing values of a GraphQL Transaction fragment.
class ENJINSDK_EXPORT TransactionFragmentArgumentsImpl : public serialization::ISerializable {
public:
    /// \brief Default constructor to be used internally.
    TransactionFragmentArgumentsImpl() = default;

    ~TransactionFragmentArgumentsImpl() override = default;

    std::string serialize() override;

    /// \brief Sets the value for the associated field to true.
    void set_with_blockchain_data();

    /// \brief Sets the value for the associated field to true.
    void set_with_meta();

    /// \brief Sets the value for the associated field to true.
    void set_with_encoded_data();

    /// \brief Sets the value for the associated field to true.
    void set_with_asset_data();

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

    bool operator==(const TransactionFragmentArgumentsImpl& rhs) const;

    bool operator!=(const TransactionFragmentArgumentsImpl& rhs) const;

private:
    std::optional<bool> with_blockchain_data;
    std::optional<bool> with_meta;
    std::optional<bool> with_encoded_data;
    std::optional<bool> with_asset_data;
    std::optional<bool> with_signed_txs;
    std::optional<bool> with_error;
    std::optional<bool> with_nonce;
    std::optional<bool> with_state;
    std::optional<bool> with_receipt;
    std::optional<bool> with_receipt_logs;
    std::optional<bool> with_log_event;
};

}

#endif //ENJINCPPSDK_SHAREDTRANSACTIONFRAGMENTARGUMENTSIMPL_HPP