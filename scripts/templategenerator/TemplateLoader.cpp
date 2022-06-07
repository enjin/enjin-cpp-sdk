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

#include "TemplateLoader.hpp"

#include "enjinsdk_utils/StringUtils.hpp"
#include <fstream>
#include <stack>
#include <stdexcept>
#include <vector>

namespace fs = std::filesystem;

namespace enjin::generator {

TemplateLoader::TemplateLoader(fs::path resource_dir)
        : resource_dir(std::move(resource_dir)),
          fragments(std::make_shared<std::map<std::string, Template>>()) {
}

void TemplateLoader::load() {
    load_raw_resources();
}

void TemplateLoader::load_raw_resources() {
    if (!fs::exists(resource_dir)) {
        return;
    }

    // Selects the appropriate regular expression based on the filesystem
    std::regex re = fs::path::preferred_separator == '/'
            ? std::regex(FORWARD_SLASH_REGEX)
            : std::regex(BACK_SLASH_REGEX);

    std::stack<fs::path> path_stack;
    path_stack.push(resource_dir);

    while (!path_stack.empty()) {
        auto resource_path = path_stack.top();
        path_stack.pop();

        if (fs::is_directory(resource_path)) {
            for (const auto& entry : fs::directory_iterator(resource_path)) {
                path_stack.push(entry.path());
            }
        } else {
            std::string abs_path(fs::absolute(resource_path).string());
            std::smatch matcher;

            // Check if any matches were made
            if (!std::regex_search(abs_path, matcher, re)) {
                continue;
            }

            auto group_type = matcher[1];
            for (const auto& type : TemplateType::values()) {
                if (utils::to_lower(type.to_string()) == utils::to_lower(group_type)) {
                    load_and_cache_template_contents(resource_path, type);
                    break;
                }
            }
        }
    }
}

void TemplateLoader::load_and_cache_template_contents(const std::filesystem::path& path, TemplateType type) {
    std::ifstream file(path);

    std::vector<std::string> contents;
    std::string line;
    while (std::getline(file, line)) {
        contents.push_back(line);
    }

    file.close();

    if (contents.empty()) {
        return;
    }

    auto t_namespace = Template::read_namespace(contents);
    if (!t_namespace.has_value()) {
        return;
    }

    switch (type.value()) {
        case TemplateType::Value::Fragment:
            fragments->emplace(t_namespace.value(), Template(t_namespace.value(), type, contents, fragments));
            break;
        case TemplateType::Value::Mutation:
        case TemplateType::Value::Query:
            operations.emplace(t_namespace.value(), Template(t_namespace.value(), type, contents, fragments));
            break;
        default:
            throw std::runtime_error("Unknown template type: " + type.to_string());
    }
}

const std::map<std::string, Template>& TemplateLoader::get_operations() const {
    return operations;
}

}
