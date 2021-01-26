#ifndef ENJINCPPSDK_ISHAREDSCHEMA_HPP
#define ENJINCPPSDK_ISHAREDSCHEMA_HPP

#include "enjinsdk/GraphqlResponse.hpp"
#include "enjinsdk/models/Balance.hpp"
#include "enjinsdk/models/GasPrices.hpp"
#include "enjinsdk/models/Platform.hpp"
#include "enjinsdk/models/Project.hpp"
#include "enjinsdk/models/Request.hpp"
#include "enjinsdk/models/Token.hpp"
#include "enjinsdk/shared/AdvancedSendToken.hpp"
#include "enjinsdk/shared/ApproveEnj.hpp"
#include "enjinsdk/shared/ApproveMaxEnj.hpp"
#include "enjinsdk/shared/CancelTransaction.hpp"
#include "enjinsdk/shared/CompleteTrade.hpp"
#include "enjinsdk/shared/CreateTrade.hpp"
#include "enjinsdk/shared/GetBalances.hpp"
#include "enjinsdk/shared/GetGasPrices.hpp"
#include "enjinsdk/shared/GetPlatform.hpp"
#include "enjinsdk/shared/GetProject.hpp"
#include "enjinsdk/shared/GetRequest.hpp"
#include "enjinsdk/shared/GetRequests.hpp"
#include "enjinsdk/shared/GetToken.hpp"
#include "enjinsdk/shared/GetTokens.hpp"
#include "enjinsdk/shared/MeltToken.hpp"
#include "enjinsdk/shared/Message.hpp"
#include "enjinsdk/shared/ResetEnjApproval.hpp"
#include "enjinsdk/shared/SendEnj.hpp"
#include "enjinsdk/shared/SendToken.hpp"
#include "enjinsdk/shared/SetApprovalForAll.hpp"
#include <future>
#include <vector>

namespace enjin::sdk::shared {

/// \brief Interface for shared schema implementation.
class ISharedSchema {
public:
    /// \brief Default destructor.
    virtual ~ISharedSchema() = default;

    /// \brief Sends AdvancedSendToken request asynchronously.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::Request>>
    advanced_send_token_async(AdvancedSendToken& request) = 0;

    /// \brief Sends AdvancedSendToken request synchronously.
    /// \param request The request.
    /// \return The response.
    virtual graphql::GraphqlResponse<models::Request> advanced_send_token_sync(AdvancedSendToken& request) = 0;

    /// \brief Sends ApproveEnj request asynchronously.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::Request>> approve_enj_async(ApproveEnj& request) = 0;

    /// \brief Sends ApproveEnj request synchronously.
    /// \param request The request.
    /// \return The response.
    virtual graphql::GraphqlResponse<models::Request> approve_enj_sync(ApproveEnj& request) = 0;

    /// \brief Sends ApproveMaxEnj request asynchronously.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::Request>> approve_enj_max_async(ApproveMaxEnj& request) = 0;

    /// \brief Sends ApproveMaxEnj request synchronously.
    /// \param request The request.
    /// \return The response.
    virtual graphql::GraphqlResponse<models::Request> approve_enj_max_sync(ApproveMaxEnj& request) = 0;

    /// \brief Sends CancelTransaction request asynchronously.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<bool>> cancel_transaction_async(CancelTransaction& request) = 0;

    /// \brief Sends CancelTransaction request synchronously.
    /// \param request The request.
    /// \return The response.
    virtual graphql::GraphqlResponse<bool> cancel_transaction_sync(CancelTransaction& request) = 0;

    /// \brief Sends CompleteTrade request asynchronously.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::Request>> complete_trade_async(CompleteTrade& request) = 0;

    /// \brief Sends CompleteTrade request synchronously.
    /// \param request The request.
    /// \return The response.
    virtual graphql::GraphqlResponse<models::Request> complete_trade_sync(CompleteTrade& request) = 0;

    /// \brief Sends CreateTrade request asynchronously.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::Request>> create_trade_async(CreateTrade& request) = 0;

    /// \brief Sends CreateTrade request synchronously.
    /// \param request The request.
    /// \return The response.
    virtual graphql::GraphqlResponse<models::Request> create_trade_sync(CreateTrade& request) = 0;

    /// \brief Sends GetBalances request asynchronously.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<std::vector<models::Balance>>>
    get_balances_async(GetBalances& request) = 0;

    /// \brief Sends GetBalances request synchronously.
    /// \param request The request.
    /// \return The response.
    virtual graphql::GraphqlResponse<std::vector<models::Balance>> get_balances_sync(GetBalances& request) = 0;

