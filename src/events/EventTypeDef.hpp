#ifndef ENJINCPPSDK_EVENTTYPEDEF_HPP
#define ENJINCPPSDK_EVENTTYPEDEF_HPP

#include "enjinsdk/models/EventType.hpp"
#include <map>
#include <string>
#include <vector>

namespace enjin::sdk::events {

class EventTypeDef {
public:
    EventTypeDef() = delete;

    ~EventTypeDef() = default;

    bool in(const std::vector<models::EventType>& types);

    [[nodiscard]] models::EventType get_type() const;

    [[nodiscard]] const std::string& get_key() const;

    [[nodiscard]] const std::vector<std::string>& get_channels() const;

    [[nodiscard]] const std::string& get_name() const;

    bool operator==(const EventTypeDef& rhs) const;

    bool operator!=(const EventTypeDef& rhs) const;

    static std::vector<EventTypeDef> values();

    static std::vector<EventTypeDef> filter_by_channel_types(const std::vector<std::string>& channels);

    static EventTypeDef get_from_name(const std::string& name);

    static EventTypeDef get_from_key(const std::string& key);

private:
    models::EventType type;
    std::string key;
    std::vector<std::string> channels;
    std::string name;

    EventTypeDef(models::EventType type, std::string key, std::vector<std::string> channels);

    static EventTypeDef* create(models::EventType type, const std::string& key, std::vector<std::string> channels);

