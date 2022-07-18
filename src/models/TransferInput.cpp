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

#include "enjinsdk/models/TransferInput.hpp"

#include "enjinsdk/JsonUtils.hpp"
#include <utility>

using namespace enjin::sdk::json;
using namespace enjin::sdk::models;
using namespace enjin::sdk::serialization;
using namespace enjin::sdk::utils;

class TransferInput::Impl final : public ISerializable {
public:
    Impl() = default;

    ~Impl() override = default;

    [[nodiscard]] std::string serialize() const override {
        return to_json().to_string();
    }

    void set_from(std::string address) {
        from_opt = std::move(address);
    }

    void set_to(std::string address) {
        to_opt = std::move(address);
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

        JsonUtils::try_set_field(json, "from", from_opt);
        JsonUtils::try_set_field(json, "to", to_opt);
        JsonUtils::try_set_field(json, "assetId", asset_id_opt);
        JsonUtils::try_set_field(json, "assetIndex", asset_index_opt);
        JsonUtils::try_set_field(json, "value", value_opt);

        return json;
    }

    bool operator==(const Impl& rhs) const {
        return from_opt == rhs.from_opt
               && to_opt == rhs.to_opt
               && asset_id_opt == rhs.asset_id_opt
               && asset_index_opt == rhs.asset_index_opt
               && value_opt == rhs.value_opt;
    }

    bool operator!=(const Impl& rhs) const {
        return !(*this == rhs);
    }

private:
    std::optional<std::string> from_opt;
    std::optional<std::string> to_opt;
    std::optional<std::string> asset_id_opt;
    std::optional<std::string> asset_index_opt;
    std::optional<std::string> value_opt;
};

TransferInput::TransferInput() : pimpl(std::make_unique<Impl>()) {
}

TransferInput::TransferInput(const TransferInput& other) : pimpl(std::make_unique<Impl>(*other.pimpl)) {
}

TransferInput::TransferInput(TransferInput&& other) noexcept = default;

TransferInput::~TransferInput() = default;

std::string TransferInput::serialize() const {
    return pimpl->serialize();
}

TransferInput& TransferInput::set_from(std::string address) {
    pimpl->set_from(std::move(address));
    return *this;
}

TransferInput& TransferInput::set_to(std::string address) {
    pimpl->set_to(std::move(address));
    return *this;
}

TransferInput& TransferInput::set_asset_id(std::string id) {
    pimpl->set_asset_id(std::move(id));
    return *this;
}

TransferInput& TransferInput::set_asset_index(std::string index) {
    pimpl->set_asset_index(std::move(index));
    return *this;
}

TransferInput& TransferInput::set_value(std::string value) {
    pimpl->set_value(std::move(value));
    return *this;
}

JsonValue TransferInput::to_json() const {
    return pimpl->to_json();
}

bool TransferInput::operator==(const TransferInput& rhs) const {
    return *pimpl == *rhs.pimpl;
}

bool TransferInput::operator!=(const TransferInput& rhs) const {
    return *pimpl != *rhs.pimpl;
}

TransferInput& TransferInput::operator=(const TransferInput& rhs) {
    pimpl = std::make_unique<Impl>(*rhs.pimpl);
    return *this;
}
