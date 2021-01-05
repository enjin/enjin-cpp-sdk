#ifndef ENJINCPPSDK_DUMMYOBJECT_HPP
#define ENJINCPPSDK_DUMMYOBJECT_HPP

#include "enjinsdk/serialization/ISerializable.hpp"
#include <optional>
#include <string>

namespace enjin::test::utils {

class DummyObject : public enjin::sdk::serialization::ISerializable {
public:
    std::optional<int> id;
    constexpr static char ID_KEY[] = "id";

    DummyObject() = default;

    explicit DummyObject(int id);

    ~DummyObject() override = default;

    void deserialize(const char* json) override;

    std::string serialize() override;

    bool operator==(const DummyObject& rhs) const;

    bool operator!=(const DummyObject& rhs) const;

    static DummyObject create_default_dummy_object();

};

}

#endif //ENJINCPPSDK_DUMMYOBJECT_HPP
