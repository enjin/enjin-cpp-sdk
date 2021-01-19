#ifndef ENJINCPPSDK_TOKENSORT_HPP
#define ENJINCPPSDK_TOKENSORT_HPP

#include "enjinsdk/models/SortDirection.hpp"
#include "enjinsdk/models/TokenField.hpp"
#include "enjinsdk/serialization/ISerializable.hpp"
#include <optional>

namespace enjin::sdk::models {

/// \brief Models sorting input for Tokens (items).
class TokenSort : public enjin::sdk::serialization::ISerializable {
public:
    /// \brief Default constructor.
    TokenSort() = default;

    std::string serialize() override;

    /// \brief Sets the field to sort by.
    /// \param field The field.
    /// \return This input for chaining.
    TokenSort& set_field(TokenField field);

    /// \brief Sets the direction to sort by.
    /// \param direction The direction.
    /// \return This input for chaining.
    TokenSort& set_direction(SortDirection direction);

    bool operator==(const TokenSort& rhs) const;

    bool operator!=(const TokenSort& rhs) const;

private:
    std::optional<TokenField> field;
    std::optional<SortDirection> direction;

    constexpr static char FIELD_KEY[] = "field";
    constexpr static char DIRECTION_KEY[] = "direction";
};

}

#endif //ENJINCPPSDK_TOKENSORT_HPP
