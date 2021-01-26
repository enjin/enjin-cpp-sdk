#include "enjinsdk/shared/ResetEnjApproval.hpp"

namespace enjin::sdk::shared {

ResetEnjApproval::ResetEnjApproval() : graphql::AbstractGraphqlRequest("enjin.sdk.shared.ResetEnjApproval") {
}

std::string ResetEnjApproval::serialize() {
    return TransactionRequestArgumentsTemplate::serialize();
}

bool ResetEnjApproval::operator==(const ResetEnjApproval& rhs) const {
    return static_cast<const graphql::AbstractGraphqlRequest&>(*this) ==
           static_cast<const graphql::AbstractGraphqlRequest&>(rhs) &&
           static_cast<const TransactionRequestArgumentsTemplate<ResetEnjApproval>&>(*this) ==
           static_cast<const TransactionRequestArgumentsTemplate<ResetEnjApproval>&>(rhs);
}

bool ResetEnjApproval::operator!=(const ResetEnjApproval& rhs) const {
    return !(rhs == *this);
}

}