#include "AssetChannel.hpp"

#include "enjinsdk_utils/StringUtils.hpp"
#include <sstream>

namespace enjin::sdk::events {

AssetChannel::AssetChannel(const models::Platform& platform, const std::string& asset_id)
        : platform(platform), asset_id(asset_id) {
}

std::string AssetChannel::channel() const {
    std::stringstream ss;
    ss << "enjincloud."
       << utils::to_lower(platform.get_network().value())
       << ".asset."
       << asset_id;
    return ss.str();
}

}
