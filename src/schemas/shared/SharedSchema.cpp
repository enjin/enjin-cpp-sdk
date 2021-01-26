#include <enjinsdk/shared/SharedSchema.hpp>

namespace enjin::sdk::shared {

SharedSchema::SharedSchema(const enjin::sdk::TrustedPlatformMiddleware& middleware, const std::string& schema)
        : BaseSchema(middleware, schema) {
}

std::future<graphql::GraphqlResponse<models::Request>>
SharedSchema::advanced_send_token_async(AdvancedSendToken& request) {
    return send_request_for_one<models::Request>(request);
}

graphql::GraphqlResponse<models::Request> SharedSchema::advanced_send_token_sync(AdvancedSendToken& request) {
    return send_request_for_one<models::Request>(request).get();
}

std::future<graphql::GraphqlResponse<models::Request>> SharedSchema::approve_enj_async(ApproveEnj& request) {
    return send_request_for_one<models::Request>(request);
}

graphql::GraphqlResponse<models::Request> SharedSchema::approve_enj_sync(ApproveEnj& request) {
    return send_request_for_one<models::Request>(request).get();
}

std::future<graphql::GraphqlResponse<models::Request>> SharedSchema::approve_enj_max_async(ApproveMaxEnj& request) {
    return send_request_for_one<models::Request>(request);
}

graphql::GraphqlResponse<models::Request> SharedSchema::approve_enj_max_sync(ApproveMaxEnj& request) {
    return send_request_for_one<models::Request>(request).get();
}

std::future<graphql::GraphqlResponse<bool>> SharedSchema::cancel_transaction_async(CancelTransaction& request) {
    return send_request_for_one<bool>(request);
}

graphql::GraphqlResponse<bool> SharedSchema::cancel_transaction_sync(CancelTransaction& request) {
    return send_request_for_one<bool>(request).get();
}

std::future<graphql::GraphqlResponse<models::Request>> SharedSchema::complete_trade_async(CompleteTrade& request) {
    return send_request_for_one<models::Request>(request);
}

graphql::GraphqlResponse<models::Request> SharedSchema::complete_trade_sync(CompleteTrade& request) {
    return send_request_for_one<models::Request>(request).get();
}

std::future<graphql::GraphqlResponse<models::Request>> SharedSchema::create_trade_async(CreateTrade& request) {
    return send_request_for_one<models::Request>(request);
}

graphql::GraphqlResponse<models::Request> SharedSchema::create_trade_sync(CreateTrade& request) {
    return send_request_for_one<models::Request>(request).get();
}

std::future<graphql::GraphqlResponse<std::vector<models::Balance>>>
SharedSchema::get_balances_async(GetBalances& request) {
    return send_request_for_many<models::Balance>(request);
}

graphql::GraphqlResponse<std::vector<models::Balance>> SharedSchema::get_balances_sync(GetBalances& request) {
    return send_request_for_many<models::Balance>(request).get();
}

std::future<graphql::GraphqlResponse<models::GasPrices>> SharedSchema::get_gas_prices_async(GetGasPrices& request) {
    return send_request_for_one<models::GasPrices>(request);
}

graphql::GraphqlResponse<models::GasPrices> SharedSchema::get_gas_prices_sync(GetGasPrices& request) {
    return send_request_for_one<models::GasPrices>(request).get();
}

std::future<graphql::GraphqlResponse<models::Platform>> SharedSchema::get_platform_async(GetPlatform& request) {
    return send_request_for_one<models::Platform>(request);
}

graphql::GraphqlResponse<models::Platform> SharedSchema::get_platform_sync(GetPlatform& request) {
    return send_request_for_one<models::Platform>(request).get();
}

std::future<graphql::GraphqlResponse<models::Project>> SharedSchema::get_project_async(GetProject& request) {
    return send_request_for_one<models::Project>(request);
}

graphql::GraphqlResponse<models::Project> SharedSchema::get_project_sync(GetProject& request) {
    return send_request_for_one<models::Project>(request).get();
}

std::future<graphql::GraphqlResponse<models::Request>> SharedSchema::get_request_async(GetRequest& request) {
    return send_request_for_one<models::Request>(request);
}

graphql::GraphqlResponse<models::Request> SharedSchema::get_request_sync(GetRequest& request) {
    return send_request_for_one<models::Request>(request).get();
}

std::future<graphql::GraphqlResponse<std::vector<models::Request>>>
SharedSchema::get_requests_async(GetRequests& request) {
    return send_request_for_many<models::Request>(request);
}

graphql::GraphqlResponse<std::vector<models::Request>> SharedSchema::get_requests_sync(GetRequests& request) {
    return send_request_for_many<models::Request>(request).get();
}

std::future<graphql::GraphqlResponse<models::Token>> SharedSchema::get_token_async(GetToken& request) {
    return send_request_for_one<models::Token>(request);
}

graphql::GraphqlResponse<models::Token> SharedSchema::get_token_sync(GetToken& request) {
    return send_request_for_one<models::Token>(request).get();
}

std::future<graphql::GraphqlResponse<std::vector<models::Token>>> SharedSchema::get_tokens_async(GetTokens& request) {
    return send_request_for_many<models::Token>(request);
}

graphql::GraphqlResponse<std::vector<models::Token>> SharedSchema::get_tokens_sync(GetTokens& request) {
    return send_request_for_many<models::Token>(request).get();
}

std::future<graphql::GraphqlResponse<models::Request>> SharedSchema::melt_token_async(MeltToken& request) {
    return send_request_for_one<models::Request>(request);
}

graphql::GraphqlResponse<models::Request> SharedSchema::melt_token_sync(MeltToken& request) {
    return send_request_for_one<models::Request>(request).get();
}

std::future<graphql::GraphqlResponse<models::Request>> SharedSchema::message_async(Message& request) {
    return send_request_for_one<models::Request>(request);
}

graphql::GraphqlResponse<models::Request> SharedSchema::message_sync(Message& request) {
    return send_request_for_one<models::Request>(request).get();
}

std::future<graphql::GraphqlResponse<models::Request>>
SharedSchema::reset_enj_approval_async(ResetEnjApproval& request) {
    return send_request_for_one<models::Request>(request);
}

graphql::GraphqlResponse<models::Request> SharedSchema::reset_enj_approval_sync(ResetEnjApproval& request) {
    return send_request_for_one<models::Request>(request).get();
}

std::future<graphql::GraphqlResponse<models::Request>> SharedSchema::send_enj_async(SendEnj& request) {
    return send_request_for_one<models::Request>(request);
}

graphql::GraphqlResponse<models::Request> SharedSchema::send_enj_sync(SendEnj& request) {
    return send_request_for_one<models::Request>(request).get();
}

std::future<graphql::GraphqlResponse<models::Request>> SharedSchema::send_token_async(SendToken& request) {
    return send_request_for_one<models::Request>(request);
}

graphql::GraphqlResponse<models::Request> SharedSchema::send_token_sync(SendToken& request) {
    return send_request_for_one<models::Request>(request).get();
}

std::future<graphql::GraphqlResponse<models::Request>>
SharedSchema::set_approval_for_all_async(SetApprovalForAll& request) {
    return send_request_for_one<models::Request>(request);
}

graphql::GraphqlResponse<models::Request> SharedSchema::set_approval_for_all_sync(SetApprovalForAll& request) {
    return send_request_for_one<models::Request>(request).get();
}

}
