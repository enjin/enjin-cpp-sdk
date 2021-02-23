#ifndef ENJINCPPSDK_PROJECTCHANNEL_HPP
#define ENJINCPPSDK_PROJECTCHANNEL_HPP

#include "IChannel.hpp"
#include "enjinsdk/models/Platform.hpp"

namespace enjin::sdk::events {

/// \brief Represents a channel to subscribe to for Enjin Cloud project events.
class ProjectChannel : public IChannel {
public:
    ProjectChannel() = delete;

    /// \brief Constructs a channel for the given network and project.
    /// \param platform The platform.
    /// \param project_id The project ID.
    ProjectChannel(const models::Platform& platform, int project_id);

    ~ProjectChannel() override = default;

    [[nodiscard]] std::string channel() const override;

private:
    models::Platform platform;
    int project_id;
};

}

#endif //ENJINCPPSDK_PROJECTCHANNEL_HPP
