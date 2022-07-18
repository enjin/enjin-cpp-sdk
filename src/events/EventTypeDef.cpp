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

#include "enjinsdk/EnumUtils.hpp"
#include "enjinsdk_utils/StringUtils.hpp"
#include <algorithm>

/* The namespace for utilities from enjin::utils is used explicitly to avoid collision with enjin::sdk::utils with some
 * compilers.
 */
using namespace enjin::sdk::events;
using namespace enjin::sdk::models;
using namespace enjin::sdk::utils;
using namespace enjin::utils;

EventTypeDef::EventTypeDef()
        : type(EventType::Unknown),
          channels({}),
          name(EnumUtils::serialize_event_type(type)) {
}

EventTypeDef::EventTypeDef(EventType type, std::string key, std::vector<std::string> channels)
        : type(type),
          key(std::move(key)),
          channels(std::move(channels)),
          name(EnumUtils::serialize_event_type(type)) {
}

bool EventTypeDef::in(const std::vector<EventType>& types) const {
    return std::find_if(types.begin(), types.end(), [this](EventType t) {
        return t == type;
    }) != types.end();
}

EventType EventTypeDef::get_type() const {
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
    return type == rhs.type
           && key == rhs.key
           && channels == rhs.channels
           && name == rhs.name;
}

bool EventTypeDef::operator!=(const EventTypeDef& rhs) const {
    return !(rhs == *this);
}

std::vector<EventTypeDef> EventTypeDef::values() {
    std::vector<EventTypeDef> values;
    values.reserve(map.size());

    for (auto& [k, v]: map) {
        values.push_back(*v);
    }

    return values;
}

