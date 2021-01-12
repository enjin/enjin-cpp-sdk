#ifndef ENJINCPPSDK_TOKENTRANSFERFEESETTINGS_HPP
#define ENJINCPPSDK_TOKENTRANSFERFEESETTINGS_HPP

#include "enjinsdk/models/TokenTransferFeeType.hpp"
#include "enjinsdk/serialization/IDeserializable.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::models {

/// \brief Models transfer fee settings for an item.
class TokenTransferFeeSettings : public enjin::sdk::serialization::IDeserializable {
public:
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

private:
    std::optional<TokenTransferFeeType> type;
    std::optional<std::string> token_id;
    std::optional<std::string> value;

    constexpr static char TYPE_KEY[] = "type";
    constexpr static char TOKEN_ID_KEY[] = "tokenId";
    constexpr static char VALUE_KEY[] = "value";
};

}

#endif //ENJINCPPSDK_TOKENTRANSFERFEESETTINGS_HPP
