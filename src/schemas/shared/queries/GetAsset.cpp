#include "enjinsdk/shared/GetAsset.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::shared {

GetAsset::GetAsset() : graphql::AbstractGraphqlRequest("enjin.sdk.shared.GetAsset") {
}

std::string GetAsset::serialize() const {
    rapidjson::Document document(rapidjson::kObjectType);
    utils::join_serialized_object_to_document(document, AssetFragmentArguments::serialize());

    if (id.has_value()) {
        utils::set_string_member(document, "id", id.value());
    }

    return utils::document_to_string(document);
}

GetAsset& GetAsset::set_id(const std::string& id) {
    GetAsset::id = id;
    return *this;
}

bool GetAsset::operator==(const GetAsset& rhs) const {
    return static_cast<const graphql::AbstractGraphqlRequest&>(*this) ==
           static_cast<const graphql::AbstractGraphqlRequest&>(rhs) &&
           static_cast<const AssetFragmentArguments<GetAsset>&>(*this) ==
           static_cast<const AssetFragmentArguments<GetAsset>&>(rhs) &&
           id == rhs.id;
}

bool GetAsset::operator!=(const GetAsset& rhs) const {
    return !(rhs == *this);
}

}
