#ifndef ENJINCPPSDK_APPCHANNEL_HPP
#define ENJINCPPSDK_APPCHANNEL_HPP

#include "IChannel.hpp"
#include "enjinsdk/models/Platform.hpp"

namespace enjin::sdk::events {

/// \brief Represents a channel to subscribe to for Enjin Cloud application events.
class AppChannel : public IChannel {
public:
    AppChannel() = delete;

    /// \brief Constructs a channel for the given network and application (project).
    /// \param platform The platform.
    /// \param app_id The app (project) ID.
    AppChannel(const models::Platform& platform, int app_id);

    ~AppChannel() override = default;

    [[nodiscard]] std::string channel() const override;

private:
    models::Platform platform;
    int app_id;
};

}

#endif //ENJINCPPSDK_APPCHANNEL_HPP
