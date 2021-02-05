#ifndef ENJINCPPSDK_PUSHERPUSHERCHANNEL_HPP
#define ENJINCPPSDK_PUSHERPUSHERCHANNEL_HPP

#include "enjinsdk/internal/pusher/PusherEvent.hpp"
#include "enjinsdk/internal/pusher/ISubscriptionEventListener.hpp"
#include <functional>
#include <string>

namespace enjin::pusher {

/// \brief TODO
class PusherChannel {
public:
    PusherChannel() = default;

    ~PusherChannel() = default;

    void bind(const std::string& event_name, ISubscriptionEventListener& listener);

    [[nodiscard]] const std::string& get_name() const;

private:
    std::string name;
};

}

#endif //ENJINCPPSDK_PUSHERPUSHERCHANNEL_HPP
