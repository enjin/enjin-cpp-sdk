#ifndef ENJINCPPSDK_TRANSACTIONEVENT_HPP
#define ENJINCPPSDK_TRANSACTIONEVENT_HPP

#include "enjinsdk/serialization/IDeserializable.hpp"
#include <optional>
#include <string>
#include <vector>

namespace enjin::sdk::models {

/// \brief Models a blockchain transaction event.
class TransactionEvent : enjin::sdk::serialization::IDeserializable {
public:
    /// \brief Default constructor.
    TransactionEvent() = default;

    void deserialize(const std::string& json) override;

    /// \brief Returns the name of this event.
    /// \return The name.
    [[nodiscard]] const std::optional<std::string>& get_name() const;

    /// \brief Returns the serialized parameters for this event.
    /// \return The parameters.
    [[nodiscard]] const std::optional<std::vector<std::string>>& get_inputs() const;

    /// \brief Returns the serialized non-indexed parameters for this event.
    /// \return The non-indexed parameters.
    [[nodiscard]] const std::optional<std::vector<std::string>>& get_non_indexed_inputs() const;

    /// \brief Returns the serialized indexed parameters for this event.
    /// \return The indexed parameters.
    [[nodiscard]] const std::optional<std::vector<std::string>>& get_indexed_inputs() const;

    /// \brief Returns the event signature.
    /// \return The signature.
    /// \remarks If the event was anonymous, then the optional will not have a value.
    [[nodiscard]] const std::optional<std::string>& get_signature() const;

    /// \brief Returns the encoded signature.
    /// \return The encoded signature.
    [[nodiscard]] const std::optional<std::string>& get_encoded_signature() const;

    bool operator==(const TransactionEvent& rhs) const;

    bool operator!=(const TransactionEvent& rhs) const;

private:
    std::optional<std::string> name;
    std::optional<std::vector<std::string>> inputs;
    std::optional<std::vector<std::string>> non_indexed_inputs;
    std::optional<std::vector<std::string>> indexed_inputs;
    std::optional<std::string> signature;
    std::optional<std::string> encoded_signature;

    constexpr static char NAME_KEY[] = "name";
    constexpr static char INPUTS_KEY[] = "inputs";
    constexpr static char NON_INDEXED_INPUTS_KEY[] = "nonIndexedInputs";
    constexpr static char INDEXED_INPUTS_KEY[] = "indexedInputs";
    constexpr static char SIGNATURE_KEY[] = "signature";
    constexpr static char ENCODED_SIGNATURE_KEY[] = "encodedSignature";
};

}

#endif //ENJINCPPSDK_TRANSACTIONEVENT_HPP
