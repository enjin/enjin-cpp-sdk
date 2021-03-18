#ifndef ENJINCPPSDK_TRADE_HPP
#define ENJINCPPSDK_TRADE_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/ISerializable.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::models {

/// \brief Models a trade input for trade requests.
class ENJINSDK_EXPORT Trade : public serialization::ISerializable {
public:
    /// \brief Default constructor.
    Trade() = default;

    ~Trade() override = default;

    std::string serialize() override;

    /// Sets the asset ID to trade or ENJ if unused.
    /// \param id The ID.
    /// \return This input for chaining.
    Trade& set_asset_id(const std::string& id);

    /// Sets the index for non-fungible assets.
    /// \param index The index.
    /// \return This input for chaining.
    Trade& set_asset_index(const std::string& index);

    /// Sets the amount of assets to trade.
    /// \param value The amount.
    /// \return This input for chaining.
    Trade& set_value(const std::string& value);

    bool operator==(const Trade& rhs) const;

    bool operator!=(const Trade& rhs) const;

private:
    std::optional<std::string> asset_id;
    std::optional<std::string> asset_index;
    std::optional<std::string> value;

    constexpr static char ASSET_ID_KEY[] = "assetId";
    constexpr static char ASSET_INDEX_KEY[] = "assetIndex";
    constexpr static char VALUE_KEY[] = "value";
};

}

#endif //ENJINCPPSDK_TRADE_HPP
