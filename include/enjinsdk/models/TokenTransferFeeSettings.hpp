#ifndef ENJINCPPSDK_TOKENTRANSFERFEESETTINGS_HPP
#define ENJINCPPSDK_TOKENTRANSFERFEESETTINGS_HPP

#include "enjinsdk/models/TokenTransferFeeType.hpp"
#include "enjinsdk/serialization/IDeserializable.hpp"
#include "enjinsdk/serialization/ISerializable.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::models {

/// \brief Models transfer fee settings for an item.
class TokenTransferFeeSettings : public enjin::sdk::serialization::IDeserializable {
public:
    /// \brief Default constructor.
    TokenTransferFeeSettings() = default;

    void deserialize(const std::string& json) override;

    /// \brief Returns the transfer fee type.
    /// \return The transfer type.
    [[nodiscard]] const std::optional<TokenTransferFeeType>& get_type() const;

    /// \brief Returns the token (item) ID or "0" if ENJ.
    /// \return The item ID.
    [[nodiscard]] const std::optional<std::string>& get_token_id() const;

    /// \brief Returns the fee value in Wei.
    /// \return The value.
    [[nodiscard]] const std::optional<std::string>& get_value() const;

    bool operator==(const TokenTransferFeeSettings& rhs) const;

    bool operator!=(const TokenTransferFeeSettings& rhs) const;

protected:
    std::optional<TokenTransferFeeType> type;
    std::optional<std::string> token_id;
    std::optional<std::string> value;

    constexpr static char TYPE_KEY[] = "type";
    constexpr static char TOKEN_ID_KEY[] = "tokenId";
    constexpr static char VALUE_KEY[] = "value";
};

/// \brief Models input for the transfer fee settings used in GraphQL requests.
class TokenTransferFeeSettingsInput : public TokenTransferFeeSettings,
                                      public serialization::ISerializable {
public:
    /// \brief Default constructor.
    TokenTransferFeeSettingsInput() = default;

    ~TokenTransferFeeSettingsInput() override = default;

    std::string serialize() override;

    /// \brief Sets the transfer type for this input.
    /// \param type The type.
    /// \return This input for chaining.
    TokenTransferFeeSettingsInput& set_type(TokenTransferFeeType type);

    /// \brief Sets the token ID for this input.
    /// \param token_id The ID.
    /// \return This input for chaining.
    TokenTransferFeeSettingsInput& set_token_id(const std::string& token_id);

    /// \brief Sets the value in Wei for this input.
    /// \param value The value.
    /// \return This input for chaining.
    TokenTransferFeeSettingsInput& set_value(const std::string& value);

    bool operator==(const TokenTransferFeeSettingsInput& rhs) const;

    bool operator!=(const TokenTransferFeeSettingsInput& rhs) const;
};

}

#endif //ENJINCPPSDK_TOKENTRANSFERFEESETTINGS_HPP
