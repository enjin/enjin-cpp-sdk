#include "enjinsdk/models/Notifications.hpp"

#include "RapidJsonUtils.hpp"

namespace enjin::sdk::models {

void Notifications::deserialize(const std::string& json) {
    rapidjson::Document document;
    document.Parse(json.c_str());
    if (document.IsObject()) {
        if (document.HasMember(PUSHER_KEY) && document[PUSHER_KEY].IsObject()) {
            pusher.emplace(utils::get_object_as_type<Pusher>(document, PUSHER_KEY));
        }
    }
}

const std::optional<Pusher>& Notifications::get_pusher() const {
    return pusher;
}

bool Notifications::operator==(const Notifications& rhs) const {
    return pusher == rhs.pusher;
}

bool Notifications::operator!=(const Notifications& rhs) const {
    return !(rhs == *this);
}

}
