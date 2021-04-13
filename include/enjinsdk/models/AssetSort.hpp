#ifndef ENJINCPPSDK_ASSETSORT_HPP
#define ENJINCPPSDK_ASSETSORT_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/ISerializable.hpp"
#include "enjinsdk/models/SortDirection.hpp"
#include "enjinsdk/models/AssetField.hpp"
#include <optional>

namespace enjin::sdk::models {

/// \brief Models sorting input for Assets.
class ENJINSDK_EXPORT AssetSort : public serialization::ISerializable {
public:
    /// \brief Default constructor.
    AssetSort() = default;

    ~AssetSort() override = default;

    [[nodiscard]] std::string serialize() const override;

    /// \brief Sets the field to sort by.
    /// \param field The field.
    /// \return This input for chaining.
    AssetSort& set_field(AssetField field);

    /// \brief Sets the direction to sort by.
    /// \param direction The direction.
    /// \return This input for chaining.
    AssetSort& set_direction(SortDirection direction);

    bool operator==(const AssetSort& rhs) const;

    bool operator!=(const AssetSort& rhs) const;

private:
    std::optional<AssetField> field;
    std::optional<SortDirection> direction;

    constexpr static char FIELD_KEY[] = "field";
    constexpr static char DIRECTION_KEY[] = "direction";
};

}

#endif //ENJINCPPSDK_ASSETSORT_HPP