    inline static std::map<models::EventType, EventTypeDef*> map = {
            {models::EventType::UNKNOWN,                  create(models::EventType::UNKNOWN,
                                                                 "",
                                                                 {""})},
            {models::EventType::PROJECT_CREATED,          create(models::EventType::PROJECT_CREATED,
                                                                 "EnjinCloud\\Events\\ProjectCreated",
                                                                 {"project"})},
            {models::EventType::PROJECT_DELETED,          create(models::EventType::PROJECT_DELETED,
                                                                 "EnjinCloud\\Events\\ProjectDeleted",
                                                                 {"project"})},
            {models::EventType::PROJECT_LINKED,           create(models::EventType::PROJECT_LINKED,
                                                                 "EnjinCloud\\Events\\ProjectLinked",
                                                                 {"project", "wallet"})},
            {models::EventType::PROJECT_LOCKED,           create(models::EventType::PROJECT_LOCKED,
                                                                 "EnjinCloud\\Events\\ProjectLocked",
                                                                 {"project"})},
            {models::EventType::PROJECT_UNLINKED,         create(models::EventType::PROJECT_UNLINKED,
                                                                 "EnjinCloud\\Events\\ProjectUnlinked",
                                                                 {"project", "wallet"})},
            {models::EventType::PROJECT_UNLOCKED,         create(models::EventType::PROJECT_UNLOCKED,
                                                                 "EnjinCloud\\Events\\ProjectUnlocked",
                                                                 {"project"})},
            {models::EventType::PROJECT_UPDATED,          create(models::EventType::PROJECT_UPDATED,
                                                                 "EnjinCloud\\Events\\ProjectUpdated",
                                                                 {"project"})},
            {models::EventType::BLOCKCHAIN_LOG_PROCESSED, create(models::EventType::BLOCKCHAIN_LOG_PROCESSED,
                                                                 "EnjinCloud\\Events\\BlockchainLogProcessed",
                                                                 {"project", "asset", "wallet"})},
            {models::EventType::MESSAGE_PROCESSED,        create(models::EventType::MESSAGE_PROCESSED,
                                                                 "EnjinCloud\\Events\\MessageProcessed",
                                                                 {"project", "asset", "wallet"})},
            {models::EventType::PLAYER_CREATED,           create(models::EventType::PLAYER_CREATED,
                                                                 "EnjinCloud\\Events\\PlayerCreated",
                                                                 {"project", "player"})},
            {models::EventType::PLAYER_DELETED,           create(models::EventType::PLAYER_DELETED,
                                                                 "EnjinCloud\\Events\\PlayerDeleted",
                                                                 {"project", "player"})},
            {models::EventType::PLAYER_LINKED,            create(models::EventType::PLAYER_LINKED,
                                                                 "EnjinCloud\\Events\\PlayerLinked",
                                                                 {"project", "player", "wallet"})},
            {models::EventType::PLAYER_UNLINKED,          create(models::EventType::PLAYER_UNLINKED,
                                                                 "EnjinCloud\\Events\\PlayerUnlinked",
                                                                 {"project", "player", "wallet"})},
            {models::EventType::PLAYER_UPDATED,           create(models::EventType::PLAYER_UPDATED,
                                                                 "EnjinCloud\\Events\\PlayerUpdated",
                                                                 {"project", "player"})},
            {models::EventType::ASSET_CREATED,            create(models::EventType::ASSET_CREATED,
                                                                 "EnjinCloud\\Events\\AssetCreated",
                                                                 {"project", "asset", "wallet"})},
            {models::EventType::ASSET_MELTED,             create(models::EventType::ASSET_MELTED,
                                                                 "EnjinCloud\\Events\\AssetMelted",
                                                                 {"project", "asset", "wallet"})},
            {models::EventType::ASSET_MINTED,             create(models::EventType::ASSET_MINTED,
                                                                 "EnjinCloud\\Events\\AssetMinted",
                                                                 {"project", "asset", "wallet"})},
            {models::EventType::ASSET_TRANSFERRED,        create(models::EventType::ASSET_TRANSFERRED,
                                                                 "EnjinCloud\\Events\\AssetTransferred",
                                                                 {"project", "asset", "wallet"})},
            {models::EventType::ASSET_UPDATED,            create(models::EventType::ASSET_UPDATED,
                                                                 "EnjinCloud\\Events\\AssetUpdated",
                                                                 {"project", "asset", "wallet"})},
            {models::EventType::TRADE_COMPLETED,          create(models::EventType::TRADE_COMPLETED,
                                                                 "EnjinCloud\\Events\\TradeCompleted",
                                                                 {"project", "asset", "wallet"})},
            {models::EventType::TRADE_CREATED,            create(models::EventType::TRADE_CREATED,
                                                                 "EnjinCloud\\Events\\TradeCreated",
                                                                 {"project", "asset", "wallet"})},
            {models::EventType::TRANSACTION_BROADCAST,    create(models::EventType::TRANSACTION_BROADCAST,
                                                                 "EnjinCloud\\Events\\TransactionBroadcast",
                                                                 {"project", "asset", "wallet"})},
            {models::EventType::TRANSACTION_CANCELED,     create(models::EventType::TRANSACTION_CANCELED,
                                                                 "EnjinCloud\\Events\\TransactionCanceled",
                                                                 {"project", "asset", "wallet"})},
            {models::EventType::TRANSACTION_DROPPED,      create(models::EventType::TRANSACTION_DROPPED,
                                                                 "EnjinCloud\\Events\\TransactionDropped",
                                                                 {"project", "asset", "wallet"})},
            {models::EventType::TRANSACTION_EXECUTED,     create(models::EventType::TRANSACTION_EXECUTED,
                                                                 "EnjinCloud\\Events\\TransactionExecuted",
                                                                 {"project", "asset", "wallet"})},
            {models::EventType::TRANSACTION_FAILED,       create(models::EventType::TRANSACTION_FAILED,
                                                                 "EnjinCloud\\Events\\TransactionFailed",
                                                                 {"project", "asset", "wallet"})},
            {models::EventType::TRANSACTION_PENDING,      create(models::EventType::TRANSACTION_PENDING,
                                                                 "EnjinCloud\\Events\\TransactionPending",
                                                                 {"project", "asset", "wallet"})},
            {models::EventType::TRANSACTION_PROCESSING,   create(models::EventType::TRANSACTION_PROCESSING,
                                                                 "EnjinCloud\\Events\\TransactionProcessing",
                                                                 {"project", "asset", "wallet"})},
            {models::EventType::TRANSACTION_UPDATED,      create(models::EventType::TRANSACTION_UPDATED,
                                                                 "EnjinCloud\\Events\\TransactionUpdated",
                                                                 {"project", "asset", "wallet"})},
    };
};

}

#endif //ENJINCPPSDK_EVENTTYPEDEF_HPP
