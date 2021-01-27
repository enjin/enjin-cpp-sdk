#ifndef ENJINCPPSDK_SHAREDSCHEMA_HPP
#define ENJINCPPSDK_SHAREDSCHEMA_HPP

#include "enjinsdk/BaseSchema.hpp"
#include "enjinsdk/shared/ISharedSchema.hpp"
#include <string>

namespace enjin::sdk::shared {

/// \brief Class for sending requests shared across schemas.
class SharedSchema : public ISharedSchema,
                     public BaseSchema {
public:
    ~SharedSchema() override = default;

    std::future<graphql::GraphqlResponse<models::Request>>
    advanced_send_token_async(AdvancedSendToken& request) override;

    graphql::GraphqlResponse<models::Request> advanced_send_token_sync(AdvancedSendToken& request) override;

    std::future<graphql::GraphqlResponse<models::Request>> approve_enj_async(ApproveEnj& request) override;

    graphql::GraphqlResponse<models::Request> approve_enj_sync(ApproveEnj& request) override;

    std::future<graphql::GraphqlResponse<models::Request>> approve_enj_max_async(ApproveMaxEnj& request) override;

    graphql::GraphqlResponse<models::Request> approve_enj_max_sync(ApproveMaxEnj& request) override;

    std::future<graphql::GraphqlResponse<bool>> cancel_transaction_async(CancelTransaction& request) override;

    graphql::GraphqlResponse<bool> cancel_transaction_sync(CancelTransaction& request) override;

    std::future<graphql::GraphqlResponse<models::Request>> complete_trade_async(CompleteTrade& request) override;

    graphql::GraphqlResponse<models::Request> complete_trade_sync(CompleteTrade& request) override;

    std::future<graphql::GraphqlResponse<models::Request>> create_trade_async(CreateTrade& request) override;

    graphql::GraphqlResponse<models::Request> create_trade_sync(CreateTrade& request) override;

    std::future<graphql::GraphqlResponse<std::vector<models::Balance>>>
    get_balances_async(GetBalances& request) override;

    graphql::GraphqlResponse<std::vector<models::Balance>> get_balances_sync(GetBalances& request) override;

    std::future<graphql::GraphqlResponse<models::GasPrices>> get_gas_prices_async(GetGasPrices& request) override;

    graphql::GraphqlResponse<models::GasPrices> get_gas_prices_sync(GetGasPrices& request) override;

    std::future<graphql::GraphqlResponse<models::Platform>> get_platform_async(GetPlatform& request) override;

    graphql::GraphqlResponse<models::Platform> get_platform_sync(GetPlatform& request) override;

    std::future<graphql::GraphqlResponse<models::Project>> get_project_async(GetProject& request) override;

    graphql::GraphqlResponse<models::Project> get_project_sync(GetProject& request) override;

    std::future<graphql::GraphqlResponse<models::Request>> get_request_async(GetRequest& request) override;

    graphql::GraphqlResponse<models::Request> get_request_sync(GetRequest& request) override;

    std::future<graphql::GraphqlResponse<std::vector<models::Request>>>
    get_requests_async(GetRequests& request) override;

    graphql::GraphqlResponse<std::vector<models::Request>> get_requests_sync(GetRequests& request) override;

    std::future<graphql::GraphqlResponse<models::Token>> get_token_async(GetToken& request) override;

    graphql::GraphqlResponse<models::Token> get_token_sync(GetToken& request) override;

    std::future<graphql::GraphqlResponse<std::vector<models::Token>>> get_tokens_async(GetTokens& request) override;

    graphql::GraphqlResponse<std::vector<models::Token>> get_tokens_sync(GetTokens& request) override;

    std::future<graphql::GraphqlResponse<models::Request>> melt_token_async(MeltToken& request) override;

    graphql::GraphqlResponse<models::Request> melt_token_sync(MeltToken& request) override;

    std::future<graphql::GraphqlResponse<models::Request>> message_async(Message& request) override;

    graphql::GraphqlResponse<models::Request> message_sync(Message& request) override;

    std::future<graphql::GraphqlResponse<models::Request>> reset_enj_approval_async(ResetEnjApproval& request) override;

    graphql::GraphqlResponse<models::Request> reset_enj_approval_sync(ResetEnjApproval& request) override;

    std::future<graphql::GraphqlResponse<models::Request>> send_enj_async(SendEnj& request) override;

    graphql::GraphqlResponse<models::Request> send_enj_sync(SendEnj& request) override;

    std::future<graphql::GraphqlResponse<models::Request>> send_token_async(SendToken& request) override;

    graphql::GraphqlResponse<models::Request> send_token_sync(SendToken& request) override;

    std::future<graphql::GraphqlResponse<models::Request>>
    set_approval_for_all_async(SetApprovalForAll& request) override;

    graphql::GraphqlResponse<models::Request> set_approval_for_all_sync(SetApprovalForAll& request) override;

protected:
    /// \brief Constructs the schema with the middleware and name.
    /// \param middleware The middleware.
    /// \param schema The schema name.
    SharedSchema(const TrustedPlatformMiddleware& middleware, const std::string& schema);
};

}

#endif //ENJINCPPSDK_SHAREDSCHEMA_HPP
