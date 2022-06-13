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

#include "enjinsdk/models/MeltInput.hpp"

#include "enjinsdk/JsonUtils.hpp"
#include <utility>

using namespace enjin::sdk::json;
using namespace enjin::sdk::models;
using namespace enjin::sdk::serialization;
using namespace enjin::sdk::utils;

class MeltInput::Impl final : public ISerializable {
public:
    Impl() = default;

    ~Impl() override = default;

    [[nodiscard]] std::string serialize() const override {
        return to_json().to_string();
    }

    void set_asset_id(std::string id) {
        asset_id_opt = std::move(id);
    }

    void set_asset_index(std::string index) {
        asset_index_opt = std::move(index);
    }

    void set_value(std::string value) {
        value_opt = std::move(value);
    }

    [[nodiscard]] json::JsonValue to_json() const override {
        JsonValue json = JsonValue::create_object();

        JsonUtils::try_set_field(json, "assetId", asset_id_opt);
        JsonUtils::try_set_field(json, "assetIndex", asset_index_opt);
        JsonUtils::try_set_field(json, "value", value_opt);

        return json;
    }

    bool operator==(const Impl& rhs) const {
        return asset_id_opt == rhs.asset_id_opt
               && asset_index_opt == rhs.asset_index_opt
               && value_opt == rhs.value_opt;
    }

    bool operator!=(const Impl& rhs) const {
        return !(*this == rhs);
    }

private:
    std::optional<std::string> asset_id_opt;
    std::optional<std::string> asset_index_opt;
    std::optional<std::string> value_opt;
};

MeltInput::MeltInput() : pimpl(std::make_unique<Impl>()) {
}

MeltInput::MeltInput(const MeltInput& other) : pimpl(std::make_unique<Impl>(*other.pimpl)) {
}

MeltInput::MeltInput(MeltInput&& other) noexcept = default;

MeltInput::~MeltInput() = default;

std::string MeltInput::serialize() const {
    return pimpl->serialize();
}

MeltInput& MeltInput::set_asset_id(std::string id) {
    pimpl->set_asset_id(std::move(id));
    return *this;
}

MeltInput& MeltInput::set_asset_index(std::string index) {
    pimpl->set_asset_index(std::move(index));
    return *this;
}

MeltInput& MeltInput::set_value(std::string value) {
    pimpl->set_value(std::move(value));
    return *this;
}

JsonValue MeltInput::to_json() const {
    return pimpl->to_json();
}

bool MeltInput::operator==(const MeltInput& rhs) const {
    return *pimpl == *rhs.pimpl;
}

bool MeltInput::operator!=(const MeltInput& rhs) const {
    return *pimpl != *rhs.pimpl;
}

MeltInput& MeltInput::operator=(const MeltInput& rhs) {
    pimpl = std::make_unique<Impl>(*rhs.pimpl);
    return *this;
}
