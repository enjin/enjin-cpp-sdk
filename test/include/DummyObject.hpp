#ifndef ENJINCPPSDK_DUMMYOBJECT_HPP
#define ENJINCPPSDK_DUMMYOBJECT_HPP

#include "enjinsdk/IDeserializable.hpp"
#include "enjinsdk/ISerializable.hpp"
#include <optional>
#include <string>

namespace enjin::test::utils {

class DummyObject : public sdk::serialization::IDeserializable,
                    public sdk::serialization::ISerializable {
public:
    std::optional<int> id;

    constexpr static char ID_KEY[] = "id";

    DummyObject() = default;

    explicit DummyObject(int id);

    ~DummyObject() override = default;

    void deserialize(const std::string& json) override;

    [[nodiscard]] std::string serialize() const override;

    bool operator==(const DummyObject& rhs) const;

    bool operator!=(const DummyObject& rhs) const;

    static DummyObject create_default_dummy_object();
};

}

#endif //ENJINCPPSDK_DUMMYOBJECT_HPP
