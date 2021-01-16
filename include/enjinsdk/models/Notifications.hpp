#ifndef ENJINCPPSDK_NOTIFICATIONS_HPP
#define ENJINCPPSDK_NOTIFICATIONS_HPP

#include "enjinsdk/models/Pusher.hpp"
#include "enjinsdk/serialization/IDeserializable.hpp"
#include <optional>

namespace enjin::sdk::models {

/// \brief Models the notification drivers and settings for the platform.
class Notifications : public enjin::sdk::serialization::IDeserializable {
public:
    /// \brief Default constructor.
    Notifications() = default;

    void deserialize(const std::string& json) override;

    /// \brief Returns the Pusher settings of the platform.
    /// \return The Pusher settings.
    [[nodiscard]] const std::optional<Pusher>& get_pusher() const;

    bool operator==(const Notifications& rhs) const;

    bool operator!=(const Notifications& rhs) const;

private:
    std::optional<Pusher> pusher;

    constexpr static char PUSHER_KEY[] = "pusher";
};

}

#endif //ENJINCPPSDK_NOTIFICATIONS_HPP
