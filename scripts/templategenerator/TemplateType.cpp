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

#include "TemplateType.hpp"

#include <stdexcept>

namespace enjin::generator {

TemplateType::TemplateType(TemplateType::Value value) : m_value(value) {
}

TemplateType::Value TemplateType::value() const {
    return m_value;
}

std::string TemplateType::to_string() const {
    switch (m_value) {
        case TemplateType::Value::Fragment:
            return "FRAGMENT";
        case TemplateType::Value::Mutation:
            return "MUTATION";
        case TemplateType::Value::Query:
            return "QUERY";
        default:
            throw std::runtime_error("Unknown template type");
    }
}

bool TemplateType::operator==(const TemplateType& rhs) const {
    return m_value == rhs.m_value;
}

bool TemplateType::operator!=(const TemplateType& rhs) const {
    return !(rhs == *this);
}

std::ostream& operator<<(std::ostream& os, const TemplateType& type) {
    os << type.to_string();
    return os;
}

std::vector<TemplateType> TemplateType::values() {
    return std::vector<TemplateType>({
        TemplateType(TemplateType::Value::Fragment),
        TemplateType(TemplateType::Value::Mutation),
        TemplateType(TemplateType::Value::Query),
    });
}

}
