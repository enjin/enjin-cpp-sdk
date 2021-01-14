#ifndef ENJINCPPSDK_TOKEN_HPP
#define ENJINCPPSDK_TOKEN_HPP

#include "enjinsdk/models/TokenConfigData.hpp"
#include "enjinsdk/models/TokenStateData.hpp"
#include "enjinsdk/models/TokenVariant.hpp"
#include "enjinsdk/models/TokenVariantMode.hpp"
#include "enjinsdk/serialization/IDeserializable.hpp"
#include <optional>
#include <string>
#include <vector>

namespace enjin::sdk::models {

/// \brief Models a item on the platform.
class Token : public enjin::sdk::serialization::IDeserializable {
public:
    /// \brief Default constructor.
    Token() = default;

    void deserialize(const std::string& json) override;

    /// \brief Returns the ID of this token.
    /// \return The ID.
    [[nodiscard]] const std::optional<std::string>& get_id() const;

    /// \brief Returns the name of this item.
    /// \return The name.
    [[nodiscard]] const std::optional<std::string>& get_name() const;

    /// \brief Returns the state data of this item.
    /// \return The state data.
    [[nodiscard]] const std::optional<TokenStateData>& get_state_data() const;

    /// \brief Returns the configuration data of this item.
    /// \return The configuration data.
    [[nodiscard]] const std::optional<TokenConfigData>& get_config_data() const;

    /// \brief Returns the token variant mode of this item.
    /// \return The variant mode.
    [[nodiscard]] const std::optional<TokenVariantMode>& get_variant_mode() const;

    /// \brief Returns the token variants of this item.
    /// \return The variants.
    [[nodiscard]] const std::optional<std::vector<TokenVariant>>& get_variants() const;

    /// \brief Returns the datetime when this item was created.
    /// \return The datetime.
    /// \remarks The datetime is formatted using the ISO 8601 date format.
    [[nodiscard]] const std::optional<std::string>& get_created_at() const;

    /// \brief Returns the datetime when this item was last updated.
    /// \return The datetime.
    /// \remarks The datetime is formatted using the ISO 8601 date format.
    [[nodiscard]] const std::optional<std::string>& get_updated_at() const;

    bool operator==(const Token& rhs) const;

    bool operator!=(const Token& rhs) const;

private:
    std::optional<std::string> id;
    std::optional<std::string> name;
    std::optional<TokenStateData> state_data;
    std::optional<TokenConfigData> config_data;
    std::optional<TokenVariantMode> variant_mode;
    std::optional<std::vector<TokenVariant>> variants;
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

#endif //ENJINCPPSDK_TOKEN_HPP
