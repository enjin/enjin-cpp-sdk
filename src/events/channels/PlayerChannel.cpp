#include "PlayerChannel.hpp"

#include "StringUtils.hpp"
#include <sstream>

namespace enjin::sdk::events {

PlayerChannel::PlayerChannel(const models::Platform& platform, int app_id, const std::string& player_id)
        : platform(platform), app_id(app_id), player_id(player_id) {
}

std::string PlayerChannel::channel() const {
    return (std::stringstream() << "enjincloud."
                                << utils::to_lower(platform.get_network().value())
                                << ".app."
                                << app_id
                                << ".player."
                                << player_id
    ).str();
}

}
