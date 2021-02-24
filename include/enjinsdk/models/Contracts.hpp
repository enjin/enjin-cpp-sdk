#ifndef ENJINCPPSDK_CONTRACTS_HPP
#define ENJINCPPSDK_CONTRACTS_HPP

#include "enjinsdk_export.h"
#include "enjinsdk/models/SupplyModels.hpp"
#include "enjinsdk/serialization/IDeserializable.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::models {

/// \brief Models a smart contract used by the platform.
class ENJINSDK_EXPORT Contracts : public enjin::sdk::serialization::IDeserializable {
public:
    /// \brief Default constructor.
    Contracts() = default;

    ~Contracts() override = default;

    void deserialize(const std::string& json) override;

    /// \brief Returns the ENJ contract address.
    /// \return The contract address.
    [[nodiscard]] const std::optional<std::string>& get_enj() const;

    /// \brief Returns the crypto items contract address.
    /// \return The contract address.
    [[nodiscard]] const std::optional<std::string>& get_crypto_items() const;

    /// \brief Returns the platform registry contract address.
    /// \return The contract address.
    [[nodiscard]] const std::optional<std::string>& get_platform_registry() const;

    /// \brief Returns the supply models used by the platform.
    /// \return The supply models.
    [[nodiscard]] const std::optional<SupplyModels>& get_supply_models() const;

    bool operator==(const Contracts& rhs) const;

    bool operator!=(const Contracts& rhs) const;

private:
    std::optional<std::string> enj;
    std::optional<std::string> crypto_items;
    std::optional<std::string> platform_registry;
    std::optional<SupplyModels> supply_models;

    constexpr static char ENJ_KEY[] = "enj";
    constexpr static char CRYPTO_ITEMS_KEY[] = "cryptoItems";
    constexpr static char PLATFORM_REGISTRY_KEY[] = "platformRegistry";
    constexpr static char SUPPLY_MODELS_KEY[] = "supplyModels";
};

}

#endif //ENJINCPPSDK_CONTRACTS_HPP
