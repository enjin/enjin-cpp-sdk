#include "TokenChannel.hpp"

#include "StringUtils.hpp"
#include <sstream>

namespace enjin::sdk::events {

TokenChannel::TokenChannel(const models::Platform& platform, const std::string& token_id)
        : platform(platform), token_id(token_id) {
}

std::string TokenChannel::channel() const {
    return (std::stringstream() << "enjincloud."
                                << utils::to_lower(platform.get_network().value())
                                << ".token."
                                << token_id
    ).str();
}

}
