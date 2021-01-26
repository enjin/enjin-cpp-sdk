#ifndef ENJINCPPSDK_SHAREDTOKENFRAGMENTARGUMENTS_HPP
#define ENJINCPPSDK_SHAREDTOKENFRAGMENTARGUMENTS_HPP

#include "enjinsdk/models/TokenIdFormat.hpp"
#include "enjinsdk/serialization/ISerializable.hpp"
#include <optional>

namespace enjin::sdk::shared {

/// \brief Internal implementation class for storing values of a GraphQL Token fragment.
class TokenFragmentArguments : public serialization::ISerializable {
public:
    /// \brief Default constructor.
    TokenFragmentArguments() = default; // TODO: Consider making this constructor private and friend to its implementing template class.

    ~TokenFragmentArguments() override = default;

    std::string serialize() override;

    /// \brief Sets the value for the associated field to the passed value.
    /// \param token_id_format The ID format.
    void set_token_id_format(models::TokenIdFormat token_id_format);

    /// \brief Sets the value for the associated field to true.
    void set_with_state_data();

    /// \brief Sets the value for the associated field to true.
    void set_with_config_data();

    /// \brief Sets the value for the associated field to true.
    void set_with_token_blocks();

    /// \brief Sets the value for the associated field to true.
    void set_with_creator();

    /// \brief Sets the value for the associated field to true.
    void set_with_melt_details();

    /// \brief Sets the value for the associated field to true.
    void set_with_metadata_uri();

    /// \brief Sets the value for the associated field to true.
    void set_with_supply_details();

    /// \brief Sets the value for the associated field to true.
    void set_with_transfer_settings();

    /// \brief Sets the value for the associated field to true.
    void set_with_token_variant_mode();

    /// \brief Sets the value for the associated field to true.
    void set_with_token_variants();

    /// \brief Sets the value for the associated field to true.
    void set_with_variant_metadata();

    bool operator==(const TokenFragmentArguments& rhs) const;

    bool operator!=(const TokenFragmentArguments& rhs) const;

private:
    std::optional<models::TokenIdFormat> token_id_format;
    std::optional<bool> with_state_data;
    std::optional<bool> with_config_data;
    std::optional<bool> with_token_blocks;
    std::optional<bool> with_creator;
    std::optional<bool> with_melt_details;
    std::optional<bool> with_metadata_uri;
    std::optional<bool> with_supply_details;
    std::optional<bool> with_transfer_settings;
    std::optional<bool> with_token_variant_mode;
    std::optional<bool> with_token_variants;
    std::optional<bool> with_variant_metadata;
};

}

#endif //ENJINCPPSDK_SHAREDTOKENFRAGMENTARGUMENTS_HPP
