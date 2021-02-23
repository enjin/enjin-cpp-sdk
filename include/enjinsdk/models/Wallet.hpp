#ifndef ENJINCPPSDK_WALLET_HPP
#define ENJINCPPSDK_WALLET_HPP

#include "enjinsdk/models/Asset.hpp"
#include "enjinsdk/serialization/IDeserializable.hpp"
#include <optional>
#include <string>
#include <vector>

namespace enjin::sdk::models {

/// \brief Models a wallet on the platform.
class Wallet : public enjin::sdk::serialization::IDeserializable {
public:
    /// \brief Default constructor.
    Wallet() = default;

    void deserialize(const std::string& json) override;

    /// \brief Returns the Ethereum address of this wallet.
    /// \return The address.
    [[nodiscard]] const std::optional<std::string>& get_eth_address() const;

    /// \brief Returns the ENJ allowance given for crypto-items.
    /// \return The allowance.
    [[nodiscard]] const std::optional<float>& get_enj_allowance() const;

    /// \brief Returns the ENJ balance for this wallet.
    /// \return The balance.
    [[nodiscard]] const std::optional<float>& get_enj_balance() const;

    /// \brief Returns the ETH balance for this wallet.
    /// \return The balance.
    [[nodiscard]] const std::optional<float>& get_eth_balance() const;

    /// \brief Returns the assets this wallet has created.
    /// \return The assets.
    [[nodiscard]] const std::optional<std::vector<Asset>>& get_assets_created() const;

    bool operator==(const Wallet& rhs) const;

    bool operator!=(const Wallet& rhs) const;

private:
    std::optional<std::string> eth_address;
    std::optional<float> enj_allowance;
    std::optional<float> enj_balance;
    std::optional<float> eth_balance;
    std::optional<std::vector<Asset>> assets_created;

    constexpr static char ETH_ADDRESS_KEY[] = "ethAddress";
    constexpr static char ENJ_ALLOWANCE_KEY[] = "enjAllowance";
    constexpr static char ENJ_BALANCE_KEY[] = "enjBalance";
    constexpr static char ETH_BALANCE_KEY[] = "ethBalance";
    constexpr static char ASSETS_CREATED_KEY[] = "assetsCreated";
};

}

#endif //ENJINCPPSDK_WALLET_HPP
