#include "enjinsdk/models/NotificationEvent.hpp"

#include <utility>

namespace enjin::sdk::models {

NotificationEvent::NotificationEvent(EventType type, std::string channel, std::string message)
        : type(type), channel(std::move(channel)), message(std::move(message)) {
}

EventType NotificationEvent::get_type() const {
    return type;
}

const std::string& NotificationEvent::get_channel() const {
    return channel;
}

const std::string& NotificationEvent::get_message() const {
    return message;
}

bool NotificationEvent::operator==(const NotificationEvent& rhs) const {
    return type == rhs.type &&
           channel == rhs.channel &&
           message == rhs.message;
}

bool NotificationEvent::operator!=(const NotificationEvent& rhs) const {
    return !(rhs == *this);
}

}
