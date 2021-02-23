#ifndef ENJINCPPSDK_PUSHEROPTIONS_HPP
#define ENJINCPPSDK_PUSHEROPTIONS_HPP

#include "enjinsdk/serialization/IDeserializable.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::models {

/// \brief Models Pusher options used by the platform.
class PusherOptions : public enjin::sdk::serialization::IDeserializable {
public:
    /// \brief Default constructor.
    PusherOptions() = default;

    ~PusherOptions() override = default;

    void deserialize(const std::string& json) override;

    /// \brief Returns the cluster the platform is in.
    /// \return The cluster.
    [[nodiscard]] const std::optional<std::string>& get_cluster() const;

    /// \brief Returns the encryption setting the platform uses.
    /// \return Whether encryption is used or not.
    [[nodiscard]] const std::optional<bool>& get_encrypted() const;

    bool operator==(const PusherOptions& rhs) const;

    bool operator!=(const PusherOptions& rhs) const;

private:
    std::optional<std::string> cluster;
    std::optional<bool> encrypted;

    constexpr static char CLUSTER_KEY[] = "cluster";
    constexpr static char ENCRYPTED_KEY[] = "encrypted";
};

}

#endif //ENJINCPPSDK_PUSHEROPTIONS_HPP
