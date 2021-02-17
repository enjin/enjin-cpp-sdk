#ifndef ENJINCPPSDK_PUSHERPUSHEROPTIONS_HPP
#define ENJINCPPSDK_PUSHERPUSHEROPTIONS_HPP

#include <optional>
#include <string>

namespace enjin::pusher {

/// \brief Class for modeling options for a Pusher client.
class PusherOptions {
public:
    /// \brief Default constructor.
    PusherOptions() = default;

    /// \brief Default destructor.
    ~PusherOptions() = default;

    /// \brief Returns the websocket host to be used by the client.
    /// \return The host.
    [[nodiscard]] std::string host() const;

    /// \brief Determines if encryption is to be used.
    /// \return Whether encryption is to be used.
    [[nodiscard]] bool is_encrypted() const;

    /// \brief Sets the cluster.
    /// \param cluster The cluster.
    /// \return This for chaining.
    PusherOptions& set_cluster(const std::string& cluster);

    /// \brief Sets whether encryption is to be used.
    /// \param encrypted The state.
    /// \return This for chaining.
    PusherOptions& set_encrypted(bool encrypted);

    /// \brief Returns the cluster.
    /// \return The optional for the cluster.
    [[nodiscard]] const std::optional<std::string>& get_cluster() const;

private:
    std::optional<std::string> cluster;
    bool encrypted = false;
};

}

#endif //ENJINCPPSDK_PUSHERPUSHEROPTIONS_HPP
