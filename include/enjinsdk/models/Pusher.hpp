#ifndef ENJINCPPSDK_PUSHER_HPP
#define ENJINCPPSDK_PUSHER_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/IDeserializable.hpp"
#include "enjinsdk/models/PusherChannels.hpp"
#include "enjinsdk/models/PusherOptions.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::models {

/// \brief Models Pusher settings for the platform.
class ENJINSDK_EXPORT Pusher : public serialization::IDeserializable {
public:
    /// \brief Default constructor.
    Pusher() = default;

    ~Pusher() override = default;

    void deserialize(const std::string& json) override;

    /// \brief Returns the key for the platform.
    /// \return The key.
    [[nodiscard]] const std::optional<std::string>& get_key() const;

    /// \brief Returns the namespace the platform broadcasts on.
    /// \return The namespace.
    [[nodiscard]] const std::optional<std::string>& get_pusher_namespace() const;

    /// \brief Returns the Pusher channels the platform broadcasts on.
    /// \return The channels.
    [[nodiscard]] const std::optional<PusherChannels>& get_channels() const;

    /// \brief Represents the options for Pusher that the platform uses.
    /// \return The options.
    [[nodiscard]] const std::optional<PusherOptions>& get_options() const;

    bool operator==(const Pusher& rhs) const;

    bool operator!=(const Pusher& rhs) const;

private:
    std::optional<std::string> key;
    std::optional<std::string> pusher_namespace;
    std::optional<PusherChannels> channels;
    std::optional<PusherOptions> options;

    constexpr static char KEY_KEY[] = "key";
    constexpr static char PUSHER_NAMESPACE_KEY[] = "namespace";
    constexpr static char CHANNELS_KEY[] = "channels";
    constexpr static char OPTIONS_KEY[] = "options";
};

}

#endif //ENJINCPPSDK_PUSHER_HPP
