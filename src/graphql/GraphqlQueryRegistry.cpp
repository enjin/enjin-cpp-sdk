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

#include "enjinsdk/GraphqlQueryRegistry.hpp"

#include "TemplateConstants.hpp"
#include <utility>

namespace enjin::sdk::graphql {

GraphqlQueryRegistry::GraphqlQueryRegistry() {
    register_template_constants();
}

bool GraphqlQueryRegistry::register_template(std::string name, std::string query) {
    if (registered.find(name) == registered.end()) {
        registered.emplace(std::move(name), std::move(query));
        return true;
    }

    return false;
}

void GraphqlQueryRegistry::register_template_constants() {
    for (const auto& t : TemplateConstants::templates) {
        register_template(t.first, t.second);
    }
}

bool GraphqlQueryRegistry::has_operation_for_name(const std::string& name) const {
    return registered.find(name) != registered.end();
}

std::string GraphqlQueryRegistry::get_operation_for_name(const std::string& name) const {
    auto iter = registered.find(name);
    if (iter == registered.end()) {
        return std::string();
    }

    return iter->second;
}

}
