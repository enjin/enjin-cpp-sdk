#ifndef ENJINCPPSDK_PROJECT_HPP
#define ENJINCPPSDK_PROJECT_HPP

#include "enjinsdk/serialization/ISerializable.hpp"

namespace enjin::sdk::models {

class Project : public enjin::sdk::serialization::ISerializable {
public:
    Project() = default;

    void deserialize(const char* json) override;

    std::string serialize() override;

    // TODO: Implement fields and getters.
};

}

#endif //ENJINCPPSDK_PROJECT_HPP
