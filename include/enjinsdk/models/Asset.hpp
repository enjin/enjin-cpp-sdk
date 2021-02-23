#ifndef ENJINCPPSDK_ASSET_HPP
#define ENJINCPPSDK_ASSET_HPP

#include "enjinsdk/models/AssetConfigData.hpp"
#include "enjinsdk/models/AssetStateData.hpp"
#include "enjinsdk/models/AssetVariant.hpp"
#include "enjinsdk/models/AssetVariantMode.hpp"
#include "enjinsdk/serialization/IDeserializable.hpp"
#include <optional>
#include <string>
#include <vector>

namespace enjin::sdk::models {

/// \brief Models a asset on the platform.
class Asset : public enjin::sdk::serialization::IDeserializable {
public:
    /// \brief Default constructor.
    Asset() = default;

    void deserialize(const std::string& json) override;

    /// \brief Returns the ID of this asset.
    /// \return The ID.
    [[nodiscard]] const std::optional<std::string>& get_id() const;

    /// \brief Returns the name of this asset.
    /// \return The name.
    [[nodiscard]] const std::optional<std::string>& get_name() const;

    /// \brief Returns the state data of this asset.
    /// \return The state data.
    [[nodiscard]] const std::optional<AssetStateData>& get_state_data() const;

    /// \brief Returns the configuration data of this asset.
    /// \return The configuration data.
    [[nodiscard]] const std::optional<AssetConfigData>& get_config_data() const;

    /// \brief Returns the asset variant mode of this asset.
    /// \return The variant mode.
    [[nodiscard]] const std::optional<AssetVariantMode>& get_variant_mode() const;

    /// \brief Returns the asset variants of this asset.
    /// \return The variants.
    [[nodiscard]] const std::optional<std::vector<AssetVariant>>& get_variants() const;

    /// \brief Returns the datetime when this asset was created.
    /// \return The datetime.
    /// \remarks The datetime is formatted using the ISO 8601 date format.
    [[nodiscard]] const std::optional<std::string>& get_created_at() const;

    /// \brief Returns the datetime when this asset was last updated.
    /// \return The datetime.
    /// \remarks The datetime is formatted using the ISO 8601 date format.
    [[nodiscard]] const std::optional<std::string>& get_updated_at() const;

    bool operator==(const Asset& rhs) const;

    bool operator!=(const Asset& rhs) const;

private:
    std::optional<std::string> id;
    std::optional<std::string> name;
    std::optional<AssetStateData> state_data;
    std::optional<AssetConfigData> config_data;
    std::optional<AssetVariantMode> variant_mode;
    std::optional<std::vector<AssetVariant>> variants;
    std::optional<std::string> created_at;
    std::optional<std::string> updated_at;

    constexpr static char ID_KEY[] = "id";
    constexpr static char NAME_KEY[] = "name";
    constexpr static char STATE_DATA_KEY[] = "stateData";
    constexpr static char CONFIG_DATA_KEY[] = "configData";
    constexpr static char VARIANT_MODE_KEY[] = "variantMode";
    constexpr static char VARIANTS_KEY[] = "variants";
    constexpr static char CREATED_AT_KEY[] = "createdAt";
    constexpr static char UPDATED_AT_KEY[] = "updatedAt";
};

}

#endif //ENJINCPPSDK_ASSET_HPP
