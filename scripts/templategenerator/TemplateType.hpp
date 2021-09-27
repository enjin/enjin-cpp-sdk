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

#ifndef ENJINSDK_TEMPLATETYPE_HPP
#define ENJINSDK_TEMPLATETYPE_HPP

#include <ostream>
#include <string>
#include <vector>

namespace enjin::generator {

class TemplateType {
public:
    enum class Value {
        FRAGMENT,
        MUTATION,
        QUERY,
    };

    TemplateType() = delete;

    explicit TemplateType(Value value);

    ~TemplateType() = default;

    [[nodiscard]] Value value() const;

    [[nodiscard]] std::string to_string() const;

    bool operator==(const TemplateType& rhs) const;

    bool operator!=(const TemplateType& rhs) const;

    friend std::ostream& operator<<(std::ostream& os, const TemplateType& type);

    [[nodiscard]] static std::vector<TemplateType> values();

private:
    Value m_value;
};

}

#endif //ENJINSDK_TEMPLATETYPE_HPP
