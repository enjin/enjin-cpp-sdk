#include "enjinsdk/internal/TokenFragmentArguments.hpp"

#include "EnumUtils.hpp"
#include "RapidJsonUtils.hpp"

namespace enjin::sdk::shared {

std::string TokenFragmentArguments::serialize() {
    rapidjson::Document document(rapidjson::kObjectType);

    if (token_id_format.has_value()) {
        utils::set_string_member(document,
                                 "tokenIdFormat",
                                 utils::serialize_token_id_format(token_id_format.value()));
    }
    if (with_state_data.has_value()) {
        utils::set_boolean_member(document, "withStateData", with_state_data.value());
    }
    if (with_config_data.has_value()) {
        utils::set_boolean_member(document, "withConfigData", with_config_data.value());
    }
    if (with_token_blocks.has_value()) {
        utils::set_boolean_member(document, "withTokenBlocks", with_token_blocks.value());
    }
    if (with_creator.has_value()) {
        utils::set_boolean_member(document, "withCreator", with_creator.value());
    }
    if (with_melt_details.has_value()) {
        utils::set_boolean_member(document, "withMeltDetails", with_melt_details.value());
    }
    if (with_metadata_uri.has_value()) {
        utils::set_boolean_member(document, "withMetadataUri", with_metadata_uri.value());
    }
    if (with_supply_details.has_value()) {
        utils::set_boolean_member(document, "withSupplyDetails", with_supply_details.value());
    }
    if (with_transfer_settings.has_value()) {
        utils::set_boolean_member(document, "withTransferSettings", with_transfer_settings.value());
    }
    if (with_token_variant_mode.has_value()) {
        utils::set_boolean_member(document, "withTokenVariantMode", with_token_variant_mode.value());
    }
    if (with_token_variants.has_value()) {
        utils::set_boolean_member(document, "withTokenVariants", with_token_variants.value());
    }
    if (with_variant_metadata.has_value()) {
        utils::set_boolean_member(document, "withVariantMetadata", with_variant_metadata.value());
    }

    return utils::document_to_string(document);
}

void TokenFragmentArguments::set_token_id_format(models::TokenIdFormat token_id_format) {
    TokenFragmentArguments::token_id_format = token_id_format;
}

void TokenFragmentArguments::set_with_state_data() {
    with_state_data = true;
}

void TokenFragmentArguments::set_with_config_data() {
    with_config_data = true;
}

void TokenFragmentArguments::set_with_token_blocks() {
    with_token_blocks = true;
}

void TokenFragmentArguments::set_with_creator() {
    with_creator = true;
}

void TokenFragmentArguments::set_with_melt_details() {
    with_melt_details = true;
}

void TokenFragmentArguments::set_with_metadata_uri() {
    with_metadata_uri = true;
}

void TokenFragmentArguments::set_with_supply_details() {
    with_supply_details = true;
}

void TokenFragmentArguments::set_with_transfer_settings() {
    with_transfer_settings = true;
}

void TokenFragmentArguments::set_with_token_variant_mode() {
    with_token_variant_mode = true;
}

void TokenFragmentArguments::set_with_token_variants() {
    with_token_variants = true;
}

void TokenFragmentArguments::set_with_variant_metadata() {
    with_variant_metadata = true;
}

bool TokenFragmentArguments::operator==(const TokenFragmentArguments& rhs) const {
    return token_id_format == rhs.token_id_format &&
           with_state_data == rhs.with_state_data &&
           with_config_data == rhs.with_config_data &&
           with_token_blocks == rhs.with_token_blocks &&
           with_creator == rhs.with_creator &&
           with_melt_details == rhs.with_melt_details &&
           with_metadata_uri == rhs.with_metadata_uri &&
           with_supply_details == rhs.with_supply_details &&
           with_transfer_settings == rhs.with_transfer_settings &&
           with_token_variant_mode == rhs.with_token_variant_mode &&
           with_token_variants == rhs.with_token_variants &&
           with_variant_metadata == rhs.with_variant_metadata;
}

bool TokenFragmentArguments::operator!=(const TokenFragmentArguments& rhs) const {
    return !(rhs == *this);
}

}
