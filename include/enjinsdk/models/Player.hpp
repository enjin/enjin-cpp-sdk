#ifndef ENJINCPPSDK_PLAYER_HPP
#define ENJINCPPSDK_PLAYER_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/models/LinkingInfo.hpp"
#include "enjinsdk/models/Wallet.hpp"
#include "enjinsdk/serialization/IDeserializable.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::models {

/// \brief Models a player on the platform.
class ENJINSDK_EXPORT Player : public enjin::sdk::serialization::IDeserializable {
public:
    /// \brief Default constructor.
    Player() = default;

    ~Player() override = default;

    void deserialize(const std::string& json) override;

    /// \brief Returns the ID of this player.
    /// \return The player ID.
    [[nodiscard]] const std::optional<std::string>& get_id() const;

    /// \brief Returns the linking information for this player.
    /// \return The information.
    [[nodiscard]] const std::optional<LinkingInfo>& get_linking_info() const;

    /// \brief Returns the wallet for this player.
    /// \return The wallet.
    [[nodiscard]] const std::optional<Wallet>& get_wallet() const;

    /// \brief Returns the datetime when this player was created.
    /// \return The datetime.
    /// \remarks The datetime is formatted using the ISO 8601 date format.
    [[nodiscard]] const std::optional<std::string>& get_created_at() const;

    /// \brief Returns the datetime when this player was last updated.
    /// \return The datetime.
    /// \remarks The datetime is formatted using the ISO 8601 date format.
    [[nodiscard]] const std::optional<std::string>& get_updated_at() const;

    bool operator==(const Player& rhs) const;

    bool operator!=(const Player& rhs) const;

private:
    std::optional<std::string> id;
    std::optional<LinkingInfo> linking_info;
    std::optional<Wallet> wallet;
    std::optional<std::string> created_at;
    std::optional<std::string> updated_at;

    constexpr static char ID_KEY[] = "id";
    constexpr static char LINKING_INFO_KEY[] = "linkingInfo";
    constexpr static char WALLET_KEY[] = "wallet";
    constexpr static char CREATED_AT_KEY[] = "createdAt";
    constexpr static char UPDATED_AT_KEY[] = "updatedAt";
};

}

#endif //ENJINCPPSDK_PLAYER_HPP
