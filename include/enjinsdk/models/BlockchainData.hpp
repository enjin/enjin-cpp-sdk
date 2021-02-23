#ifndef ENJINCPPSDK_BLOCKCHAINDATA_HPP
#define ENJINCPPSDK_BLOCKCHAINDATA_HPP

#include "enjinsdk/models/TransactionReceipt.hpp"
#include "enjinsdk/serialization/IDeserializable.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::models {

/// \brief Models the blockchain data of a request.
class BlockchainData : public enjin::sdk::serialization::IDeserializable {
public:
    /// \brief Default constructor.
    BlockchainData() = default;

    ~BlockchainData() override = default;

    void deserialize(const std::string& json) override;

    /// \brief Returns the encoded data of the request this data container belongs to.
    /// \return The encoded data.
    [[nodiscard]] const std::optional<std::string>& get_encoded_data() const;

    /// \brief Returns the signed string of the request this data container belongs to.
    /// \return The signed string.
    [[nodiscard]] const std::optional<std::string>& get_signed_transaction() const;

    /// \brief Returns the signed backup string of the request this data container belongs to.
    /// \return The signed backup string.
    [[nodiscard]] const std::optional<std::string>& get_signed_backup_transaction() const;

    /// \brief Returns the signed cancel string of the request this data container belongs to.
    /// \return The signed cancel string.
    [[nodiscard]] const std::optional<std::string>& get_signed_cancel_transaction() const;

    /// \brief Returns the receipt of the request this data container belongs to.
    /// \return The receipt.
    [[nodiscard]] const std::optional<TransactionReceipt>& get_receipt() const;

    /// \brief Returns the error message of the request this data container belongs to.
    /// \return The error message.
    [[nodiscard]] const std::optional<std::string>& get_error() const;

    /// \brief Returns the nonce of the request this data container belongs to.
    /// \return The nonce.
    [[nodiscard]] const std::optional<std::string>& get_nonce() const;

    bool operator==(const BlockchainData& rhs) const;

    bool operator!=(const BlockchainData& rhs) const;

private:
    std::optional<std::string> encoded_data;
    std::optional<std::string> signed_transaction;
    std::optional<std::string> signed_backup_transaction;
    std::optional<std::string> signed_cancel_transaction;
    std::optional<TransactionReceipt> receipt;
    std::optional<std::string> error;
    std::optional<std::string> nonce;

    constexpr static char ENCODED_DATA_KEY[] = "encodedData";
    constexpr static char SIGNED_TRANSACTION_KEY[] = "signedTransaction";
    constexpr static char SIGNED_BACKUP_TRANSACTION_KEY[] = "signedBackupTransaction";
    constexpr static char SIGNED_CANCEL_TRANSACTION_KEY[] = "signedCancelTransaction";
    constexpr static char RECEIPT_KEY[] = "receipt";
    constexpr static char ERROR_KEY[] = "error";
    constexpr static char NONCE_KEY[] = "nonce";
};

}

#endif //ENJINCPPSDK_BLOCKCHAINDATA_HPP
