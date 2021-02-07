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

    [[nodiscard]] std::string host() const;

    [[nodiscard]] bool is_encrypted() const;

    PusherOptions& set_cluster(const std::string& cluster);

    PusherOptions& set_encrypted(bool encrypted);

    [[nodiscard]] const std::optional<std::string>& get_cluster() const;

private:
    std::optional<std::string> cluster;
    bool encrypted = false;
};

}

#endif //ENJINCPPSDK_PUSHERPUSHEROPTIONS_HPP
