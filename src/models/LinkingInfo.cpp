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

#include "enjinsdk/models/LinkingInfo.hpp"

#include "enjinsdk/JsonUtils.hpp"
#include "enjinsdk/JsonValue.hpp"

using namespace enjin::sdk::json;
using namespace enjin::sdk::models;
using namespace enjin::sdk::serialization;
using namespace enjin::sdk::utils;

class LinkingInfo::Impl final : public IDeserializable {
public:
    Impl() = default;

    ~Impl() override = default;

    void deserialize(const std::string& json) override {
        JsonValue json_object;

        if (!json_object.try_parse_as_object(json)) {
            code.reset();
            qr.reset();

            return;
        }

        JsonUtils::try_get_field(json_object, "code", code);
        JsonUtils::try_get_field(json_object, "qr", qr);
    }

    [[nodiscard]] const std::optional<std::string>& get_code() const {
        return code;
    }

    [[nodiscard]] const std::optional<std::string>& get_qr() const {
        return qr;
    }

    bool operator==(const Impl& rhs) const {
        return code == rhs.code
               && qr == rhs.qr;
    }

    bool operator!=(const Impl& rhs) const {
        return !(*this == rhs);
    }

private:
    std::optional<std::string> code;
    std::optional<std::string> qr;
};

LinkingInfo::LinkingInfo() : pimpl(std::make_unique<Impl>()) {
}

LinkingInfo::LinkingInfo(const LinkingInfo& other) : pimpl(std::make_unique<Impl>(*other.pimpl)) {
}

LinkingInfo::LinkingInfo(LinkingInfo&& other) noexcept = default;

LinkingInfo::~LinkingInfo() = default;

void LinkingInfo::deserialize(const std::string& json) {
    pimpl->deserialize(json);
}

const std::optional<std::string>& LinkingInfo::get_code() const {
    return pimpl->get_code();
}

const std::optional<std::string>& LinkingInfo::get_qr() const {
    return pimpl->get_qr();
}

bool LinkingInfo::operator==(const LinkingInfo& rhs) const {
    return *pimpl == *rhs.pimpl;
}

bool LinkingInfo::operator!=(const LinkingInfo& rhs) const {
    return *pimpl != *rhs.pimpl;
}

LinkingInfo& LinkingInfo::operator=(const LinkingInfo& rhs) {
    pimpl = std::make_unique<Impl>(*rhs.pimpl);
    return *this;
}
