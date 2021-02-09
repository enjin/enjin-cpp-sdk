#ifndef ENJINCPPSDK_PLATFORM_HPP
#define ENJINCPPSDK_PLATFORM_HPP

#include "enjinsdk/models/Contracts.hpp"
#include "enjinsdk/models/Notifications.hpp"
#include "enjinsdk/serialization/IDeserializable.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::models {

/// \brief Models data about the platform.
class Platform : public enjin::sdk::serialization::IDeserializable {
public:
    /// \brief Default constructor.
    Platform() = default;

    void deserialize(const std::string& json) override;

    /// \brief Returns the ID of this platform.
    /// \return The ID.
    [[nodiscard]] const std::optional<int>& get_id() const;

    /// \brief Returns the name of this platform.
    /// \return The name.
    [[nodiscard]] const std::optional<std::string>& get_name() const;

    /// \brief Returns the current network this platform is using.
    /// \return The network.
    [[nodiscard]] const std::optional<std::string>& get_network() const;

    /// \brief Returns the smart contracts used by this platform.
    /// \return The contracts.
    [[nodiscard]] const std::optional<Contracts>& get_contracts() const;

    /// \brief Returns the notification drivers that this platform is using.
    /// \return The notification drivers.
    [[nodiscard]] const std::optional<Notifications>& get_notifications() const;

    bool operator==(const Platform& rhs) const;

    bool operator!=(const Platform& rhs) const;

private:
    std::optional<int> id;
    std::optional<std::string> name;
    std::optional<std::string> network;
    std::optional<Contracts> contracts;
    std::optional<Notifications> notifications;

    constexpr static char ID_KEY[] = "id";
    constexpr static char NAME_KEY[] = "name";
    constexpr static char NETWORK_KEY[] = "network";
    constexpr static char CONTRACTS_KEY[] = "contracts";
    constexpr static char NOTIFICATIONS_KEY[] = "notifications";
};

}

#endif //ENJINCPPSDK_PLATFORM_HPP