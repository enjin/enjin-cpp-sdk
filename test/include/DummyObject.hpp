/* Copyright 2021 Enjin Pte. Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

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

    constexpr static char IdKey[] = "id";

    DummyObject() = default;

    explicit DummyObject(int id);

    ~DummyObject() override = default;

    void deserialize(const std::string& json) override;

    [[nodiscard]] std::string serialize() const override;

    [[nodiscard]] sdk::json::JsonValue to_json() const override;

    bool operator==(const DummyObject& rhs) const;

    bool operator!=(const DummyObject& rhs) const;

    static DummyObject create_default_dummy_object();
};

}

#endif //ENJINCPPSDK_DUMMYOBJECT_HPP
