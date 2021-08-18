/* Copyright 2021 Enjin Pte Ltd.
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

#include "Template.hpp"

#include "enjinsdk_utils/StringUtils.hpp"
#include <algorithm>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>

namespace enjin::generator {

Template::Template(const std::string& template_namespace,
                   const TemplateType& type,
                   const std::vector<std::string>& contents,
                   const std::shared_ptr<std::map<std::string, Template>>& fragments)
        : template_namespace(template_namespace),
          type(type),
          fragments(fragments) {
    auto parts = utils::split(template_namespace, ".");
    name = parts[parts.size() - 1];

    parse_contents(contents);
}

std::string Template::compile() const {
    std::stringstream builder;
    builder << utils::join(" ", contents);

    if (type.value() == TemplateType::Value::FRAGMENT) {
        return builder.str();
    }

    std::vector<std::string> parameters = Template::parameters;
    std::set<std::string> processed_fragments;
    std::stack<Template> fragment_stack;

    for (const auto& reference : referenced_fragments) {
        fragment_stack.push(fragments->at(reference));
    }

    while (!fragment_stack.empty()) {
        auto fragment = fragment_stack.top();
        fragment_stack.pop();

        // Check if the fragment has already been processed
        if (processed_fragments.find(fragment.get_template_namespace()) != processed_fragments.end()) {
            continue;
        }

        // Cache the fragment's referenced fragments
        for (const auto& reference : fragment.referenced_fragments) {
            fragment_stack.push(fragments->at(reference));
        }

        // Copies the fragment's parameters to this template's parameters if they are not already cached
        std::copy_if(fragment.parameters.begin(),
                     fragment.parameters.end(),
                     std::back_inserter(parameters),
                     [parameters](const std::string& p) {
            return std::find(parameters.begin(), parameters.end(), p) == parameters.end();
        });

        builder << " " << fragment.compile();

        processed_fragments.emplace(fragment.template_namespace);
    }

    std::string replace_term = utils::to_lower(type.to_string());
    std::stringstream new_term_ss;

    new_term_ss << replace_term << " " << name;

    // Inserts necessary request header to process parameters if needed
    if (!parameters.empty()) {
        new_term_ss << "(";
        for (int i = 0; i < parameters.size(); i++) {
            new_term_ss << parameters[i];
            if (i < parameters.size() - 1) {
                new_term_ss << ", ";
            }
        }
        new_term_ss << ")";
    }

    std::string new_term = new_term_ss.str();

    return utils::trim(utils::replace(builder.str(), replace_term, new_term));
}

void Template::parse_contents(const std::vector<std::string>& contents) {
    for (const auto& line : contents) {
        auto trimmed = utils::trim(line);
        if (trimmed.find(IMPORT_KEY) == 0) {
            referenced_fragments.push_back(process_import(trimmed));
        } else if (trimmed.find(ARG_KEY) == 0) {
            parameters.push_back(process_arg(trimmed));
        } else if (!trimmed.empty() && trimmed.find('#') != 0) {
            Template::contents.push_back(trimmed);
        }
    }
}

const std::string& Template::get_template_namespace() const {
    return template_namespace;
}

const std::string& Template::get_name() const {
    return name;
}

TemplateType Template::get_type() const {
    return type;
}

std::optional<std::string> Template::read_namespace(const std::vector<std::string>& contents) {
    for (const auto& line : contents) {
        if (line.find(NAMESPACE_KEY) == 0) {
            return utils::trim(utils::split(line, " ")[1]);
        }
    }

    return std::nullopt;
}

std::string Template::process_arg(const std::string& line) {
    auto parts = utils::split(line, " ");
    if (parts.size() == 3) {
        std::stringstream ss;
        ss << "$" << parts[1] << ": " << parts[2];
        return ss.str();
    } else if (parts.size() == 4) {
        std::stringstream ss;
        ss << "$" << parts[1] << ": " << parts[2] << " = " << parts[3];
        return ss.str();
    }

    throw std::runtime_error("Argument 'line' in 'process_arg()' is of incorrect format");
}

std::string Template::process_import(const std::string& line) {
    auto parts = utils::split(line, " ");
    if (parts.size() == 2) {
        return parts[1];
    }

    throw std::runtime_error("Argument 'line' in 'process_import()' is of incorrect format");
}

}
