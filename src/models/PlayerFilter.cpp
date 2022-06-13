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

#include "enjinsdk/models/PlayerFilter.hpp"

#include "enjinsdk/JsonUtils.hpp"
#include <utility>

using namespace enjin::sdk::json;
using namespace enjin::sdk::models;
using namespace enjin::sdk::serialization;
using namespace enjin::sdk::utils;

class PlayerFilter::Impl final : public ISerializable {
public:
    Impl() = default;

    ~Impl() override = default;

    [[nodiscard]] std::string serialize() const override {
        return to_json().to_string();
    }

    void set_and(std::vector<PlayerFilter> others) {
        and_filters_opt = std::move(others);
    }

    void set_or(std::vector<PlayerFilter> others) {
        or_filters_opt = std::move(others);
    }

    void set_id(std::string id) {
        id_opt = std::move(id);
    }

    void set_id_in(std::vector<std::string> ids) {
        id_in_opt = std::move(ids);
    }

    [[nodiscard]] json::JsonValue to_json() const override {
        JsonValue json = JsonValue::create_object();

        JsonUtils::try_set_field(json, "and", and_filters_opt);
        JsonUtils::try_set_field(json, "or", or_filters_opt);
        JsonUtils::try_set_field(json, "id", id_opt);
        JsonUtils::try_set_field(json, "id_in", id_in_opt);

        return json;
    }

    bool operator==(const Impl& rhs) const {
        return and_filters_opt == rhs.and_filters_opt
               && or_filters_opt == rhs.or_filters_opt
               && id_opt == rhs.id_opt
               && id_in_opt == rhs.id_in_opt;
    }

    bool operator!=(const Impl& rhs) const {
        return !(*this == rhs);
    }

private:
    std::optional<std::vector<PlayerFilter>> and_filters_opt;
    std::optional<std::vector<PlayerFilter>> or_filters_opt;
    std::optional<std::string> id_opt;
    std::optional<std::vector<std::string>> id_in_opt;
};

PlayerFilter::PlayerFilter() : pimpl(std::make_unique<Impl>()) {
}

PlayerFilter::PlayerFilter(const PlayerFilter& other) : pimpl(std::make_unique<Impl>(*other.pimpl)) {
}

PlayerFilter::PlayerFilter(PlayerFilter&& other) noexcept = default;

PlayerFilter::~PlayerFilter() = default;

std::string PlayerFilter::serialize() const {
    return pimpl->serialize();
}

PlayerFilter& PlayerFilter::set_and(std::vector<PlayerFilter> others) {
    pimpl->set_and(std::move(others));
    return *this;
}

PlayerFilter& PlayerFilter::set_or(std::vector<PlayerFilter> others) {
    pimpl->set_or(std::move(others));
    return *this;
}

PlayerFilter& PlayerFilter::set_id(std::string id) {
    pimpl->set_id(std::move(id));
    return *this;
}

PlayerFilter& PlayerFilter::set_id_in(std::vector<std::string> ids) {
    pimpl->set_id_in(std::move(ids));
    return *this;
}

JsonValue PlayerFilter::to_json() const {
    return pimpl->to_json();
}

bool PlayerFilter::operator==(const PlayerFilter& rhs) const {
    return *pimpl == *rhs.pimpl;
}

bool PlayerFilter::operator!=(const PlayerFilter& rhs) const {
    return *pimpl != *rhs.pimpl;
}

PlayerFilter& PlayerFilter::operator=(const PlayerFilter& rhs) {
    pimpl = std::make_unique<Impl>(*rhs.pimpl);
    return *this;
}
