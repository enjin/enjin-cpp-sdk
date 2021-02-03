#include "AppChannel.hpp"

#include "StringUtils.hpp"
#include <sstream>

namespace enjin::sdk::events {

AppChannel::AppChannel(const models::Platform& platform, int app_id)
        : platform(platform), app_id(app_id) {
}

std::string AppChannel::channel() const {
    return (std::stringstream() << "enjincloud."
                                << utils::to_lower(platform.get_network().value())
                                << ".app."
                                << app_id
    ).str();
}

}
