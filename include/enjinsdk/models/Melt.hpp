#ifndef ENJINCPPSDK_MELT_HPP
#define ENJINCPPSDK_MELT_HPP

#include "enjinsdk/serialization/ISerializable.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::models {

/// \brief Models a melt input for melt requests.
class Melt : public enjin::sdk::serialization::ISerializable {
public:
    /// \brief Default constructor.
    Melt() = default;

    std::string serialize() override;

    /// Sets the token (item) ID to melt.
    /// \param id The ID.
    /// \return This input for chaining.
    Melt& set_token_id(const std::string& id);

    /// Sets the token (item) index of a non-fungible item to melt.
    /// \param index The index.
    /// \return This input for chaining.
    Melt& set_token_index(const std::string& index);

    /// Sets the amount of items to melt.
    /// \param value The amount.
    /// \return This input for chaining.
    Melt& set_value(const std::string& value);

    bool operator==(const Melt& rhs) const;

    bool operator!=(const Melt& rhs) const;

private:
    std::optional<std::string> token_id;
    std::optional<std::string> token_index;
    std::optional<std::string> value;

    constexpr static char TOKEN_ID_KEY[] = "tokenId";
    constexpr static char TOKEN_INDEX_KEY[] = "tokenIndex";
    constexpr static char VALUE_KEY[] = "value";
};

}

#endif //ENJINCPPSDK_MELT_HPP
