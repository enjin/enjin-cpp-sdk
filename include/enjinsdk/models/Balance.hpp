#ifndef ENJINCPPSDK_BALANCE_HPP
#define ENJINCPPSDK_BALANCE_HPP

#include "enjinsdk/models/Project.hpp"
#include "enjinsdk/models/Wallet.hpp"
#include "enjinsdk/serialization/IDeserializable.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::models {

/// \brief Models a item balance.
class Balance : public enjin::sdk::serialization::IDeserializable {
public:
    /// \brief Default constructor.
    Balance() = default;

    void deserialize(const std::string& json) override;

    /// \brief Returns the item ID for this balance.
    /// \return The item ID.
    [[nodiscard]] const std::optional<std::string>& get_id() const;

    /// \brief Returns the item index for this balance.
    /// \return The item index.
    [[nodiscard]] const std::optional<std::string>& get_index() const;

    /// \brief Returns the amount of the item in the balance.
    /// \return The amount of the item.
    [[nodiscard]] const std::optional<int>& get_value() const;

    /// \brief Returns the project the token of this balance belongs to.
    /// \return The project.
    [[nodiscard]] const std::optional<Project>& get_project() const;

    /// \brief Returns the wallet this balance belongs to.
    /// \return The wallet.
    [[nodiscard]] const std::optional<Wallet>& get_wallet() const;

    bool operator==(const Balance& rhs) const;

    bool operator!=(const Balance& rhs) const;

private:
    std::optional<std::string> id;
    std::optional<std::string> index;
    std::optional<int> value;
    std::optional<Project> project;
    std::optional<Wallet> wallet;

    constexpr static char ID_KEY[] = "id";
    constexpr static char INDEX_KEY[] = "index";
    constexpr static char VALUE_KEY[] = "value";
    constexpr static char PROJECT_KEY[] = "app";
    constexpr static char WALLET_KEY[] = "wallet";
};

}

#endif //ENJINCPPSDK_BALANCE_HPP
