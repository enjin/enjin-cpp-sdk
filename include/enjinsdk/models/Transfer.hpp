#ifndef ENJINCPPSDK_TRANSFER_HPP
#define ENJINCPPSDK_TRANSFER_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/ISerializable.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::models {

/// \brief Models a transfer input for transfer requests.
class ENJINSDK_EXPORT Transfer : public serialization::ISerializable {
public:
    /// \brief Default constructor.
    Transfer() = default;

    ~Transfer() override = default;

    std::string serialize() override;

    /// Sets the source Ethereum address.
    /// \param address The source.
    /// \return This input for chaining.
    Transfer& set_from(const std::string& address);

    /// Sets the destination Ethereum address.
    /// \param address The destination.
    /// \return This input for chaining.
    Transfer& set_to(const std::string& address);

    /// Sets the asset ID to transfer or ENJ if unused.
    /// \param id The ID.
    /// \return This input for chaining.
    Transfer& set_asset_id(const std::string& id);

    /// Sets the index for non-fungible assets.
    /// \param index The index.
    /// \return This input for chaining.
    Transfer& set_asset_index(const std::string& index);

    /// Sets the amount of assets to transfer.
    /// \param value The amount.
    /// \return This input for chaining.
    Transfer& set_value(const std::string& value);

    bool operator==(const Transfer& rhs) const;

    bool operator!=(const Transfer& rhs) const;

private:
    std::optional<std::string> from;
    std::optional<std::string> to;
    std::optional<std::string> asset_id;
    std::optional<std::string> asset_index;
    std::optional<std::string> value;

    constexpr static char FROM_KEY[] = "from";
    constexpr static char TO_KEY[] = "to";
    constexpr static char ASSET_ID_KEY[] = "assetId";
    constexpr static char ASSET_INDEX_KEY[] = "assetIndex";
    constexpr static char VALUE_KEY[] = "value";
};

}

#endif //ENJINCPPSDK_TRANSFER_HPP
