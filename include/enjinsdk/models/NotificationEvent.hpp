#ifndef ENJINCPPSDK_NOTIFICATIONEVENT_HPP
#define ENJINCPPSDK_NOTIFICATIONEVENT_HPP

#include "enjinsdk/models/EventType.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::models {

/// \brief Container class for notification data from the platform.
class NotificationEvent {
public:
    NotificationEvent() = delete;

    /// \brief Constructor to be used internally.
    /// \param type The event type.
    /// \param channel The event channel.
    /// \param message The serialized message.
    NotificationEvent(EventType type, std::string channel, std::string message);

    /// \brief Default destructor.
    ~NotificationEvent() = default;

    /// \brief Returns the event type.
    /// \return The event type.
    [[nodiscard]] EventType get_type() const;

    /// \brief Returns the event channel the event was broadcasted on.
    /// \return The channel.
    [[nodiscard]] const std::string& get_channel() const;

    /// \brief Returns the serialized message broadcasted with the event.
    /// \return The message.
    [[nodiscard]] const std::string& get_message() const;

    bool operator==(const NotificationEvent& rhs) const;

    bool operator!=(const NotificationEvent& rhs) const;

private:
    EventType type;
    std::string channel;
    std::string message;
};

}

#endif //ENJINCPPSDK_NOTIFICATIONEVENT_HPP
