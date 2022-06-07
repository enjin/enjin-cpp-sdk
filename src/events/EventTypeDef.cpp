/* Copyright 2021 Enjin Pte. Ltd.
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

EventTypeDef::EventTypeDef() : type(models::EventType::Unknown), channels({}), name(utils::serialize_event_type(type)) {
}

EventTypeDef::EventTypeDef(models::EventType type, std::string key, std::vector<std::string> channels)
        : type(type),
          key(std::move(key)),
          channels(std::move(channels)),
          name(utils::serialize_event_type(type)) {
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
    values.reserve(map.size());

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
           : *EventTypeDef::map[models::EventType::Unknown];
}

EventTypeDef EventTypeDef::get_from_key(const std::string& key) {
    std::vector<EventTypeDef> values = EventTypeDef::values();
    auto iter = std::find_if(values.begin(), values.end(), [key](const EventTypeDef& def) {
        return key == def.key;
    });

    return iter != values.end()
           ? *iter
           : *EventTypeDef::map[models::EventType::Unknown];
}

std::unique_ptr<EventTypeDef>
EventTypeDef::create(models::EventType type, std::string key, std::vector<std::string> channels) {
    return std::make_unique<EventTypeDef>(type, std::move(key), std::move(channels));
}

std::map<models::EventType, std::unique_ptr<EventTypeDef>> EventTypeDef::create_map() {
    std::map<models::EventType, std::unique_ptr<EventTypeDef>> map;

    map.emplace(models::EventType::Unknown, create(models::EventType::Unknown,
                                                   "",
                                                   {}));
    map.emplace(models::EventType::ProjectCreated, create(models::EventType::ProjectCreated,
                                                          "EnjinCloud\\Events\\ProjectCreated",
                                                          {"project"}));
    map.emplace(models::EventType::ProjectDeleted, create(models::EventType::ProjectDeleted,
                                                          "EnjinCloud\\Events\\ProjectDeleted",
                                                          {"project"}));
    map.emplace(models::EventType::ProjectLinked, create(models::EventType::ProjectLinked,
                                                         "EnjinCloud\\Events\\ProjectLinked",
                                                         {"project", "wallet"}));
    map.emplace(models::EventType::ProjectLocked, create(models::EventType::ProjectLocked,
                                                         "EnjinCloud\\Events\\ProjectLocked",
                                                         {"project"}));
    map.emplace(models::EventType::ProjectUnlinked, create(models::EventType::ProjectUnlinked,
                                                           "EnjinCloud\\Events\\ProjectUnlinked",
                                                           {"project", "wallet"}));
    map.emplace(models::EventType::ProjectUnlocked, create(models::EventType::ProjectUnlocked,
                                                           "EnjinCloud\\Events\\ProjectUnlocked",
                                                           {"project"}));
    map.emplace(models::EventType::ProjectUpdated, create(models::EventType::ProjectUpdated,
                                                          "EnjinCloud\\Events\\ProjectUpdated",
                                                          {"project"}));
    map.emplace(models::EventType::BlockchainLogProcessed, create(models::EventType::BlockchainLogProcessed,
                                                                  "EnjinCloud\\Events\\BlockchainLogProcessed",
                                                                  {"project", "asset", "wallet"}));
    map.emplace(models::EventType::MessageProcessed, create(models::EventType::MessageProcessed,
                                                            "EnjinCloud\\Events\\MessageProcessed",
                                                            {"project", "asset", "wallet"}));
    map.emplace(models::EventType::PlayerCreated, create(models::EventType::PlayerCreated,
                                                         "EnjinCloud\\Events\\PlayerCreated",
                                                         {"project", "player"}));
    map.emplace(models::EventType::PlayerDeleted, create(models::EventType::PlayerDeleted,
                                                         "EnjinCloud\\Events\\PlayerDeleted",
                                                         {"project", "player"}));
    map.emplace(models::EventType::PlayerLinked, create(models::EventType::PlayerLinked,
                                                        "EnjinCloud\\Events\\PlayerLinked",
                                                        {"project", "player", "wallet"}));
    map.emplace(models::EventType::PlayerUnlinked, create(models::EventType::PlayerUnlinked,
                                                          "EnjinCloud\\Events\\PlayerUnlinked",
                                                          {"project", "player", "wallet"}));
    map.emplace(models::EventType::PlayerUpdated, create(models::EventType::PlayerUpdated,
                                                         "EnjinCloud\\Events\\PlayerUpdated",
                                                         {"project", "player"}));
    map.emplace(models::EventType::AssetCreated, create(models::EventType::AssetCreated,
                                                        "EnjinCloud\\Events\\AssetCreated",
                                                        {"project", "asset", "wallet"}));
    map.emplace(models::EventType::AssetMelted, create(models::EventType::AssetMelted,
                                                       "EnjinCloud\\Events\\AssetMelted",
                                                       {"project", "asset", "wallet"}));
    map.emplace(models::EventType::AssetMinted, create(models::EventType::AssetMinted,
                                                       "EnjinCloud\\Events\\AssetMinted",
                                                       {"project", "asset", "wallet"}));
    map.emplace(models::EventType::AssetTransferred, create(models::EventType::AssetTransferred,
                                                            "EnjinCloud\\Events\\AssetTransferred",
                                                            {"project", "asset", "wallet"}));
    map.emplace(models::EventType::AssetUpdated, create(models::EventType::AssetUpdated,
                                                        "EnjinCloud\\Events\\AssetUpdated",
                                                        {"project", "asset", "wallet"}));
    map.emplace(models::EventType::TradeAssetCompleted, create(models::EventType::TradeAssetCompleted,
                                                               "EnjinCloud\\Events\\TradeAssetCompleted",
                                                               {"project", "asset", "wallet"}));
    map.emplace(models::EventType::TradeAssetCreated, create(models::EventType::TradeAssetCreated,
                                                             "EnjinCloud\\Events\\TradeAssetCreated",
                                                             {"project", "asset", "wallet"}));
    map.emplace(models::EventType::TransactionBroadcast, create(models::EventType::TransactionBroadcast,
                                                                "EnjinCloud\\Events\\TransactionBroadcast",
                                                                {"project", "asset", "wallet"}));
    map.emplace(models::EventType::TransactionCanceled, create(models::EventType::TransactionCanceled,
                                                               "EnjinCloud\\Events\\TransactionCanceled",
                                                               {"project", "asset", "wallet"}));
    map.emplace(models::EventType::TransactionDropped, create(models::EventType::TransactionDropped,
                                                              "EnjinCloud\\Events\\TransactionDropped",
                                                              {"project", "asset", "wallet"}));
    map.emplace(models::EventType::TransactionExecuted, create(models::EventType::TransactionExecuted,
                                                               "EnjinCloud\\Events\\TransactionExecuted",
                                                               {"project", "asset", "wallet"}));
    map.emplace(models::EventType::TransactionFailed, create(models::EventType::TransactionFailed,
                                                             "EnjinCloud\\Events\\TransactionFailed",
                                                             {"project", "asset", "wallet"}));
    map.emplace(models::EventType::TransactionPending, create(models::EventType::TransactionPending,
                                                              "EnjinCloud\\Events\\TransactionPending",
                                                              {"project", "asset", "wallet"}));
    map.emplace(models::EventType::TransactionProcessing, create(models::EventType::TransactionProcessing,
                                                                 "EnjinCloud\\Events\\TransactionProcessing",
                                                                 {"project", "asset", "wallet"}));
    map.emplace(models::EventType::TransactionUpdated, create(models::EventType::TransactionUpdated,
                                                              "EnjinCloud\\Events\\TransactionUpdated",
                                                              {"project", "asset", "wallet"}));

    return map;
}

}
