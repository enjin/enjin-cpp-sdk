#ifndef ENJINCPPSDK_PUSHERCHANNELS_HPP
#define ENJINCPPSDK_PUSHERCHANNELS_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/serialization/IDeserializable.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::models {

/// \brief Models Pusher channels used by the platform.
class ENJINSDK_EXPORT PusherChannels : public enjin::sdk::serialization::IDeserializable {
public:
    /// \brief Default constructor.
    PusherChannels() = default;

    ~PusherChannels() override = default;

    void deserialize(const std::string& json) override;

    /// \brief Returns the project channel.
    /// \return The project channel.
    [[nodiscard]] const std::optional<std::string>& get_project() const;

    /// \brief Returns the player channel.
    /// \return The player channel.
    [[nodiscard]] const std::optional<std::string>& get_player() const;

    /// \brief Returns the asset channel.
    /// \return The asset channel.
    [[nodiscard]] const std::optional<std::string>& get_asset() const;

    /// \brief Returns the wallet channel.
    /// \return The wallet channel.
    [[nodiscard]] const std::optional<std::string>& get_wallet() const;

    bool operator==(const PusherChannels& rhs) const;

    bool operator!=(const PusherChannels& rhs) const;

private:
    std::optional<std::string> project;
    std::optional<std::string> player;
    std::optional<std::string> asset;
    std::optional<std::string> wallet;

    constexpr static char PROJECT_KEY[] = "project";
    constexpr static char PLAYER_KEY[] = "player";
    constexpr static char ASSET_KEY[] = "asset";
    constexpr static char WALLET_KEY[] = "wallet";
};

}

#endif //ENJINCPPSDK_PUSHERCHANNELS_HPP
