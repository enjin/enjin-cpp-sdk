#include "enjinsdk/shared/GetPlatform.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::shared {

GetPlatform::GetPlatform() : graphql::AbstractGraphqlRequest("enjin.sdk.shared.GetPlatform") {
}

std::string GetPlatform::serialize() {
    rapidjson::Document document(rapidjson::kObjectType);

    if (with_contracts.has_value()) {
        utils::set_boolean_member(document, "withContracts", with_contracts.value());
    }
    if (with_notifications.has_value()) {
        utils::set_boolean_member(document, "withNotificationDrivers", with_notifications.value());
    }

    return utils::document_to_string(document);
}

GetPlatform& GetPlatform::set_with_contracts() {
    with_contracts = true;
    return *this;
}

GetPlatform& GetPlatform::set_with_notifications() {
    with_notifications = true;
    return *this;
}

bool GetPlatform::operator==(const GetPlatform& rhs) const {
    return static_cast<const graphql::AbstractGraphqlRequest&>(*this) ==
           static_cast<const graphql::AbstractGraphqlRequest&>(rhs) &&
           with_contracts == rhs.with_contracts &&
           with_notifications == rhs.with_notifications;
}

bool GetPlatform::operator!=(const GetPlatform& rhs) const {
    return !(rhs == *this);
}

}
