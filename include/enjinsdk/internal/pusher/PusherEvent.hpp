#ifndef ENJINCPPSDK_PUSHERPUSHEREVENT_HPP
#define ENJINCPPSDK_PUSHERPUSHEREVENT_HPP

#include "enjinsdk/serialization/IDeserializable.hpp"
#include <optional>
#include <string>

namespace enjin::pusher {

/// \brief Class for modeling Pusher events.
class PusherEvent : public sdk::serialization::IDeserializable {
public:
    /// \brief Default constructor.
    PusherEvent() = default;

    ~PusherEvent() override = default;

    void deserialize(const std::string& json) override;

    /// \brief Returns the user ID of the event.
    /// \return The optional for the user ID.
    [[nodiscard]] const std::optional<std::string>& get_user_id() const;

    /// \brief Returns the channel name of the event.
    /// \return The optional for the channel name.
    [[nodiscard]] const std::optional<std::string>& get_channel_name() const;

    /// \brief Returns the name of the event.
    /// \return The optional for the event name.
    [[nodiscard]] const std::optional<std::string>& get_event_name() const;

    /// \brief Returns the data of the event.
    /// \return The optional for the data.
    [[nodiscard]] const std::optional<std::string>& get_data() const;

    bool operator==(const PusherEvent& rhs) const;

    bool operator!=(const PusherEvent& rhs) const;

private:
    std::optional<std::string> user_id;
    std::optional<std::string> channel_name;
    std::optional<std::string> event_name;
    std::optional<std::string> data;
};

}

#endif //ENJINCPPSDK_PUSHERPUSHEREVENT_HPP
