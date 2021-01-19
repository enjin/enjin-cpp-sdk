#ifndef ENJINCPPSDK_TRADE_HPP
#define ENJINCPPSDK_TRADE_HPP

#include "enjinsdk/serialization/ISerializable.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::models {

/// \brief Models a trade input for trade requests.
class Trade : public enjin::sdk::serialization::ISerializable {
public:
    /// \brief Default constructor.
    Trade() = default;

    std::string serialize() override;

    /// Sets the token (item) ID to trade or ENJ if unused.
    /// \param id The ID.
    /// \return This input for chaining.
    Trade& set_token_id(const std::string& id);

    /// Sets the index for non-fungible tokens (items).
    /// \param index The index.
    /// \return This input for chaining.
    Trade& set_token_index(const std::string& index);

    /// Sets the amount of items to trade.
    /// \param value The amount.
    /// \return This input for chaining.
    Trade& set_value(const std::string& value);

    bool operator==(const Trade& rhs) const;

    bool operator!=(const Trade& rhs) const;

private:
    std::optional<std::string> token_id;
    std::optional<std::string> token_index;
    std::optional<std::string> value;

    constexpr static char TOKEN_ID_KEY[] = "tokenId";
    constexpr static char TOKEN_INDEX_KEY[] = "tokenIndex";
    constexpr static char VALUE_KEY[] = "value";
};

}

#endif //ENJINCPPSDK_TRADE_HPP
