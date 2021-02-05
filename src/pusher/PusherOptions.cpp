#include "enjinsdk/internal/pusher/PusherOptions.hpp"

namespace enjin::pusher {

PusherOptions& PusherOptions::set_cluster(const std::string& cluster) {
    PusherOptions::cluster = cluster;
    return *this;
}

PusherOptions& PusherOptions::set_use_tls(bool use_tls) {
    PusherOptions::use_tls = use_tls;
    return *this;
}

}
