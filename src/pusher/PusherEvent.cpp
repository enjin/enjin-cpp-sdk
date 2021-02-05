#include "enjinsdk/internal/pusher/PusherEvent.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::pusher {

void PusherEvent::deserialize(const std::string& json) {
    rapidjson::Document document;
    document.Parse(json.c_str());
    if (document.IsObject()) {
        if (document.HasMember(USER_ID_KEY) && document[USER_ID_KEY].IsString()) {
            user_id.emplace(document[USER_ID_KEY].GetString());
        }
        if (document.HasMember(CHANNEL_NAME_KEY) && document[CHANNEL_NAME_KEY].IsString()) {
            channel_name.emplace(document[CHANNEL_NAME_KEY].GetString());
        }
        if (document.HasMember(EVENT_NAME_KEY) && document[EVENT_NAME_KEY].IsString()) {
            event_name.emplace(document[EVENT_NAME_KEY].GetString());
        }
        if (document.HasMember(DATA_KEY) && document[DATA_KEY].IsString()) {
            data.emplace(document[DATA_KEY].GetString());
        }
    }
}

const std::optional<std::string>& PusherEvent::get_user_id() const {
    return user_id;
}

const std::optional<std::string>& PusherEvent::get_channel_name() const {
    return channel_name;
}

const std::optional<std::string>& PusherEvent::get_event_name() const {
    return event_name;
}

const std::optional<std::string>& PusherEvent::get_data() const {
    return data;
}

bool PusherEvent::operator==(const PusherEvent& rhs) const {
    return user_id == rhs.user_id &&
           channel_name == rhs.channel_name &&
           event_name == rhs.event_name &&
           data == rhs.data;
}

bool PusherEvent::operator!=(const PusherEvent& rhs) const {
    return !(rhs == *this);
}

}
