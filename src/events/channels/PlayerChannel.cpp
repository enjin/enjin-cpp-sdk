#include "PlayerChannel.hpp"

#include "StringUtils.hpp"
#include <sstream>

namespace enjin::sdk::events {

PlayerChannel::PlayerChannel(const models::Platform& platform, int project_id, const std::string& player_id)
        : platform(platform), project_id(project_id), player_id(player_id) {
}

std::string PlayerChannel::channel() const {
    return (std::stringstream() << "enjincloud."
                                << utils::to_lower(platform.get_network().value())
                                << ".project."
                                << project_id
                                << ".player."
                                << player_id
    ).str();
}

}
