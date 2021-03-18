#ifndef ENJINCPPSDK_SHAREDSETAPPROVALFORALL_HPP
#define ENJINCPPSDK_SHAREDSETAPPROVALFORALL_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/AbstractGraphqlRequest.hpp"
#include "enjinsdk/shared/TransactionRequestArguments.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::shared {

class ENJINSDK_EXPORT SetApprovalForAll : public graphql::AbstractGraphqlRequest,
                                          public TransactionRequestArguments<SetApprovalForAll> {
public:
    SetApprovalForAll();

    ~SetApprovalForAll() override = default;

    std::string serialize() override;

    SetApprovalForAll& set_operator_address(const std::string& operator_address);

    SetApprovalForAll& set_approved(bool approved);

    bool operator==(const SetApprovalForAll& rhs) const;

    bool operator!=(const SetApprovalForAll& rhs) const;

private:
    std::optional<std::string> operator_address;
    std::optional<bool> approved;
};

}

#endif //ENJINCPPSDK_SHAREDSETAPPROVALFORALL_HPP
