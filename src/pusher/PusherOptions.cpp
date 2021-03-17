#include "PusherOptions.hpp"

#include <sstream>

namespace enjin::pusher {

PusherOptions& PusherOptions::set_cluster(const std::string& cluster) {
    PusherOptions::cluster = cluster;
    return *this;
}

PusherOptions& PusherOptions::set_encrypted(bool encrypted) {
    PusherOptions::encrypted = encrypted;
    return *this;
}

const std::optional<std::string>& PusherOptions::get_cluster() const {
    return cluster;
}

bool PusherOptions::is_encrypted() const {
    return encrypted;
}

std::string PusherOptions::host() const {
    std::stringstream ss;
    ss << "ws-"
       << cluster.value_or("mt1")
       << ".pusher.com";
    return ss.str();
}

}
