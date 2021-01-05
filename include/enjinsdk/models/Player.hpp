#ifndef ENJINCPPSDK_PLAYER_HPP
#define ENJINCPPSDK_PLAYER_HPP

#include "enjinsdk/serialization/ISerializable.hpp"

namespace enjin::sdk::models {

class Player : public enjin::sdk::serialization::ISerializable {
public:
    Player() = default;

    void deserialize(const char* json) override;

    std::string serialize() override;

    // TODO: Implement fields and getters.
};

}

#endif //ENJINCPPSDK_PLAYER_HPP
