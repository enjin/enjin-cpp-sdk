#ifndef ENJINCPPSDK_BALANCE_HPP
#define ENJINCPPSDK_BALANCE_HPP

#include "enjinsdk/models/Project.hpp"
#include "enjinsdk/models/Wallet.hpp"
#include "enjinsdk/serialization/ISerializable.hpp"
#include <optional>
#include <string>

namespace enjin::sdk::models {

class Balance : public enjin::sdk::serialization::ISerializable {
public:
    Balance() = default;

    void deserialize(const char* json) override;

    std::string serialize() override;

    // TODO: Implement getters.

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
