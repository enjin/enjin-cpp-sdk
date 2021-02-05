#ifndef ENJINCPPSDK_PUSHERPUSHEREVENT_HPP
#define ENJINCPPSDK_PUSHERPUSHEREVENT_HPP

#include "enjinsdk/serialization/IDeserializable.hpp"
#include <optional>
#include <string>

namespace enjin::pusher {

/// \brief TODO
class PusherEvent : sdk::serialization::IDeserializable {
public:
    PusherEvent() = default;

    ~PusherEvent() override = default;

    void deserialize(const std::string& json) override;

    [[nodiscard]] const std::optional<std::string>& get_user_id() const;

    [[nodiscard]] const std::optional<std::string>& get_channel_name() const;

    [[nodiscard]] const std::optional<std::string>& get_event_name() const;

    [[nodiscard]] const std::optional<std::string>& get_data() const;

    bool operator==(const PusherEvent& rhs) const;

    bool operator!=(const PusherEvent& rhs) const;

private:
    std::optional<std::string> user_id;
    std::optional<std::string> channel_name;
    std::optional<std::string> event_name;
    std::optional<std::string> data;

    constexpr static char USER_ID_KEY[] = "user_id";
    constexpr static char CHANNEL_NAME_KEY[] = "channel";
    constexpr static char EVENT_NAME_KEY[] = "event";
    constexpr static char DATA_KEY[] = "data";
};

}

#endif //ENJINCPPSDK_PUSHERPUSHEREVENT_HPP
