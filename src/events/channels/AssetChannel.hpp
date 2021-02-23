#ifndef ENJINCPPSDK_ASSETCHANNEL_HPP
#define ENJINCPPSDK_ASSETCHANNEL_HPP

#include "IChannel.hpp"
#include "enjinsdk/models/Platform.hpp"
#include <string>

namespace enjin::sdk::events {

/// \brief Represents a channel to subscribe to for Enjin Cloud asset events.
class AssetChannel : public IChannel {
public:
    AssetChannel() = delete;

    /// \brief Constructs a channel for the given network and asset.
    /// \param platform The platform.
    /// \param asset_id The asset ID.
    AssetChannel(const models::Platform& platform, const std::string& asset_id);

    ~AssetChannel() override = default;

    [[nodiscard]] std::string channel() const override;

private:
    models::Platform platform;
    std::string asset_id;
};

}

#endif //ENJINCPPSDK_ASSETCHANNEL_HPP
