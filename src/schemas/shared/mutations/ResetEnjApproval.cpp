#include "enjinsdk/shared/ResetEnjApproval.hpp"

namespace enjin::sdk::shared {

ResetEnjApproval::ResetEnjApproval() : graphql::AbstractGraphqlRequest("enjin.sdk.shared.ResetEnjApproval") {
}

std::string ResetEnjApproval::serialize() {
    return TransactionRequestArguments::serialize();
}

bool ResetEnjApproval::operator==(const ResetEnjApproval& rhs) const {
    return static_cast<const graphql::AbstractGraphqlRequest&>(*this) ==
           static_cast<const graphql::AbstractGraphqlRequest&>(rhs) &&
           static_cast<const TransactionRequestArguments<ResetEnjApproval>&>(*this) ==
           static_cast<const TransactionRequestArguments<ResetEnjApproval>&>(rhs);
}

bool ResetEnjApproval::operator!=(const ResetEnjApproval& rhs) const {
    return !(rhs == *this);
}

}
