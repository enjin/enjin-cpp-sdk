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

    /// Sets the asset ID to melt.
    /// \param id The ID.
    /// \return This input for chaining.
    Melt& set_asset_id(const std::string& id);

    /// Sets the index of a non-fungible asset to melt.
    /// \param index The index.
    /// \return This input for chaining.
    Melt& set_asset_index(const std::string& index);

    /// Sets the amount of assets to melt.
    /// \param value The amount.
    /// \return This input for chaining.
    Melt& set_value(const std::string& value);

    bool operator==(const Melt& rhs) const;

    bool operator!=(const Melt& rhs) const;

private:
    std::optional<std::string> asset_id;
    std::optional<std::string> asset_index;
    std::optional<std::string> value;

    constexpr static char ASSET_ID_KEY[] = "assetId";
    constexpr static char ASSET_INDEX_KEY[] = "assetIndex";
    constexpr static char VALUE_KEY[] = "value";
};

}

#endif //ENJINCPPSDK_MELT_HPP
