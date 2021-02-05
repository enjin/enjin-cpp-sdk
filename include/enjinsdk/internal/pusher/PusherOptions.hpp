#ifndef ENJINCPPSDK_PUSHERPUSHEROPTIONS_HPP
#define ENJINCPPSDK_PUSHERPUSHEROPTIONS_HPP

#include <optional>
#include <string>

namespace enjin::pusher {

/// \brief TODO
class PusherOptions {
public:
    PusherOptions() = default;

    ~PusherOptions() = default;

    PusherOptions& set_cluster(const std::string& cluster);

    PusherOptions& set_use_tls(bool use_tls);

private:
    std::optional<std::string> cluster;
    bool use_tls = false;
};

}

#endif //ENJINCPPSDK_PUSHERPUSHEROPTIONS_HPP
