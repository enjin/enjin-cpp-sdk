#ifndef ENJINCPPSDK_REQUEST_HPP
#define ENJINCPPSDK_REQUEST_HPP

#include "enjinsdk/serialization/ISerializable.hpp"

namespace enjin::sdk::models {

class Request : public enjin::sdk::serialization::ISerializable {
public:
    Request() = default;

    void deserialize(const char* json) override;

    std::string serialize() override;

    // TODO: Implement fields and getters.
};

}

#endif //ENJINCPPSDK_REQUEST_HPP
