#include "enjinsdk/shared/ApproveEnj.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::shared {

ApproveEnj::ApproveEnj() : graphql::AbstractGraphqlRequest("enjin.sdk.shared.ApproveEnj") {
}

std::string ApproveEnj::serialize() {
    rapidjson::Document document;
    document.Parse(TransactionRequestArgumentsTemplate::serialize().c_str());

    if (value.has_value()) {
        utils::set_string_member(document, "value", value.value());
    }

    return utils::document_to_string(document);
}

ApproveEnj& ApproveEnj::set_value(const std::string& value) {
    ApproveEnj::value = value;
    return *this;
}

bool ApproveEnj::operator==(const ApproveEnj& rhs) const {
    return static_cast<const graphql::AbstractGraphqlRequest&>(*this) ==
           static_cast<const graphql::AbstractGraphqlRequest&>(rhs) &&
           static_cast<const TransactionRequestArgumentsTemplate<ApproveEnj>&>(*this) ==
           static_cast<const TransactionRequestArgumentsTemplate<ApproveEnj>&>(rhs) &&
           value == rhs.value;
}

bool ApproveEnj::operator!=(const ApproveEnj& rhs) const {
    return !(rhs == *this);
}

}
