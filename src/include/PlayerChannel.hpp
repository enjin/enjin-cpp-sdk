#ifndef ENJINCPPSDK_PLAYERCHANNEL_HPP
#define ENJINCPPSDK_PLAYERCHANNEL_HPP

#include "enjinsdk_export.h"
#include "IChannel.hpp"
#include "enjinsdk/models/Platform.hpp"
#include <string>

namespace enjin::sdk::events {

/// \brief Represents a channel to subscribe to for Enjin Cloud player events.
class ENJINSDK_EXPORT PlayerChannel : public IChannel {
public:
    PlayerChannel() = delete;

    /// \brief Constructs a channel for the given network and player on a project.
    /// \param platform The platform.
    /// \param project_id The project ID.
    /// \param player_id The player ID.
    PlayerChannel(const models::Platform& platform, int project_id, const std::string& player_id);

    ~PlayerChannel() override = default;

    [[nodiscard]] std::string channel() const override;

private:
    models::Platform platform;
    int project_id;
    std::string player_id;
};

}

#endif //ENJINCPPSDK_PLAYERCHANNEL_HPP
