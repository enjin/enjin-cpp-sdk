#ifndef ENJINCPPSDK_TOKEN_HPP
#define ENJINCPPSDK_TOKEN_HPP

#include "enjinsdk/serialization/ISerializable.hpp"

namespace enjin::sdk::models {

class Token : public enjin::sdk::serialization::ISerializable {
public:
    Token() = default;

    void deserialize(const char* json) override;

    std::string serialize() override;

    // TODO: Implement fields and getters.
};

}

#endif //ENJINCPPSDK_TOKEN_HPP
