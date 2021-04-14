#include "enjinsdk/EventListenerRegistration.hpp"

#include <algorithm>
#include <utility>

namespace enjin::sdk::events {

EventListenerRegistration::EventListenerRegistration(std::shared_ptr<IEventListener> listener)
        : EventListenerRegistration(std::move(listener), ALLOW_ALL_MATCHER) {
}

EventListenerRegistration::EventListenerRegistration(std::shared_ptr<IEventListener> listener,
                                                     std::function<bool(models::EventType)> matcher)
        : listener(std::move(listener)), matcher(std::move(matcher)) {
}

IEventListener& EventListenerRegistration::get_listener() const {
    return *listener;
}

const std::function<bool(models::EventType)>& EventListenerRegistration::get_matcher() const {
    return matcher;
}

EventListenerRegistration::RegistrationListenerConfiguration::RegistrationListenerConfiguration(
        std::shared_ptr<IEventListener> listener) : listener(std::move(listener)) {
}

EventListenerRegistration::RegistrationListenerConfiguration&
EventListenerRegistration::RegistrationListenerConfiguration::with_matcher(
        std::function<bool(models::EventType)> matcher) {
    EventListenerRegistration::RegistrationListenerConfiguration::matcher = std::move(matcher);
    return *this;
}

EventListenerRegistration::RegistrationListenerConfiguration&
EventListenerRegistration::RegistrationListenerConfiguration::with_allowed_events(
        const std::vector<models::EventType>& types) {
    matcher = [types](models::EventType type) {
        return std::any_of(types.begin(), types.end(), [type](models::EventType t) {
            return t == type; // Any of the allowed events equal the type which occurred
        });
    };
    return *this;
}

EventListenerRegistration::RegistrationListenerConfiguration&
EventListenerRegistration::RegistrationListenerConfiguration::with_ignored_events(
        const std::vector<models::EventType>& types) {
    matcher = [types](models::EventType type) {
        return std::all_of(types.begin(), types.end(), [type](models::EventType t) {
            return t != type; // All of the ignored events do not equal the type which occurred
        });
    };
    return *this;
}

std::unique_ptr<EventListenerRegistration>
EventListenerRegistration::RegistrationListenerConfiguration::create() {
    return std::unique_ptr<EventListenerRegistration>(new EventListenerRegistration(std::move(listener), matcher));
}

const IEventListener& EventListenerRegistration::RegistrationListenerConfiguration::get_listener() const {
    return *listener;
}

}
