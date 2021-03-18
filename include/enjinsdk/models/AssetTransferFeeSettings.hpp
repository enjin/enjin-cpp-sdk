#ifndef ENJINCPPSDK_ASSETTRANSFERFEESETTINGS_HPP
#define ENJINCPPSDK_ASSETTRANSFERFEESETTINGS_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/IDeserializable.hpp"
#include "enjinsdk/ISerializable.hpp"
#include "enjinsdk/models/AssetTransferFeeType.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::models {

/// \brief Models transfer fee settings for an asset.
class ENJINSDK_EXPORT AssetTransferFeeSettings : public serialization::IDeserializable {
public:
    /// \brief Default constructor.
    AssetTransferFeeSettings() = default;

    ~AssetTransferFeeSettings() override = default;

    void deserialize(const std::string& json) override;

    /// \brief Returns the transfer fee type.
    /// \return The transfer type.
    [[nodiscard]] const std::optional<AssetTransferFeeType>& get_type() const;

    /// \brief Returns the asset ID or "0" if ENJ.
    /// \return The asset ID.
    [[nodiscard]] const std::optional<std::string>& get_asset_id() const;

    /// \brief Returns the fee value in Wei.
    /// \return The value.
    [[nodiscard]] const std::optional<std::string>& get_value() const;

    bool operator==(const AssetTransferFeeSettings& rhs) const;

    bool operator!=(const AssetTransferFeeSettings& rhs) const;

protected:
    std::optional<AssetTransferFeeType> type;
    std::optional<std::string> asset_id;
    std::optional<std::string> value;

    constexpr static char TYPE_KEY[] = "type";
    constexpr static char ASSET_ID_KEY[] = "assetId";
    constexpr static char VALUE_KEY[] = "value";
};

/// \brief Models input for the transfer fee settings used in GraphQL requests.
class ENJINSDK_EXPORT AssetTransferFeeSettingsInput : public AssetTransferFeeSettings,
                                                      public serialization::ISerializable {
public:
    /// \brief Default constructor.
    AssetTransferFeeSettingsInput() = default;

    ~AssetTransferFeeSettingsInput() override = default;

    std::string serialize() override;

    /// \brief Sets the transfer type for this input.
    /// \param type The type.
    /// \return This input for chaining.
    AssetTransferFeeSettingsInput& set_type(AssetTransferFeeType type);

    /// \brief Sets the asset ID for this input.
    /// \param asset_id The ID.
    /// \return This input for chaining.
    AssetTransferFeeSettingsInput& set_asset_id(const std::string& asset_id);

    /// \brief Sets the value in Wei for this input.
    /// \param value The value.
    /// \return This input for chaining.
    AssetTransferFeeSettingsInput& set_value(const std::string& value);

    bool operator==(const AssetTransferFeeSettingsInput& rhs) const;

    bool operator!=(const AssetTransferFeeSettingsInput& rhs) const;
};

}

#endif //ENJINCPPSDK_ASSETTRANSFERFEESETTINGS_HPP
