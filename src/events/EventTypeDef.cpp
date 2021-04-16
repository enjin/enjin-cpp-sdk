/* Copyright 2021 Enjin Pte Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "EventTypeDef.hpp"

#include "EnumUtils.hpp"
#include "enjinsdk_utils/StringUtils.hpp"
#include <algorithm>

namespace enjin::sdk::events {

EventTypeDef::EventTypeDef() : type(models::EventType::UNKNOWN), channels({}), name(utils::serialize_event_type(type)) {
}

EventTypeDef::EventTypeDef(models::EventType type, std::string key, std::vector<std::string> channels)
        : type(type), key(std::move(key)), channels(std::move(channels)), name(utils::serialize_event_type(type)) {
}

bool EventTypeDef::in(const std::vector<models::EventType>& types) const {
    return std::find_if(types.begin(), types.end(), [this](models::EventType t) {
        return t == type;
    }) != types.end();
}

models::EventType EventTypeDef::get_type() const {
    return type;
}

const std::string& EventTypeDef::get_key() const {
    return key;
}

const std::vector<std::string>& EventTypeDef::get_channels() const {
    return channels;
}

const std::string& EventTypeDef::get_name() const {
    return name;
}

bool EventTypeDef::operator==(const EventTypeDef& rhs) const {
    return type == rhs.type &&
           key == rhs.key &&
           channels == rhs.channels &&
           name == rhs.name;
}

bool EventTypeDef::operator!=(const EventTypeDef& rhs) const {
    return !(rhs == *this);
}

std::vector<EventTypeDef> EventTypeDef::values() {
    std::vector<EventTypeDef> values;
    for (auto&[k, v] : map) {
        values.push_back(*v);
    }
    return values;
}

std::vector<EventTypeDef> EventTypeDef::filter_by_channel_type(const std::string& channel) {
    std::vector<EventTypeDef> defs;

    for (const auto& def : EventTypeDef::values()) {
        for (const auto& key : def.channels) {
            if (enjin::utils::to_lower(channel).find(key) != std::string::npos) {
                defs.push_back(def);
                break;
            }
        }
    }

    return defs;
}

EventTypeDef EventTypeDef::get_from_name(const std::string& name) {
    std::vector<EventTypeDef> values = EventTypeDef::values();
    auto iter = std::find_if(values.begin(), values.end(), [name](const EventTypeDef& def) {
        return name == def.name;
    });

    return iter != values.end()
           ? *iter
           : *EventTypeDef::map[models::EventType::UNKNOWN];
}

EventTypeDef EventTypeDef::get_from_key(const std::string& key) {
    std::vector<EventTypeDef> values = EventTypeDef::values();
    auto iter = std::find_if(values.begin(), values.end(), [key](const EventTypeDef& def) {
        return key == def.key;
    });

    return iter != values.end()
           ? *iter
           : *EventTypeDef::map[models::EventType::UNKNOWN];
}

std::unique_ptr<EventTypeDef>
EventTypeDef::create(models::EventType type, const std::string& key, std::vector<std::string> channels) {
    return std::make_unique<EventTypeDef>(type, key, std::move(channels));
}

std::map<models::EventType, std::unique_ptr<EventTypeDef>> EventTypeDef::create_map() {
    std::map<models::EventType, std::unique_ptr<EventTypeDef>> map;

    map.emplace(models::EventType::UNKNOWN, create(models::EventType::UNKNOWN,
                                                   "",
                                                   {}));
    map.emplace(models::EventType::PROJECT_CREATED, create(models::EventType::PROJECT_CREATED,
                                                           "EnjinCloud\\Events\\ProjectCreated",
                                                           {"project"}));
    map.emplace(models::EventType::PROJECT_DELETED, create(models::EventType::PROJECT_DELETED,
                                                           "EnjinCloud\\Events\\ProjectDeleted",
                                                           {"project"}));
    map.emplace(models::EventType::PROJECT_LINKED, create(models::EventType::PROJECT_LINKED,
                                                          "EnjinCloud\\Events\\ProjectLinked",
                                                          {"project", "wallet"}));
    map.emplace(models::EventType::PROJECT_LOCKED, create(models::EventType::PROJECT_LOCKED,
                                                          "EnjinCloud\\Events\\ProjectLocked",
                                                          {"project"}));
    map.emplace(models::EventType::PROJECT_UNLINKED, create(models::EventType::PROJECT_UNLINKED,
                                                            "EnjinCloud\\Events\\ProjectUnlinked",
                                                            {"project", "wallet"}));
    map.emplace(models::EventType::PROJECT_UNLOCKED, create(models::EventType::PROJECT_UNLOCKED,
                                                            "EnjinCloud\\Events\\ProjectUnlocked",
                                                            {"project"}));
    map.emplace(models::EventType::PROJECT_UPDATED, create(models::EventType::PROJECT_UPDATED,
                                                           "EnjinCloud\\Events\\ProjectUpdated",
                                                           {"project"}));
    map.emplace(models::EventType::BLOCKCHAIN_LOG_PROCESSED, create(models::EventType::BLOCKCHAIN_LOG_PROCESSED,
                                                                    "EnjinCloud\\Events\\BlockchainLogProcessed",
                                                                    {"project", "asset", "wallet"}));
    map.emplace(models::EventType::MESSAGE_PROCESSED, create(models::EventType::MESSAGE_PROCESSED,
                                                             "EnjinCloud\\Events\\MessageProcessed",
                                                             {"project", "asset", "wallet"}));
    map.emplace(models::EventType::PLAYER_CREATED, create(models::EventType::PLAYER_CREATED,
                                                          "EnjinCloud\\Events\\PlayerCreated",
                                                          {"project", "player"}));
    map.emplace(models::EventType::PLAYER_DELETED, create(models::EventType::PLAYER_DELETED,
                                                          "EnjinCloud\\Events\\PlayerDeleted",
                                                          {"project", "player"}));
    map.emplace(models::EventType::PLAYER_LINKED, create(models::EventType::PLAYER_LINKED,
                                                         "EnjinCloud\\Events\\PlayerLinked",
                                                         {"project", "player", "wallet"}));
    map.emplace(models::EventType::PLAYER_UNLINKED, create(models::EventType::PLAYER_UNLINKED,
                                                           "EnjinCloud\\Events\\PlayerUnlinked",
                                                           {"project", "player", "wallet"}));
    map.emplace(models::EventType::PLAYER_UPDATED, create(models::EventType::PLAYER_UPDATED,
                                                          "EnjinCloud\\Events\\PlayerUpdated",
                                                          {"project", "player"}));
    map.emplace(models::EventType::ASSET_CREATED, create(models::EventType::ASSET_CREATED,
                                                         "EnjinCloud\\Events\\AssetCreated",
                                                         {"project", "asset", "wallet"}));
    map.emplace(models::EventType::ASSET_MELTED, create(models::EventType::ASSET_MELTED,
                                                        "EnjinCloud\\Events\\AssetMelted",
                                                        {"project", "asset", "wallet"}));
    map.emplace(models::EventType::ASSET_MINTED, create(models::EventType::ASSET_MINTED,
                                                        "EnjinCloud\\Events\\AssetMinted",
                                                        {"project", "asset", "wallet"}));
    map.emplace(models::EventType::ASSET_TRANSFERRED, create(models::EventType::ASSET_TRANSFERRED,
                                                             "EnjinCloud\\Events\\AssetTransferred",
                                                             {"project", "asset", "wallet"}));
    map.emplace(models::EventType::ASSET_UPDATED, create(models::EventType::ASSET_UPDATED,
                                                         "EnjinCloud\\Events\\AssetUpdated",
                                                         {"project", "asset", "wallet"}));
    map.emplace(models::EventType::TRADE_COMPLETED, create(models::EventType::TRADE_COMPLETED,
                                                           "EnjinCloud\\Events\\TradeCompleted",
                                                           {"project", "asset", "wallet"}));
    map.emplace(models::EventType::TRADE_CREATED, create(models::EventType::TRADE_CREATED,
                                                         "EnjinCloud\\Events\\TradeCreated",
                                                         {"project", "asset", "wallet"}));
    map.emplace(models::EventType::TRANSACTION_BROADCAST, create(models::EventType::TRANSACTION_BROADCAST,
                                                                 "EnjinCloud\\Events\\TransactionBroadcast",
                                                                 {"project", "asset", "wallet"}));
    map.emplace(models::EventType::TRANSACTION_CANCELED, create(models::EventType::TRANSACTION_CANCELED,
                                                                "EnjinCloud\\Events\\TransactionCanceled",
                                                                {"project", "asset", "wallet"}));
    map.emplace(models::EventType::TRANSACTION_DROPPED, create(models::EventType::TRANSACTION_DROPPED,
                                                               "EnjinCloud\\Events\\TransactionDropped",
                                                               {"project", "asset", "wallet"}));
    map.emplace(models::EventType::TRANSACTION_EXECUTED, create(models::EventType::TRANSACTION_EXECUTED,
                                                                "EnjinCloud\\Events\\TransactionExecuted",
                                                                {"project", "asset", "wallet"}));
    map.emplace(models::EventType::TRANSACTION_FAILED, create(models::EventType::TRANSACTION_FAILED,
                                                              "EnjinCloud\\Events\\TransactionFailed",
                                                              {"project", "asset", "wallet"}));
    map.emplace(models::EventType::TRANSACTION_PENDING, create(models::EventType::TRANSACTION_PENDING,
                                                               "EnjinCloud\\Events\\TransactionPending",
                                                               {"project", "asset", "wallet"}));
    map.emplace(models::EventType::TRANSACTION_PROCESSING, create(models::EventType::TRANSACTION_PROCESSING,
                                                                  "EnjinCloud\\Events\\TransactionProcessing",
                                                                  {"project", "asset", "wallet"}));
    map.emplace(models::EventType::TRANSACTION_UPDATED, create(models::EventType::TRANSACTION_UPDATED,
                                                               "EnjinCloud\\Events\\TransactionUpdated",
                                                               {"project", "asset", "wallet"}));

    return map;
}

}
