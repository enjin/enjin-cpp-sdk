#include "enjinsdk/internal/pusher/PusherChannel.hpp"

namespace enjin::pusher {

void PusherChannel::bind(const std::string& event_name, ISubscriptionEventListener& listener) {
    // TODO: Implement function.
}

const std::string& PusherChannel::get_name() const {
    return name;
}

}
