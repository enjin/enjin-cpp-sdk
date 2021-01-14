#ifndef ENJINCPPSDK_REQUESTTYPE_HPP
#define ENJINCPPSDK_REQUESTTYPE_HPP

namespace enjin::sdk::models {

/// \brief Represents the request type when creating or updating a request.
enum class RequestType {
    UNKNOWN, ///< SDK value for unknown values.
    APPROVE,
    CREATE,
    MINT,
    SEND,
    SEND_ENJ,
    ADVANCED_SEND,
    CREATE_TRADE,
    CANCEL_TRADE,
    MELT,
    UPDATE_NAME,
    SET_ITEM_URI,
    SET_WHITELISTED,
    SET_TRANSFERABLE,
    SET_MELT_FEE,
    DECREASE_MAX_MELT_FEE,
    SET_TRANSFER_FEE,
    DECREASE_MAX_TRANSFER_FEE,
    RELEASE_RESERVE,
    ADD_LOG,
    SET_APPROVAL_FOR_ALL,
    MANAGE_UPDATE,
    SET_DECIMALS,
    SET_SYMBOL,
    MESSAGE,
};

}

#endif //ENJINCPPSDK_REQUESTTYPE_HPP