    /// \brief Sends GetGasPrices request asynchronously.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::GasPrices>> get_gas_prices_async(GetGasPrices& request) = 0;

    /// \brief Sends GetGasPrices request synchronously.
    /// \param request The request.
    /// \return The response.
    virtual graphql::GraphqlResponse<models::GasPrices> get_gas_prices_sync(GetGasPrices& request) = 0;

    /// \brief Sends GetPlatform request asynchronously.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::Platform>> get_platform_async(GetPlatform& request) = 0;

    /// \brief Sends GetPlatform request synchronously.
    /// \param request The request.
    /// \return The response.
    virtual graphql::GraphqlResponse<models::Platform> get_platform_sync(GetPlatform& request) = 0;

    /// \brief Sends GetProject request asynchronously.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::Project>> get_project_async(GetProject& request) = 0;

    /// \brief Sends GetProject request synchronously.
    /// \param request The request.
    /// \return The response.
    virtual graphql::GraphqlResponse<models::Project> get_project_sync(GetProject& request) = 0;

    /// \brief Sends GetRequest request asynchronously.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::Request>> get_request_async(GetRequest& request) = 0;

    /// \brief Sends GetRequest request synchronously.
    /// \param request The request.
    /// \return The response.
    virtual graphql::GraphqlResponse<models::Request> get_request_sync(GetRequest& request) = 0;

    /// \brief Sends GetRequests request asynchronously.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<std::vector<models::Request>>>
    get_requests_async(GetRequests& request) = 0;

    /// \brief Sends GetRequests request synchronously.
    /// \param request The request.
    /// \return The response.
    virtual graphql::GraphqlResponse<std::vector<models::Request>> get_requests_sync(GetRequests& request) = 0;

    /// \brief Sends GetToken request asynchronously.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::Token>> get_token_async(GetToken& request) = 0;

    /// \brief Sends GetToken request synchronously.
    /// \param request The request.
    /// \return The response.
    virtual graphql::GraphqlResponse<models::Token> get_token_sync(GetToken& request) = 0;

    /// \brief Sends GetTokens request asynchronously.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<std::vector<models::Token>>> get_tokens_async(GetTokens& request) = 0;

    /// \brief Sends GetTokens request synchronously.
    /// \param request The request.
    /// \return The response.
    virtual graphql::GraphqlResponse<std::vector<models::Token>> get_tokens_sync(GetTokens& request) = 0;

    /// \brief Sends MeltToken request asynchronously.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::Request>> melt_token_async(MeltToken& request) = 0;

    /// \brief Sends MeltToken request synchronously.
    /// \param request The request.
    /// \return The response.
    virtual graphql::GraphqlResponse<models::Request> melt_token_sync(MeltToken& request) = 0;

    /// \brief Sends Message request asynchronously.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::Request>> message_async(Message& request) = 0;

    /// \brief Sends Message request synchronously.
    /// \param request The request.
    /// \return The response.
    virtual graphql::GraphqlResponse<models::Request> message_sync(Message& request) = 0;

    /// \brief Sends ResetEnjApproval request asynchronously.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::Request>>
    reset_enj_approval_async(ResetEnjApproval& request) = 0;

    /// \brief Sends ResetEnjApproval request synchronously.
    /// \param request The request.
    /// \return The response.
    virtual graphql::GraphqlResponse<models::Request> reset_enj_approval_sync(ResetEnjApproval& request) = 0;

    /// \brief Sends SendEnj request asynchronously.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::Request>> send_enj_async(SendEnj& request) = 0;

    /// \brief Sends SendEnj request synchronously.
    /// \param request The request.
    /// \return The response.
    virtual graphql::GraphqlResponse<models::Request> send_enj_sync(SendEnj& request) = 0;

    /// \brief Sends SendToken request asynchronously.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::Request>> send_token_async(SendToken& request) = 0;

    /// \brief Sends SendToken request synchronously.
    /// \param request The request.
    /// \return The response.
    virtual graphql::GraphqlResponse<models::Request> send_token_sync(SendToken& request) = 0;

    /// \brief Sends SetApprovalForAll request asynchronously.
    /// \param request The request.
    /// \return The future containing the response.
    virtual std::future<graphql::GraphqlResponse<models::Request>>
    set_approval_for_all_async(SetApprovalForAll& request) = 0;

    /// \brief Sends SetApprovalForAll request synchronously.
    /// \param request The request.
    /// \return The response.
    virtual graphql::GraphqlResponse<models::Request> set_approval_for_all_sync(SetApprovalForAll& request) = 0;
};

}

#endif //ENJINCPPSDK_ISHAREDSCHEMA_HPP
