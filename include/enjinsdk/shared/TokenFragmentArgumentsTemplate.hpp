#ifndef ENJINCPPSDK_TOKENFRAGMENTARGUMENTSTEMPLATE_HPP
#define ENJINCPPSDK_TOKENFRAGMENTARGUMENTSTEMPLATE_HPP

#include "enjinsdk/internal/TokenFragmentArguments.hpp"
#include "enjinsdk/models/TokenIdFormat.hpp"
#include "enjinsdk/serialization/ISerializable.hpp"

namespace enjin::sdk::shared {

/// \brief Fragment interface used to request certain information from tokens returned by the platform.
/// \tparam T The type of the implementing class.
template<class T>
class TokenFragmentArgumentsTemplate : public serialization::ISerializable {
public:
    /// \brief Default constructor.
    TokenFragmentArgumentsTemplate() = default;

    ~TokenFragmentArgumentsTemplate() override = default;

    std::string serialize() override {
        return impl.serialize();
    }

    /// \brief Sets the desired token (item) ID format.
    /// \param token_id_format The format.
    /// \return This request for chaining.
    T& set_token_id_format(models::TokenIdFormat token_id_format) {
        impl.set_token_id_format(token_id_format);
        return dynamic_cast<T&>(*this);
    }

    /// \brief Sets the request to include the state data with the token (item).
    /// \return This request for chaining.
    T& set_with_state_data() {
        impl.set_with_state_data();
        return dynamic_cast<T&>(*this);
    }

    /// \brief Sets the request to include the configuration data with the token (item).
    /// \return This request for chaining.
    T& set_with_config_data() {
        impl.set_with_config_data();
        return dynamic_cast<T&>(*this);
    }

    /// \brief Sets the request to include the block data with the token (item) when used with set_with_state_data().
    /// \return This request for chaining.
    T& set_with_token_blocks() {
        impl.set_with_token_blocks();
        return dynamic_cast<T&>(*this);
    }

    /// \brief Sets the request to include the creator with the token (item) when used with set_with_state_data().
    /// \return This request for chaining.
    T& set_with_creator() {
        impl.set_with_creator();
        return dynamic_cast<T&>(*this);
    }

    /// \brief Sets the request to include the melt details with the token (item) when used with set_with_config_data().
    /// \return This request for chaining.
    T& set_with_melt_details() {
        impl.set_with_melt_details();
        return dynamic_cast<T&>(*this);
    }

    /// \brief Sets the request to include the metadata URI with the token (item) when used with set_with_config_data().
    /// \return This request for chaining.
    T& set_with_metadata_uri() {
        impl.set_with_metadata_uri();
        return dynamic_cast<T&>(*this);
    }

    /// \brief Sets the request to include the supply details with the token (item) when used with
    /// set_with_state_data().
    /// \return This request for chaining.
    T& set_with_supply_details() {
        impl.set_with_supply_details();
        return dynamic_cast<T&>(*this);
    }

    /// \brief Sets the request to include the transfer settings with the token (item) when used with
    /// set_with_config_data().
    /// \return This request for chaining.
    T& set_with_transfer_settings() {
        impl.set_with_transfer_settings();
        return dynamic_cast<T&>(*this);
    }

    /// \brief Sets the request to include the variant mode with the token (item).
    /// \return This request for chaining.
    T& set_with_token_variant_mode() {
        impl.set_with_token_variant_mode();
        return dynamic_cast<T&>(*this);
    }

    /// \brief Sets the request to include the variants with the token (item).
    /// \return This request for chaining.
    T& set_with_token_variants() {
        impl.set_with_token_variants();
        return dynamic_cast<T&>(*this);
    }

    /// \brief Sets the request to include the metadata for the variants with the token (item) when used with
    /// set_with_token_variants().
    /// \return This request for chaining.
    T& set_with_variant_metadata() {
        impl.set_with_variant_metadata();
        return dynamic_cast<T&>(*this);
    }

    bool operator==(const TokenFragmentArgumentsTemplate& rhs) const {
        return impl == rhs.impl;
    }

    bool operator!=(const TokenFragmentArgumentsTemplate& rhs) const {
        return rhs != *this;
    }

private:
    TokenFragmentArguments impl;
};

}

#endif //ENJINCPPSDK_TOKENFRAGMENTARGUMENTSTEMPLATE_HPP
