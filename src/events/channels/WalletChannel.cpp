#include "WalletChannel.hpp"

#include "StringUtils.hpp"
#include <sstream>

namespace enjin::sdk::events {

WalletChannel::WalletChannel(const models::Platform& platform, const std::string& eth_address)
        : platform(platform), eth_address(eth_address) {
}

std::string WalletChannel::channel() const {
    std::stringstream ss;
    ss << "enjincloud."
       << utils::to_lower(platform.get_network().value())
       << ".wallet."
       << eth_address;
    return ss.str();
}

}
