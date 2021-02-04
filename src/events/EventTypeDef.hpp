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
            {models::EventType::UNKNOWN, create(models::EventType::UNKNOWN,
                                                "",
                                                {""})},
            {models::EventType::APP_CREATED, create(models::EventType::APP_CREATED,
                                                    "EnjinCloud\\Events\\AppCreated",
                                                    {"app"})},
            {models::EventType::APP_DELETED, create(models::EventType::APP_DELETED,
                                                    "EnjinCloud\\Events\\AppDeleted",
                                                    {"app"})},
            {models::EventType::APP_LINKED, create(models::EventType::APP_LINKED,
                                                   "EnjinCloud\\Events\\AppLinked",
                                                   {"app", "wallet"})},
            {models::EventType::APP_LOCKED, create(models::EventType::APP_LOCKED,
                                                   "EnjinCloud\\Events\\AppLocked",
                                                   {"app"})},
            {models::EventType::APP_UNLINKED, create(models::EventType::APP_UNLINKED,
                                                     "EnjinCloud\\Events\\AppUnlinked",
                                                     {"app", "wallet"})},
            {models::EventType::APP_UNLOCKED, create(models::EventType::APP_UNLOCKED,
                                                     "EnjinCloud\\Events\\AppUnlocked",
                                                     {"app"})},
            {models::EventType::APP_UPDATED, create(models::EventType::APP_UPDATED,
                                                    "EnjinCloud\\Events\\AppUpdated",
                                                    {"app"})},
            {models::EventType::BLOCKCHAIN_LOG_PROCESSED, create(models::EventType::BLOCKCHAIN_LOG_PROCESSED,
                                                                 "EnjinCloud\\Events\\BlockchainLogProcessed",
                                                                 {"app", "token", "wallet"})},
            {models::EventType::MESSAGE_PROCESSED, create(models::EventType::MESSAGE_PROCESSED,
                                                          "EnjinCloud\\Events\\MessageProcessed",
                                                          {"app", "token", "wallet"})},
            {models::EventType::PLAYER_CREATED, create(models::EventType::PLAYER_CREATED,
                                                       "EnjinCloud\\Events\\PlayerCreated",
                                                       {"app", "player"})},
            {models::EventType::PLAYER_DELETED, create(models::EventType::PLAYER_DELETED,
                                                       "EnjinCloud\\Events\\PlayerDeleted",
                                                       {"app", "player"})},
            {models::EventType::PLAYER_LINKED, create(models::EventType::PLAYER_LINKED,
                                                      "EnjinCloud\\Events\\PlayerLinked",
                                                      {"app", "player", "wallet"})},
            {models::EventType::PLAYER_UNLINKED, create(models::EventType::PLAYER_UNLINKED,
                                                        "EnjinCloud\\Events\\PlayerUnlinked",
                                                        {"app", "player", "wallet"})},
            {models::EventType::PLAYER_UPDATED, create(models::EventType::PLAYER_UPDATED,
                                                       "EnjinCloud\\Events\\PlayerUpdated",
                                                       {"app", "player"})},
            {models::EventType::TOKEN_CREATED, create(models::EventType::TOKEN_CREATED,
                                                      "EnjinCloud\\Events\\TokenCreated",
                                                      {"app", "token", "wallet"})},
            {models::EventType::TOKEN_MELTED, create(models::EventType::TOKEN_MELTED,
                                                     "EnjinCloud\\Events\\TokenMelted",
                                                     {"app", "token", "wallet"})},
            {models::EventType::TOKEN_MINTED, create(models::EventType::TOKEN_MINTED,
                                                     "EnjinCloud\\Events\\TokenMinted",
                                                     {"app", "token", "wallet"})},
            {models::EventType::TOKEN_TRANSFERRED, create(models::EventType::TOKEN_TRANSFERRED,
                                                          "EnjinCloud\\Events\\TokenTransferred",
                                                          {"app", "token", "wallet"})},
            {models::EventType::TOKEN_UPDATED, create(models::EventType::TOKEN_UPDATED,
                                                      "EnjinCloud\\Events\\TokenUpdated",
                                                      {"app", "token", "wallet"})},
            {models::EventType::TRADE_COMPLETED, create(models::EventType::TRADE_COMPLETED,
                                                        "EnjinCloud\\Events\\TradeCompleted",
                                                        {"app", "token", "wallet"})},
            {models::EventType::TRADE_CREATED, create(models::EventType::TRADE_CREATED,
                                                      "EnjinCloud\\Events\\TradeCreated",
                                                      {"app", "token", "wallet"})},
            {models::EventType::TRANSACTION_BROADCAST, create(models::EventType::TRANSACTION_BROADCAST,
                                                              "EnjinCloud\\Events\\TransactionBroadcast",
                                                              {"app", "token", "wallet"})},
            {models::EventType::TRANSACTION_CANCELED, create(models::EventType::TRANSACTION_CANCELED,
                                                             "EnjinCloud\\Events\\TransactionCanceled",
                                                             {"app", "token", "wallet"})},
            {models::EventType::TRANSACTION_DROPPED, create(models::EventType::TRANSACTION_DROPPED,
                                                            "EnjinCloud\\Events\\TransactionDropped",
                                                            {"app", "token", "wallet"})},
            {models::EventType::TRANSACTION_EXECUTED, create(models::EventType::TRANSACTION_EXECUTED,
                                                             "EnjinCloud\\Events\\TransactionExecuted",
                                                             {"app", "token", "wallet"})},
            {models::EventType::TRANSACTION_FAILED, create(models::EventType::TRANSACTION_FAILED,
                                                           "EnjinCloud\\Events\\TransactionFailed",
                                                           {"app", "token", "wallet"})},
            {models::EventType::TRANSACTION_PENDING, create(models::EventType::TRANSACTION_PENDING,
                                                            "EnjinCloud\\Events\\TransactionPending",
                                                            {"app", "token", "wallet"})},
            {models::EventType::TRANSACTION_PROCESSING, create(models::EventType::TRANSACTION_PROCESSING,
                                                               "EnjinCloud\\Events\\TransactionProcessing",
                                                               {"app", "token", "wallet"})},
            {models::EventType::TRANSACTION_UPDATED, create(models::EventType::TRANSACTION_UPDATED,
                                                            "EnjinCloud\\Events\\TransactionUpdated",
                                                            {"app", "token", "wallet"})},
    };
};

}

#endif //ENJINCPPSDK_EVENTTYPEDEF_HPP
