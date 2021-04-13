#include "enjinsdk/shared/ApproveMaxEnj.hpp"

namespace enjin::sdk::shared {

ApproveMaxEnj::ApproveMaxEnj() : graphql::AbstractGraphqlRequest("enjin.sdk.shared.ApproveMaxEnj") {
}

std::string ApproveMaxEnj::serialize() const {
    return TransactionRequestArguments::serialize();
}

bool ApproveMaxEnj::operator==(const ApproveMaxEnj& rhs) const {
    return static_cast<const graphql::AbstractGraphqlRequest&>(*this) ==
           static_cast<const graphql::AbstractGraphqlRequest&>(rhs) &&
           static_cast<const TransactionRequestArguments<ApproveMaxEnj>&>(*this) ==
           static_cast<const TransactionRequestArguments<ApproveMaxEnj>&>(rhs);
}

bool ApproveMaxEnj::operator!=(const ApproveMaxEnj& rhs) const {
    return !(rhs == *this);
}

}
