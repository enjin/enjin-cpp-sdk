#include "PlayerChannel.hpp"

#include "enjinsdk_utils/StringUtils.hpp"
#include <sstream>

namespace enjin::sdk::events {

PlayerChannel::PlayerChannel(const models::Platform& platform, int project_id, const std::string& player_id)
        : platform(platform), project_id(project_id), player_id(player_id) {
}

std::string PlayerChannel::channel() const {
    std::stringstream ss;
    ss << "enjincloud."
       << utils::to_lower(platform.get_network().value())
       << ".project."
       << project_id
       << ".player."
       << player_id;
    return ss.str();
}

}
