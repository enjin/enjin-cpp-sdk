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

#include "enjinsdk/models/AssetSortInput.hpp"

#include "enjinsdk/JsonUtils.hpp"

using namespace enjin::sdk::json;
using namespace enjin::sdk::models;
using namespace enjin::sdk::serialization;
using namespace enjin::sdk::utils;

class AssetSortInput::Impl final : public ISerializable {
public:
    Impl() = default;

    ~Impl() override = default;

    [[nodiscard]] std::string serialize() const override {
        return to_json().to_string();
    }

    void set_field(AssetField field) {
        field_opt = field;
    }

    void set_direction(SortDirection direction) {
        direction_opt = direction;
    }

    [[nodiscard]] json::JsonValue to_json() const override {
        JsonValue json = JsonValue::create_object();

        JsonUtils::try_set_field(json, "field", field_opt);
        JsonUtils::try_set_field(json, "direction", direction_opt);

        return json;
    }

    bool operator==(const Impl& rhs) const {
        return field_opt == rhs.field_opt
               && direction_opt == rhs.direction_opt;
    }

    bool operator!=(const Impl& rhs) const {
        return !(*this == rhs);
    }

private:
    std::optional<AssetField> field_opt;
    std::optional<SortDirection> direction_opt;
};

AssetSortInput::AssetSortInput() : pimpl(std::make_unique<Impl>()) {
}

AssetSortInput::AssetSortInput(const AssetSortInput& other) : pimpl(std::make_unique<Impl>(*other.pimpl)) {
}

AssetSortInput::AssetSortInput(AssetSortInput&& other) noexcept = default;

AssetSortInput::~AssetSortInput() = default;

std::string AssetSortInput::serialize() const {
    return pimpl->serialize();
}

AssetSortInput& AssetSortInput::set_field(AssetField field) {
    pimpl->set_field(field);
    return *this;
}

AssetSortInput& AssetSortInput::set_direction(SortDirection direction) {
    pimpl->set_direction(direction);
    return *this;
}

JsonValue AssetSortInput::to_json() const {
    return pimpl->to_json();
}

bool AssetSortInput::operator==(const AssetSortInput& rhs) const {
    return *pimpl == *rhs.pimpl;
}

bool AssetSortInput::operator!=(const AssetSortInput& rhs) const {
    return *pimpl != *rhs.pimpl;
}

AssetSortInput& AssetSortInput::operator=(const AssetSortInput& rhs) {
    pimpl = std::make_unique<Impl>(*rhs.pimpl);
    return *this;
}
