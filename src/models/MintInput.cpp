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

#include "enjinsdk/models/MintInput.hpp"

#include "enjinsdk/JsonUtils.hpp"
#include <utility>

using namespace enjin::sdk::json;
using namespace enjin::sdk::models;
using namespace enjin::sdk::serialization;
using namespace enjin::sdk::utils;

class MintInput::Impl final : public ISerializable {
public:
    Impl() = default;

    ~Impl() override = default;

    [[nodiscard]] std::string serialize() const override {
        return to_json().to_string();
    }

    void set_to(std::string address) {
        to_opt = std::move(address);
    }

    void set_value(std::string value) {
        value_opt = std::move(value);
    }

    [[nodiscard]] json::JsonValue to_json() const override {
        JsonValue json = JsonValue::create_object();

        JsonUtils::try_set_field(json, "to", to_opt);
        JsonUtils::try_set_field(json, "value", value_opt);

        return json;
    }

    bool operator==(const Impl& rhs) const {
        return to_opt == rhs.to_opt
               && value_opt == rhs.value_opt;
    }

    bool operator!=(const Impl& rhs) const {
        return !(*this == rhs);
    }

private:
    std::optional<std::string> to_opt;
    std::optional<std::string> value_opt;
};

MintInput::MintInput() : pimpl(std::make_unique<Impl>()) {
}

MintInput::MintInput(const MintInput& other) : pimpl(std::make_unique<Impl>(*other.pimpl)) {
}

MintInput::MintInput(MintInput&& other) noexcept = default;

MintInput::~MintInput() = default;

std::string MintInput::serialize() const {
    return pimpl->serialize();
}

MintInput& MintInput::set_to(std::string address) {
    pimpl->set_to(std::move(address));
    return *this;
}

MintInput& MintInput::set_value(std::string value) {
    pimpl->set_value(std::move(value));
    return *this;
}

JsonValue MintInput::to_json() const {
    return pimpl->to_json();
}

bool MintInput::operator==(const MintInput& rhs) const {
    return *pimpl == *rhs.pimpl;
}

bool MintInput::operator!=(const MintInput& rhs) const {
    return *pimpl != *rhs.pimpl;
}

MintInput& MintInput::operator=(const MintInput& rhs) {
    pimpl = std::make_unique<Impl>(*rhs.pimpl);
    return *this;
}
