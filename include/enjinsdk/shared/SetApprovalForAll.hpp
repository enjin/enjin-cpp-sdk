#ifndef ENJINCPPSDK_SETAPPROVALFORALL_HPP
#define ENJINCPPSDK_SETAPPROVALFORALL_HPP

#include "enjinsdk/AbstractGraphqlRequest.hpp"
#include "enjinsdk/shared/TransactionRequestArgumentsTemplate.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::shared {

class SetApprovalForAll : public graphql::AbstractGraphqlRequest,
                          public TransactionRequestArgumentsTemplate<SetApprovalForAll> {
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

#endif //ENJINCPPSDK_SETAPPROVALFORALL_HPP
