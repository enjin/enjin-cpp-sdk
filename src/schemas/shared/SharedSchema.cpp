#include <enjinsdk/shared/SharedSchema.hpp>

#include <utility>

namespace enjin::sdk::shared {

SharedSchema::SharedSchema(TrustedPlatformMiddleware middleware,
                           const std::string& schema,
                           std::shared_ptr<utils::Logger> logger)
        : BaseSchema(std::move(middleware), schema, std::move(logger)) {
}

std::future<graphql::GraphqlResponse<models::Request>>
SharedSchema::advanced_send_asset_async(AdvancedSendAsset& request) {
    return send_request_for_one<models::Request>(request);
}

graphql::GraphqlResponse<models::Request> SharedSchema::advanced_send_asset_sync(AdvancedSendAsset& request) {
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

std::future<graphql::GraphqlResponse<models::Asset>> SharedSchema::get_asset_async(GetAsset& request) {
    return send_request_for_one<models::Asset>(request);
}

graphql::GraphqlResponse<models::Asset> SharedSchema::get_asset_sync(GetAsset& request) {
    return send_request_for_one<models::Asset>(request).get();
}

std::future<graphql::GraphqlResponse<std::vector<models::Asset>>> SharedSchema::get_assets_async(GetAssets& request) {
    return send_request_for_many<models::Asset>(request);
}

graphql::GraphqlResponse<std::vector<models::Asset>> SharedSchema::get_assets_sync(GetAssets& request) {
    return send_request_for_many<models::Asset>(request).get();
}

std::future<graphql::GraphqlResponse<models::Request>> SharedSchema::melt_asset_async(MeltAsset& request) {
    return send_request_for_one<models::Request>(request);
}

graphql::GraphqlResponse<models::Request> SharedSchema::melt_asset_sync(MeltAsset& request) {
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

std::future<graphql::GraphqlResponse<models::Request>> SharedSchema::send_asset_async(SendAsset& request) {
    return send_request_for_one<models::Request>(request);
}

graphql::GraphqlResponse<models::Request> SharedSchema::send_asset_sync(SendAsset& request) {
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
