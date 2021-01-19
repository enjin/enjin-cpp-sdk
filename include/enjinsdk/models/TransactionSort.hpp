#ifndef ENJINCPPSDK_TRANSACTIONSORT_HPP
#define ENJINCPPSDK_TRANSACTIONSORT_HPP

#include "enjinsdk/models/SortDirection.hpp"
#include "enjinsdk/models/TransactionField.hpp"
#include "enjinsdk/serialization/ISerializable.hpp"
#include <optional>

namespace enjin::sdk::models {

/// \brief Models sorting input for Transactions (Requests).
class TransactionSort : public enjin::sdk::serialization::ISerializable {
public:
    /// \brief Default constructor.
    TransactionSort() = default;

    std::string serialize() override;

    /// \brief Sets the field to sort by.
    /// \param field The field.
    /// \return This input for chaining.
    TransactionSort& set_field(TransactionField field);

    /// \brief Sets the direction to sort by.
    /// \param direction The direction.
    /// \return This input for chaining.
    TransactionSort& set_direction(SortDirection direction);

    bool operator==(const TransactionSort& rhs) const;

    bool operator!=(const TransactionSort& rhs) const;

private:
    std::optional<TransactionField> field;
    std::optional<SortDirection> direction;

    constexpr static char FIELD_KEY[] = "field";
    constexpr static char DIRECTION_KEY[] = "direction";
};

}

#endif //ENJINCPPSDK_TRANSACTIONSORT_HPP
