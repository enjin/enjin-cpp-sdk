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

#include "enjinsdk/models/SupplyModels.hpp"

#include "enjinsdk/JsonUtils.hpp"
#include "enjinsdk/JsonValue.hpp"

using namespace enjin::sdk::json;
using namespace enjin::sdk::models;
using namespace enjin::sdk::serialization;
using namespace enjin::sdk::utils;

class SupplyModels::Impl final : public IDeserializable {
public:
    Impl() = default;

    ~Impl() override = default;

    void deserialize(const std::string& json) override {
        JsonValue json_object;

        if (!json_object.try_parse_as_object(json)) {
            fixed.reset();
            settable.reset();
            infinite.reset();
            collapsing.reset();
            annual_value.reset();
            annual_percentage.reset();

            return;
        }

        JsonUtils::try_get_field(json_object, "fixed", fixed);
        JsonUtils::try_get_field(json_object, "settable", settable);
        JsonUtils::try_get_field(json_object, "infinite", infinite);
        JsonUtils::try_get_field(json_object, "collapsing", collapsing);
        JsonUtils::try_get_field(json_object, "annualValue", annual_value);
        JsonUtils::try_get_field(json_object, "annualPercentage", annual_percentage);
    }

    [[nodiscard]] const std::optional<std::string>& get_fixed() const {
        return fixed;
    }

    [[nodiscard]] const std::optional<std::string>& get_settable() const {
        return settable;
    }

    [[nodiscard]] const std::optional<std::string>& get_infinite() const {
        return infinite;
    }

    [[nodiscard]] const std::optional<std::string>& get_collapsing() const {
        return collapsing;
    }

    [[nodiscard]] const std::optional<std::string>& get_annual_value() const {
        return annual_value;
    }

    [[nodiscard]] const std::optional<std::string>& get_annual_percentage() const {
        return annual_percentage;
    }

    bool operator==(const Impl& rhs) const {
        return fixed == rhs.fixed
               && settable == rhs.settable
               && infinite == rhs.infinite
               && collapsing == rhs.collapsing
               && annual_value == rhs.annual_value
               && annual_percentage == rhs.annual_percentage;
    }

    bool operator!=(const Impl& rhs) const {
        return !(*this == rhs);
    }

private:
    std::optional<std::string> fixed;
    std::optional<std::string> settable;
    std::optional<std::string> infinite;
    std::optional<std::string> collapsing;
    std::optional<std::string> annual_value;
    std::optional<std::string> annual_percentage;
};

SupplyModels::SupplyModels() : pimpl(std::make_unique<Impl>()) {
}

SupplyModels::SupplyModels(const SupplyModels& other) : pimpl(std::make_unique<Impl>(*other.pimpl)) {
}

SupplyModels::SupplyModels(SupplyModels&& other) noexcept = default;

SupplyModels::~SupplyModels() = default;

void SupplyModels::deserialize(const std::string& json) {
    pimpl->deserialize(json);
}

const std::optional<std::string>& SupplyModels::get_fixed() const {
    return pimpl->get_fixed();
}

const std::optional<std::string>& SupplyModels::get_settable() const {
    return pimpl->get_settable();
}

const std::optional<std::string>& SupplyModels::get_infinite() const {
    return pimpl->get_infinite();
}

const std::optional<std::string>& SupplyModels::get_collapsing() const {
    return pimpl->get_collapsing();
}

const std::optional<std::string>& SupplyModels::get_annual_value() const {
    return pimpl->get_annual_value();
}

const std::optional<std::string>& SupplyModels::get_annual_percentage() const {
    return pimpl->get_annual_percentage();
}

bool SupplyModels::operator==(const SupplyModels& rhs) const {
    return *pimpl == *rhs.pimpl;
}

bool SupplyModels::operator!=(const SupplyModels& rhs) const {
    return *pimpl != *rhs.pimpl;
}

SupplyModels& SupplyModels::operator=(const SupplyModels& rhs) {
    pimpl = std::make_unique<Impl>(*rhs.pimpl);
    return *this;
}
