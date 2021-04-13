#include "enjinsdk/shared/GetGasPrices.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::shared {

GetGasPrices::GetGasPrices() : graphql::AbstractGraphqlRequest("enjin.sdk.shared.GetGasPrices") {
}

std::string GetGasPrices::serialize() const {
    return utils::document_to_string(rapidjson::Document(rapidjson::kObjectType));
}

bool GetGasPrices::operator==(const GetGasPrices& rhs) const {
    return static_cast<const graphql::AbstractGraphqlRequest&>(*this) ==
           static_cast<const graphql::AbstractGraphqlRequest&>(rhs);
}

bool GetGasPrices::operator!=(const GetGasPrices& rhs) const {
    return !(rhs == *this);
}

}
