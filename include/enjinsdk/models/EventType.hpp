#ifndef ENJINCPPSDK_EVENTTYPE_HPP
#define ENJINCPPSDK_EVENTTYPE_HPP

namespace enjin::sdk::models {

/// \brief Enums defining the different types of notifications that may be received from the platform.
enum class EventType {
    UNKNOWN, ///< SDK value for unknown values from the platform.
    APP_CREATED,
    APP_DELETED,
    APP_LINKED,
    APP_LOCKED,
    APP_UNLINKED,
    APP_UNLOCKED,
    APP_UPDATED,
    BLOCKCHAIN_LOG_PROCESSED,
    MESSAGE_PROCESSED,
    PLAYER_CREATED,
    PLAYER_DELETED,
    PLAYER_LINKED,
    PLAYER_UNLINKED,
    PLAYER_UPDATED,
    ASSET_CREATED,
    ASSET_MELTED,
    ASSET_MINTED,
    ASSET_TRANSFERRED,
    ASSET_UPDATED,
    TRADE_COMPLETED,
    TRADE_CREATED,
    TRANSACTION_BROADCAST,
    TRANSACTION_CANCELED,
    TRANSACTION_DROPPED,
    TRANSACTION_EXECUTED,
    TRANSACTION_FAILED,
    TRANSACTION_PENDING,
    TRANSACTION_PROCESSING,
    TRANSACTION_UPDATED,
};

}

#endif //ENJINCPPSDK_EVENTTYPE_HPP
