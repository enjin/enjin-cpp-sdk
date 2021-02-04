#include "EventTypeDef.hpp"

#include "EnumUtils.hpp"
#include "StringUtils.hpp"
#include <algorithm>
#include <utility>

namespace enjin::sdk::events {

EventTypeDef::EventTypeDef(models::EventType type, std::string key, std::vector<std::string> channels)
        : type(type), key(std::move(key)), channels(std::move(channels)), name(utils::serialize_event_type(type)) {
}

bool EventTypeDef::in(const std::vector<models::EventType>& types) {
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

std::vector<EventTypeDef> EventTypeDef::filter_by_channel_types(const std::vector<std::string>& channels) {
    std::vector<EventTypeDef> defs;

    for (auto& channel : channels) {
        for (auto& def : EventTypeDef::values()) {
            auto iter = std::find(def.channels.begin(), def.channels.end(), utils::to_lower(channel));
            if (iter != def.channels.end()) {
                defs.push_back(def);
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

EventTypeDef*
EventTypeDef::create(models::EventType type, const std::string& key, std::vector<std::string> channels) {
    return new EventTypeDef(type, key, std::move(channels));
}

}