std::vector<EventTypeDef> EventTypeDef::filter_by_channel_type(const std::string& channel) {
    std::vector<EventTypeDef> defs;

    for (const auto& def: EventTypeDef::values()) {
        for (const auto& key: def.channels) {
            if (to_lower(channel).find(key) != std::string::npos) {
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
           : *EventTypeDef::map[EventType::Unknown];
}

EventTypeDef EventTypeDef::get_from_key(const std::string& key) {
    std::vector<EventTypeDef> values = EventTypeDef::values();
    auto iter = std::find_if(values.begin(), values.end(), [key](const EventTypeDef& def) {
        return key == def.key;
    });

    return iter != values.end()
           ? *iter
           : *EventTypeDef::map[EventType::Unknown];
}

std::unique_ptr<EventTypeDef> EventTypeDef::create(EventType type, std::string key, std::vector<std::string> channels) {
    return std::make_unique<EventTypeDef>(type, std::move(key), std::move(channels));
}

std::map<EventType, std::unique_ptr<EventTypeDef>> EventTypeDef::create_map() {
    std::map<EventType, std::unique_ptr<EventTypeDef>> map;

    map.emplace(EventType::Unknown, create(EventType::Unknown,
                                           "",
                                           {}));
    map.emplace(EventType::ProjectCreated, create(EventType::ProjectCreated,
                                                  "EnjinCloud\\Events\\ProjectCreated",
                                                  {"project"}));
    map.emplace(EventType::ProjectDeleted, create(EventType::ProjectDeleted,
                                                  "EnjinCloud\\Events\\ProjectDeleted",
                                                  {"project"}));
    map.emplace(EventType::ProjectLinked, create(EventType::ProjectLinked,
                                                 "EnjinCloud\\Events\\ProjectLinked",
                                                 {"project", "wallet"}));
    map.emplace(EventType::ProjectLocked, create(EventType::ProjectLocked,
                                                 "EnjinCloud\\Events\\ProjectLocked",
                                                 {"project"}));
    map.emplace(EventType::ProjectUnlinked, create(EventType::ProjectUnlinked,
                                                   "EnjinCloud\\Events\\ProjectUnlinked",
                                                   {"project", "wallet"}));
    map.emplace(EventType::ProjectUnlocked, create(EventType::ProjectUnlocked,
                                                   "EnjinCloud\\Events\\ProjectUnlocked",
                                                   {"project"}));
    map.emplace(EventType::ProjectUpdated, create(EventType::ProjectUpdated,
                                                  "EnjinCloud\\Events\\ProjectUpdated",
                                                  {"project"}));
    map.emplace(EventType::BlockchainLogProcessed, create(EventType::BlockchainLogProcessed,
                                                          "EnjinCloud\\Events\\BlockchainLogProcessed",
                                                          {"project", "asset", "wallet"}));
    map.emplace(EventType::MessageProcessed, create(EventType::MessageProcessed,
                                                    "EnjinCloud\\Events\\MessageProcessed",
                                                    {"project", "asset", "wallet"}));
    map.emplace(EventType::PlayerCreated, create(EventType::PlayerCreated,
                                                 "EnjinCloud\\Events\\PlayerCreated",
                                                 {"project", "player"}));
    map.emplace(EventType::PlayerDeleted, create(EventType::PlayerDeleted,
                                                 "EnjinCloud\\Events\\PlayerDeleted",
                                                 {"project", "player"}));
    map.emplace(EventType::PlayerLinked, create(EventType::PlayerLinked,
                                                "EnjinCloud\\Events\\PlayerLinked",
                                                {"project", "player", "wallet"}));
    map.emplace(EventType::PlayerUnlinked, create(EventType::PlayerUnlinked,
                                                  "EnjinCloud\\Events\\PlayerUnlinked",
                                                  {"project", "player", "wallet"}));
    map.emplace(EventType::PlayerUpdated, create(EventType::PlayerUpdated,
                                                 "EnjinCloud\\Events\\PlayerUpdated",
                                                 {"project", "player"}));
    map.emplace(EventType::AssetCreated, create(EventType::AssetCreated,
                                                "EnjinCloud\\Events\\AssetCreated",
                                                {"project", "asset", "wallet"}));
    map.emplace(EventType::AssetMelted, create(EventType::AssetMelted,
                                               "EnjinCloud\\Events\\AssetMelted",
                                               {"project", "asset", "wallet"}));
    map.emplace(EventType::AssetMinted, create(EventType::AssetMinted,
                                               "EnjinCloud\\Events\\AssetMinted",
                                               {"project", "asset", "wallet"}));
    map.emplace(EventType::AssetTransferred, create(EventType::AssetTransferred,
                                                    "EnjinCloud\\Events\\AssetTransferred",
                                                    {"project", "asset", "wallet"}));
    map.emplace(EventType::AssetUpdated, create(EventType::AssetUpdated,
                                                "EnjinCloud\\Events\\AssetUpdated",
                                                {"project", "asset", "wallet"}));
    map.emplace(EventType::TradeAssetCompleted, create(EventType::TradeAssetCompleted,
                                                       "EnjinCloud\\Events\\TradeAssetCompleted",
                                                       {"project", "asset", "wallet"}));
    map.emplace(EventType::TradeAssetCreated, create(EventType::TradeAssetCreated,
                                                     "EnjinCloud\\Events\\TradeAssetCreated",
                                                     {"project", "asset", "wallet"}));
    map.emplace(EventType::TransactionBroadcast, create(EventType::TransactionBroadcast,
                                                        "EnjinCloud\\Events\\TransactionBroadcast",
                                                        {"project", "asset", "wallet"}));
    map.emplace(EventType::TransactionCanceled, create(EventType::TransactionCanceled,
                                                       "EnjinCloud\\Events\\TransactionCanceled",
                                                       {"project", "asset", "wallet"}));
    map.emplace(EventType::TransactionDropped, create(EventType::TransactionDropped,
                                                      "EnjinCloud\\Events\\TransactionDropped",
                                                      {"project", "asset", "wallet"}));
    map.emplace(EventType::TransactionExecuted, create(EventType::TransactionExecuted,
                                                       "EnjinCloud\\Events\\TransactionExecuted",
                                                       {"project", "asset", "wallet"}));
    map.emplace(EventType::TransactionFailed, create(EventType::TransactionFailed,
                                                     "EnjinCloud\\Events\\TransactionFailed",
                                                     {"project", "asset", "wallet"}));
    map.emplace(EventType::TransactionPending, create(EventType::TransactionPending,
                                                      "EnjinCloud\\Events\\TransactionPending",
                                                      {"project", "asset", "wallet"}));
    map.emplace(EventType::TransactionProcessing, create(EventType::TransactionProcessing,
                                                         "EnjinCloud\\Events\\TransactionProcessing",
                                                         {"project", "asset", "wallet"}));
    map.emplace(EventType::TransactionUpdated, create(EventType::TransactionUpdated,
                                                      "EnjinCloud\\Events\\TransactionUpdated",
                                                      {"project", "asset", "wallet"}));

    return map;
}
