#ifndef ENJINCPPSDK_TOKENVARIANT_HPP
#define ENJINCPPSDK_TOKENVARIANT_HPP

#include "enjinsdk/serialization/IDeserializable.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::models {

/// \brief Models a token variant.
class TokenVariant : public enjin::sdk::serialization::IDeserializable {
public:
    void deserialize(const std::string& json) override;

    /// \brief Returns the ID of this variant.
    /// \return The ID.
    [[nodiscard]] const std::optional<int>& get_id() const;

    /// \brief Returns the the ID of the token this variant belongs to.
    /// \return The token ID.
    [[nodiscard]] const std::optional<std::string>& get_token_id() const;

    /// \brief Returns the metadata of this variant.
    /// \return The metadata.
    [[nodiscard]] const std::optional<std::string>& get_variant_metadata() const;

    /// \brief Returns the usage count of this variant.
    /// \return The usage count.
    [[nodiscard]] const std::optional<int>& get_usage_count() const;

    /// \brief Returns the datetime when this variant was created.
    /// \return The datetime.
    /// \remarks The datetime is formatted using the ISO 8601 date format.
    [[nodiscard]] const std::optional<std::string>& get_created_at() const;

    /// \brief Returns the datetime when this variant was last updated.
    /// \return The datetime.
    /// \remarks The datetime is formatted using the ISO 8601 date format.
    [[nodiscard]] const std::optional<std::string>& get_updated_at() const;

private:
    std::optional<int> id;
    std::optional<std::string> token_id;
    std::optional<std::string> variant_metadata;
    std::optional<int> usage_count;
    std::optional<std::string> created_at;
    std::optional<std::string> updated_at;

    constexpr static char ID_KEY[] = "id";
    constexpr static char TOKEN_ID_KEY[] = "tokenId";
    constexpr static char VARIANT_METADATA_KEY[] = "variantMetadata";
    constexpr static char USAGE_COUNT_KEY[] = "usageCount";
    constexpr static char CREATED_AT_KEY[] = "createdAt";
    constexpr static char UPDATED_AT_KEY[] = "updatedAt";
};

}

#endif //ENJINCPPSDK_TOKENVARIANT_HPP
