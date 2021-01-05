#ifndef ENJINCPPSDK_WALLET_HPP
#define ENJINCPPSDK_WALLET_HPP

#include "enjinsdk/serialization/ISerializable.hpp"

namespace enjin::sdk::models {

class Wallet : public enjin::sdk::serialization::ISerializable {
public:
    Wallet() = default;

    void deserialize(const char* json) override;

    std::string serialize() override;

    // TODO: Implement fields and getters.
};

}

#endif //ENJINCPPSDK_WALLET_HPP
