#ifndef ENJINCPPSDK_ASSETCONFIGDATA_HPP
#define ENJINCPPSDK_ASSETCONFIGDATA_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/models/AssetTransferFeeSettings.hpp"
#include "enjinsdk/models/AssetTransferable.hpp"
#include "enjinsdk/serialization/IDeserializable.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::models {

/// \brief Models the configuration data of a asset.
class ENJINSDK_EXPORT AssetConfigData : public enjin::sdk::serialization::IDeserializable {
public:
    /// \brief Default constructor.
    AssetConfigData() = default;

    ~AssetConfigData() override = default;

    void deserialize(const std::string& json) override;

    /// \brief Returns the melt fee ratio of the asset this config belongs too.
    /// \return The ratio.
    /// \remarks The ratio is in the range of 0-10000 to allow for fractional ratios. e.g. 1 = 0.01%, 10000 = 100%,
    /// ect...
    [[nodiscard]] const std::optional<int>& get_melt_fee_ratio() const;

    /// \brief Returns the max melt fee ratio of the asset this config belongs too.
    /// \return The ratio.
    /// \remarks The ratio is in the range of 0-10000 to allow for fractional ratios. e.g. 1 = 0.01%, 10000 = 100%,
    /// ect...
    [[nodiscard]] const std::optional<int>& get_melt_fee_max_ratio() const;

    /// \brief Returns the melt value for the asset this config belongs to. This value corresponds to its exchange rate.
    /// \return The melt value.
    [[nodiscard]] const std::optional<std::string>& get_melt_value() const;

    /// \brief Returns the URI for the metadata of the asset this config belongs to.
    /// \return The URI.
    [[nodiscard]] const std::optional<std::string>& get_metadata_uri() const;

    /// \brief Returns the transferable type of the asset this config belongs to.
    /// \return The transferable type.
    [[nodiscard]] const std::optional<AssetTransferable>& get_transferable() const;

    /// \brief Returns the transfer fee settings for the asset this config belongs to.
    /// \return The transfer fee settings.
    [[nodiscard]] const std::optional<AssetTransferFeeSettings>& get_transfer_fee_settings() const;

    bool operator==(const AssetConfigData& rhs) const;

    bool operator!=(const AssetConfigData& rhs) const;

private:
    std::optional<int> melt_fee_ratio;
    std::optional<int> melt_fee_max_ratio;
    std::optional<std::string> melt_value;
    std::optional<std::string> metadata_uri;
    std::optional<AssetTransferable> transferable;
    std::optional<AssetTransferFeeSettings> transfer_fee_settings;

    constexpr static char MELT_FEE_RATIO_KEY[] = "meltFeeRatio";
    constexpr static char MELT_FEE_MAX_RATIO_KEY[] = "meltFeeMaxRatio";
    constexpr static char MELT_VALUE_KEY[] = "meltValue";
    constexpr static char METADATA_URI_KEY[] = "metadataURI";
    constexpr static char TRANSFERABLE_KEY[] = "transferable";
    constexpr static char TRANSFER_FEE_SETTINGS_KEY[] = "transferFeeSettings";
};

}

#endif //ENJINCPPSDK_ASSETCONFIGDATA_HPP
