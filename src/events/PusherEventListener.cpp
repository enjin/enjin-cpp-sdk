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

#include "PusherEventListener.hpp"

#include "EventTypeDef.hpp"
#include <sstream>
#include <string>

namespace enjin::sdk::events {

PusherEventListener::PusherEventListener(PusherEventService* service) : service(service) {
}

void PusherEventListener::on_event(const pusher::PusherEvent& event) {
    const std::string key = event.get_event_name().value_or("");
    const std::string channel = event.get_channel_name().value_or("");
    const std::string message = event.get_data().value_or("");

    auto listeners = service->get_listeners();
    auto logger = service->get_logger_provider();

    // Log event received
    if (logger != nullptr) {
        std::stringstream ss;
        ss << "Received event " << key << " on channel " << channel << " with results " << message;
        logger->log(utils::LogLevel::Info, ss.str());
    }

    if (listeners.empty()) {
        if (logger != nullptr) {
            logger->log(utils::LogLevel::Info, "No registered listener when event was received");
        }

        return;
    }

    EventTypeDef def = EventTypeDef::get_from_key(key);
    if (def.get_type() == models::EventType::Unknown) {
        if (logger != nullptr) {
            std::stringstream ss;
            ss << "Unknown event type for key " << def.get_key();
            logger->log(utils::LogLevel::Warn, ss.str());
        }

        return;
    }

    models::NotificationEvent notification_event(def.get_type(), channel, message);

    for (const auto& registration : listeners) {
        if (registration.get_matcher()(notification_event.get_type())) {
            registration.get_listener().notification_received(notification_event);
        }
    }
}

}
