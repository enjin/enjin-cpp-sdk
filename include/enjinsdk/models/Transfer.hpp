#ifndef ENJINCPPSDK_TRANSFER_HPP
#define ENJINCPPSDK_TRANSFER_HPP

#include "enjinsdk/serialization/ISerializable.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::models {

/// \brief Models a transfer input for transfer requests.
class Transfer : public enjin::sdk::serialization::ISerializable {
public:
    /// \brief Default constructor.
    Transfer() = default;

    std::string serialize() override;

    /// Sets the source Ethereum address.
    /// \param address The source.
    /// \return This input for chaining.
    Transfer& set_from(const std::string& address);

    /// Sets the destination Ethereum address.
    /// \param address The destination.
    /// \return This input for chaining.
    Transfer& set_to(const std::string& address);

    /// Sets the token (item) ID to transfer or ENJ is unused.
    /// \param id The ID.
    /// \return This input for chaining.
    Transfer& set_token_id(const std::string& id);

    /// Sets the index for non-fungible tokens (items).
    /// \param index The index.
    /// \return This input for chaining.
    Transfer& set_token_index(const std::string& index);

    /// Sets the amount of items to transfer.
    /// \param value The amount.
    /// \return This input for chaining.
    Transfer& set_value(const std::string& value);

    bool operator==(const Transfer& rhs) const;

    bool operator!=(const Transfer& rhs) const;

private:
    std::optional<std::string> from;
    std::optional<std::string> to;
    std::optional<std::string> token_id;
    std::optional<std::string> token_index;
    std::optional<std::string> value;

    constexpr static char FROM_KEY[] = "from";
    constexpr static char TO_KEY[] = "to";
    constexpr static char TOKEN_ID_KEY[] = "tokenId";
    constexpr static char TOKEN_INDEX_KEY[] = "tokenIndex";
    constexpr static char VALUE_KEY[] = "value";
};

}

#endif //ENJINCPPSDK_TRANSFER_HPP
